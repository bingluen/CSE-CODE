#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdio.h>
#include <syscall.h>

using namespace std;

/*
* 地圖定義
* 牆壁 = 0
* 活路 = 1
* 礦源 = 2
* 起點 = 3
* 邊界 = 4
* 傳點上 = 5
* 傳點下 = 6
*/

/* define Map const */
const int MAP_WALL = 0;
const int MAP_ROAD = 1;
const int MAP_ORE = 2;
const int MAP_START = 3;
const int MAP_MARGIN = 4;
const int MAP_WARP_UP = 5;
const int MAP_WARP_DOWN = 6;

/**
 * Position print style
 * 標準輸出格式 = -1
 * Debug格式 = -2
 */
const int POSITION_PRINT_STYLE_STD = -1;
const int POSITION_PRINT_STYLE_RESULT = -3;
const int POSITION_PRINT_STYLE_DEBUG = -2;

/**
 * 前進方向
 * 上、右、下、左
 */
const short int direction[4][2] = { { 0, -1 }, { 1, 0 }, { 0, 1 }, { -1, 0 } };

/* Data structure */
//position
struct Position
{
	short int x;
	short int y;
	short int floor;
};

//robot
struct Robot
{
	struct Position pos;
	short int direction;
};

struct Pit
{
	short int floors;
	struct Map* startFloor;
	struct Map* endFloor;
};

struct Map
{
	short int data[22][22];
	struct Map* downFloor;
	struct Map* upFloor;
	short int row;
};

/* Global data */

struct Pit pit = { 0, 0, 0 };

pthread_t mainTid;

int numThread = 0;
int numOre = 0;

/* subroutine */

//loadPitMap
void loadPitMap(char* filename);

//AddMap
void addMapToPil(unsigned short int [22][22], size_t);

//encodeMapSymbol
int encodeMapSymbol(char symbol);

//decodeMapSymbol
char decodeMapSymbol(int code);

//print [Debug]
void printMap();

//explore
void explore();

//Stepping
void *stepping(void *pRobot);

//search start potin
struct Position searchStartPoint();

//search forward direction
size_t searchForwardDirection(struct Position pos);

//count number of road
short int countRoadNum(struct Position pos);

//set position to wall
void setWall(struct Position pos);


bool isUp(struct Position pos);
bool isDown(struct Position pos);
bool isOre(struct Position pos);

int main (int argc, char *argv[])
{
	struct timespec begin, end;
	double timeCost = 0;
	// get begin time 
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin); 

	mainTid = syscall(SYS_gettid);
	loadPitMap(argv[1]);
	explore();

	/* get end time  */
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

	/* Nanosecond to millisecond */
	timeCost = (end.tv_nsec - begin.tv_nsec) / 1000.0 / 1000.0;
	cout << "總執行時間：" << timeCost << " ms" << endl;

	cout << "本次探勘使用機器人(thread)數量：" << numThread << endl;
	cout << "找到的礦源有：" << numOre << "個" << endl;

	return 0;
}

void loadPitMap(char *filename)
{
	ifstream mapFile(filename, ios::in);

	if(!mapFile)
	{
		cout << "File could not be opened." << endl;
		exit(1);
	}

	unsigned short int map[22][22];
	unsigned int row = 0;


	//load file
	char input[20];

	/* 先讀第一行 */
	mapFile.getline(input, 21, '\n');
	/* 重新指向開頭 */
	mapFile.seekg(0);

	/* 判斷長度  若長度是20則只有一層地圖 */

	if(strlen(input) == 20)
	{
		row = 0;
		/* 只有一層地圖 */

		//set top margin
		for (size_t i = 0; i < 22; i++)
			map[row][i] = MAP_MARGIN;
		row++;

		while(mapFile.getline(input, 21, '\n'))
		{
			map[row][0] = MAP_MARGIN;
			for(size_t i = 1; i < 22; i++)
			{
				map[row][i] = encodeMapSymbol(input[i - 1]);
			}
			map[row++][21] = MAP_MARGIN;
		}

		//set bottom margin
		for (size_t i = 0; i < 22; i++)
			map[row][i] = MAP_MARGIN;
		row++;
		addMapToPil(map, row);
	} else {
		/* 多層地圖 */

		while(!mapFile.eof())
		{
			/* clear map */
			memset(map, 0, sizeof(unsigned short int) * 22 * 22);
			row = 0;

			//set top margin
			for (size_t i = 0; i < 22; i++)
				map[row][i] = MAP_MARGIN;
			row++;
			while(mapFile.getline(input, 21, '\n')) {
				if(strlen(input) < 20)
					if(row > 1)
						break;
					else
						continue;
			    map[row][0] = MAP_MARGIN;
				for(size_t i = 1; i < 22; i++)
				{
					map[row][i] = encodeMapSymbol(input[i - 1]);
				}
				map[row++][21] = MAP_MARGIN;
			}
			//set bottom margin
			for (size_t i = 0; i < 22; i++)
				map[row][i] = MAP_MARGIN;
			row++;
			addMapToPil(map, row);
		}
	}

	/*
	
	*/
}

void addMapToPil(unsigned short int map[22][22], size_t row)
{
	/* allocate momoery for map */
	struct Map *pMap;
	pMap = new Map;

	/* copy data */
	memcpy(pMap->data, map, sizeof(unsigned short int) * row * 22);
	pMap->row = row;

	if(pit.floors == 0)
	{
		pit.startFloor = pit.endFloor = pMap;
		pit.floors = 1;
		pMap->upFloor = pMap->downFloor = NULL;
	}
	else if(pit.floors >= 1)
	{
		pMap->upFloor = pit.endFloor;
		pMap->downFloor = NULL;
		pit.endFloor->downFloor = pMap;
		pit.endFloor = pMap;
		pit.floors += 1;
	}

	//cout << "[Debug] pit: floors = " << pit.floors << " , startFloor = " << pit.startFloor << " , endFloor = " << pit.endFloor << endl;
}

int encodeMapSymbol(char symbol)
{
	switch (symbol)
	{
	case ' ':
		return MAP_ROAD;
	case 'k':
	case 'K':
		return MAP_ORE;
	case 's':
	case 'S':
		return MAP_START;
	case '*':
		return MAP_WALL;
	case 'U':
	case 'u':
		return MAP_WARP_UP;
	case 'D':
	case 'd':
		return MAP_WARP_DOWN;
	}
}

char decodeMapSymbol(int code)
{
	switch (code)
	{
	case MAP_ROAD:
		return ' ';
	case MAP_ORE:
		return 'K';
	case MAP_START:
		return 'S';
	case MAP_WALL:
		return '*';
	case MAP_WARP_UP:
		return 'U';
	case MAP_WARP_DOWN:
		return 'D';
	case MAP_MARGIN:
		return '#';

	}
}

void printMap()
{
	cout << "順向列印" << endl;
	struct Map* pMap = pit.startFloor;
	for(size_t i = 0; i < pit.floors; i++)
	{
		cout << "第 " << "-" <<i << " 層" << endl;
		for(size_t j = 0; j < pMap->row; j++)
		{
			for(size_t k = 0; k < 22; k++)
			{
				cout << decodeMapSymbol(pMap->data[j][k]);
			}

			cout << endl;
		}
		pMap = pMap->downFloor;
	}
/*
	cout << endl;
	cout << "逆向列印" << endl;
	pMap = pit.endFloor;
	for(int i = pit.floors ; i > 0; i--)
	{
		cout << "第 "<< "-" << (i-1)*-1 << " 層" << endl;
		for(size_t j = 0; j < pMap->row; j++)
		{
			for(size_t k = 0; k < 22; k++)
			{
				cout << decodeMapSymbol(pMap->data[j][k]);
			}

			cout << endl;
		}
		pMap = pMap->upFloor;
	}
	*/
}

struct Position searchStartPoint()
{
	struct Position startPoint;
	struct Map* pMap = pit.startFloor;
	for(size_t k = 0; k < pit.floors; k++)
	{
		for(size_t i = 0; i < pMap->row; i++)
		{
			for(size_t j = 0; j < 22; j++)
			{
				if(pMap->data[i][j] == MAP_START)
				{
					startPoint.x = i;
					startPoint.y = j;
					startPoint.floor = k;

					//cout << "[Debug] startPoint: floors = " << startPoint.floor << " , startPoint.x = " << startPoint.x << " , startPoint.y = " << startPoint.y << endl;

					return startPoint;
				}
			}
		}
		pMap = pMap->downFloor;
	}
	
}

void printPosition(struct Position pos, int style)
{
	if (pit.floors > 1)
	{
		switch(style)
		{
			case POSITION_PRINT_STYLE_STD:
				cout << "[tid = " << syscall(SYS_gettid) << "]: (" << pos.floor * -1 << "," << pos.x - 1 << "," << pos.y - 1 << ")" << endl;
				break;
			case POSITION_PRINT_STYLE_RESULT:
				cout << syscall(SYS_gettid) << "(" << pos.floor * -1 << "," << pos.x - 1 << "," << pos.y - 1 << ")";
				break;
			case POSITION_PRINT_STYLE_DEBUG:
				cout << "[Debug] [tid = " << syscall(SYS_gettid) << "]: (" << pos.floor * -1 << "," << pos.x - 1 << "," << pos.y - 1 << ")" << endl;
				break;
		}
	} else {
		switch(style)
		{
			case POSITION_PRINT_STYLE_STD:
				cout << "[tid = " << syscall(SYS_gettid) << "]: (" << pos.x - 1 << "," << pos.y - 1 << ")" << endl;
				break;
			case POSITION_PRINT_STYLE_RESULT:
				cout << syscall(SYS_gettid) << "(" << pos.x - 1 << "," << pos.y - 1 << ")";
				break;
			case POSITION_PRINT_STYLE_DEBUG:
				cout << "[Debug] [tid = " << syscall(SYS_gettid) << "]: (" << pos.x - 1 << "," << pos.y - 1 << ")";
				break;
		}
	}
	
}

size_t searchForwardDirection(struct Position pos)
{
	/* 拿到所在樓層地圖 */
	struct Map *pMap = pit.startFloor;
	for(size_t i = 0; i < pos.floor && i < pit.floors; i++)
		pMap = pMap->downFloor;

	/*  尋找第一個可行進方向 */
	for(size_t i = 0; i < 4; i++)
	{
		if(pMap->data[pos.x + direction[i][0]][pos.y + direction[i][1]] == MAP_ROAD||
			pMap->data[pos.x + direction[i][0]][pos.y +direction[i][1]] == MAP_WARP_DOWN ||
			pMap->data[pos.x + direction[i][0]][pos.y +direction[i][1]] == MAP_WARP_UP ||
			pMap->data[pos.x + direction[i][0]][pos.y +direction[i][1]] == MAP_ORE)
			return i;
	}
}

short int countRoadNum(struct Position pos)
{
	short count = 0;

	//printPosition(pos, POSITION_PRINT_STYLE_DEBUG);


	/* 拿到所在樓層地圖 */
	struct Map *pMap = pit.startFloor;
	for(size_t i = 0; i < pos.floor && i < pit.floors; i++)
		pMap = pMap->downFloor;

	//cout << "[" <<  decodeMapSymbol(pMap->data[pos.x][pos.y]) << "]" << endl;

	/*  計算可行進方向 */
	for(size_t i = 0; i < 4; i++)
	{
		/*
		cout << "[ (" 
			<< pos.x + direction[i][0] << ", " << pos.y +direction[i][1] << ") "
			<<  decodeMapSymbol(pMap->data[pos.x + direction[i][0]][pos.y +direction[i][1]]) 
			<< "]" << endl;
			*/
		if(pMap->data[pos.x + direction[i][0]][pos.y +direction[i][1]] == MAP_ROAD ||
			pMap->data[pos.x + direction[i][0]][pos.y +direction[i][1]] == MAP_WARP_DOWN ||
			pMap->data[pos.x + direction[i][0]][pos.y +direction[i][1]] == MAP_WARP_UP||
			pMap->data[pos.x + direction[i][0]][pos.y +direction[i][1]] == MAP_ORE)
			count++;
	}

	return count;
}

void explore()
{
	/* init first robot */
	struct Robot robot;

	robot.pos = searchStartPoint();
	robot.direction = searchForwardDirection(robot.pos);

	stepping(reinterpret_cast<void *> (&robot));
}

void *stepping(void *pRob) 
{

	short int roadNum = 0;

	struct Robot * pR = reinterpret_cast<struct Robot *> (pRob);

	/* print robot position */
	printPosition(pR->pos, POSITION_PRINT_STYLE_STD);
	/* set to wall */
	setWall(pR->pos);

	/* go ahead */
	pR->pos.x += direction[pR->direction][0];
	pR->pos.y += direction[pR->direction][1];

	/* set to wall */
	setWall(pR->pos);

	while((roadNum = countRoadNum(pR->pos)) == 1)
	{

		/* find direction */
		pR->direction = searchForwardDirection(pR->pos);

		/* go-ahead */
		pR->pos.x += direction[pR->direction][0];
		pR->pos.y += direction[pR->direction][1];

		/* if is a stairs go down or go up */
		if(isDown(pR->pos))
		{
			/* set to wall */
			setWall(pR->pos);
			pR->pos.floor += 1;
			//printPosition(pR->pos, POSITION_PRINT_STYLE_DEBUG);
			cout << "往下一層" << endl;
			/* find direction */
			pR->direction = searchForwardDirection(pR->pos);
		}
		else if(isUp(pR->pos))
		{
			/* set to wall */
			setWall(pR->pos);
			pR->pos.floor -= 1;
			//printPosition(pR->pos, POSITION_PRINT_STYLE_DEBUG);
			cout << "往上一層" << endl;
			/* find direction */
			pR->direction = searchForwardDirection(pR->pos);
		}
			

		/* set to wall */
		if(!isOre(pR->pos))
			setWall(pR->pos);

		/* DEbug
			printMap();
			sleep(1);
		*/
	}

	if(roadNum > 1)
	{
		pthread_t *tid;
		pthread_attr_t *attr;
		struct Robot *pRobot;

		tid = new pthread_t[roadNum];
		attr = new pthread_attr_t[roadNum];

		/* 產生岔路數量的robot */
		for(size_t i = 0; i < roadNum; i++)
		{
			pthread_attr_init(attr + i);

			/* find direction */
			size_t dir = searchForwardDirection(pR->pos);

			pRobot = new struct Robot;

			pRobot->pos.x = pR->pos.x;
			pRobot->pos.y = pR->pos.y;
			pRobot->pos.floor = pR->pos.floor;
			pRobot->direction = dir;
			numThread++;
			pthread_create(tid+i, attr+i, stepping, reinterpret_cast<void *> (pRobot));
			sleep(3);
		}

		/* wait for all thread */
		bool isFound = false;
		for(size_t i = 0; i < roadNum; i++)
		{
			int *messages;
			pthread_join(*(tid+i), reinterpret_cast<void **> (&messages));
			if(*messages == 1)
			{
				isFound = true;
				printPosition(pR->pos, POSITION_PRINT_STYLE_RESULT);
				cout << " Found !" << endl;
			}
		}

		if(mainTid != syscall(SYS_gettid)) 
		{
			int mFound = 1;
			int mNone = 0;
			if(isFound)
				pthread_exit(&mFound);
			else
				pthread_exit(&mNone);
		}

	} else if(roadNum == 0 && mainTid != syscall(SYS_gettid)) {
		int mFound = 1;
		int mNone = 0;
		if(isOre(pR->pos))
		{
			/* set to wall */
			setWall(pR->pos);
			printPosition(pR->pos, POSITION_PRINT_STYLE_RESULT);
			cout << " Found !" << endl;
			numOre++;
			pthread_exit(&mFound);
		}
		else
		{
			/* set to wall */
			setWall(pR->pos);
			printPosition(pR->pos, POSITION_PRINT_STYLE_RESULT);
			cout << " None !" << endl;
			pthread_exit(&mNone);
		}
	}
}

void setWall(struct Position pos)
{
	/* 拿到所在樓層地圖 */
	struct Map *pMap = pit.startFloor;
	for(size_t i = 0; i < pos.floor && i < pit.floors; i++)
		pMap = pMap->downFloor;

	/* set wall */
	pMap->data[pos.x][pos.y] = MAP_WALL;
}

bool isDown(struct Position pos)
{
	/* 拿到所在樓層地圖 */
	struct Map *pMap = pit.startFloor;
	for(size_t i = 0; i < pos.floor && i < pit.floors; i++)
		pMap = pMap->downFloor;

	if(pMap->data[pos.x][pos.y] == MAP_WARP_DOWN)
		return true;
	else
		return false;
}

bool isUp(struct Position pos)
{
	/* 拿到所在樓層地圖 */
	struct Map *pMap = pit.startFloor;
	for(size_t i = 0; i < pos.floor && i < pit.floors; i++)
		pMap = pMap->downFloor;

	if(pMap->data[pos.x][pos.y] == MAP_WARP_UP)
		return true;
	else
		return false;
}

bool isOre(struct Position pos)
{
	/* 拿到所在樓層地圖 */
	struct Map *pMap = pit.startFloor;
	for(size_t i = 0; i < pos.floor && i < pit.floors; i++)
		pMap = pMap->downFloor;

	if(pMap->data[pos.x][pos.y] == MAP_ORE)
		return true;
	else
		return false;
}