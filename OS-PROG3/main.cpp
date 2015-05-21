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

/* subroutine */
//Robot
void *robot(struct Robot&);

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

int main (int argc, char *argv[])
{
	loadPitMap(argv[1]);
	printMap();
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

	cout << "[Debug] pit: floors = " << pit.floors << " , startFloor = " << pit.startFloor << " , endFloor = " << pit.endFloor << endl;
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
	struct Map* pMap = pit.startFloor;
	for(size_t i = 0; i < pit.floors; i++)
	{
		cout << "第 " << i << " 層" << endl;
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
}

void *robot(struct Robot&)
{
}

void explore()
{

}