/*
 * 地圖定義
 * 牆壁 = 0
 * 活路 = 1
 * 礦源 = 2
 * 起點 = -1
 */

#define MAP_WALL 0
#define MAP_ROAD 1
#define MAP_ORE 2
#define MAP_START 3
#define MAP_MARGIN 4

#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/ipc.h>
#include <sys/shm.h>

using namespace std;

/* main component */
void loadMap(char *filename, short int (*map)[22]);
short int encodeMapSymbol(char);
char decodeMapSymbol(short int);
void explore();
void findStartingPoint(struct Position&);
int createRobot(short int dir);
int getNumRoute();
int getDirection();
void refreshPassableDirection(bool* passableDirection);
bool isPassable(short int , short int);
bool isOre(short int, short int);
bool isChild(int [], int, int);
bool isNotFinish();

/* debug tool */
void printMap();

/* Data Structure */

//position
struct Position
{
	short int x;
	short int y;
};

//robot
struct Robot
{
	struct Position pos;
	short int direction;
}robot;

/* Data */

//map data
short int (*map)[22] = new short int[22][22];
bool *passableDirection = new bool [4];
unsigned int row = 0;

/* Direction const */
short int direction[4][2] = {{0, -1}, {1, 0}, {0 ,1}, {-1, 0}};

//shared memory setting
int map_shm_id = 0;
int passableDirection_shm_id = 0;

//main pid
pid_t mainPid;

int main(int argc, char* argv[])
{
	struct timespec begin, end;
	double timeCost = 0;
	 mainPid = getpid();
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin); // get begin time 

	if(argc <= 1)
	{
		cerr << "Please assignment map data file." << endl;
		exit(1);
	}

	loadMap(argv[1], map);

	cout << "[Main pid = "<< getpid() <<"] map loading successful!" << endl;

	printMap();	

	//cout << "[Main pid = "<< getpid() <<"] Set map data to shared." << endl;

	//map_shm_id = shmget(IPC_PRIVATE,sizeof(short int)*22*22,IPC_CREAT|0666);

	//cout << "[Main pid = "<< getpid() <<"] Set passable direction record data to shared." << endl;

	//passableDirection_shm_id = shmget(IPC_PRIVATE,sizeof(passableDirection),IPC_CREAT|0666);

	/* test
	cout << "[Debug !!] Share memory Size:\t passableDirection = " << sizeof(passableDirection) << "\tmap = " << sizeof(map) << endl;
	*/

	cout << "[Main pid = "<< getpid() <<"] Finding starting point." << endl;

	findStartingPoint(robot.pos);

	cout << "[Main pid = "<< getpid() <<"] start to explore." << endl;

	explore();

	//printMap();

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end); // get begin time 

	timeCost = end.tv_sec - begin.tv_sec;
	cout << "總執行時間：" << timeCost << endl;

	return 0;
}

void loadMap(char *filename, short int (*map)[22])
{
	ifstream mapFile(filename, ios::in);

	if ( !mapFile )
	{
		cout << "File could not be opened." << endl;
		exit( 1 );
	}

	//load file
	char input[20];

	//set top wall
	for(size_t i = 0; i < 22; i++)
		map[row][i] = MAP_MARGIN;

	row++;

	//load map
	while( mapFile.getline(input, 21, '\n') )
	{
	    //set left wall
	    map[row][0] = MAP_MARGIN;
	    for(size_t i = 1; i < 22;i++)
	    {
	    	map[row][i] = encodeMapSymbol(input[i-1]);
	    }
	    //set right wall
	    map[row++][21] = MAP_MARGIN;
	}

	//set bottom wall
	for(size_t i = 0; i < 22; i++)
		map[row][i] = MAP_MARGIN;
	
	row++;
}

short int encodeMapSymbol(char symbol)
{
	switch(symbol)
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
	}
}

char encodeMapSymbol(short int code)
{
	switch(code)
	{
		case MAP_ROAD:
			return ' ';
		case MAP_ORE:
			return 'K';
		case MAP_START:
			return 'S';
		case MAP_WALL:
			return '*';
		case MAP_MARGIN:
			return '#';
	}
}

void printMap()
{
	/* 不要在多process時執行，會印歪。 */
	cout << "     \t0123456789012345678901" << endl;
	for(size_t i = 0; i < row; i++)
	{
		cout << "i = " << i << "\t";
		for(size_t j = 0; j < 22; j++)
		{
			cout << encodeMapSymbol(map[i][j]);
		}
		cout << "\tAddress = " << &map[i];
		cout << endl;
	}
}

void explore()
{
	//print first robot info.
	//cout << "[pid = " << getpid() << " Parent = " << getppid() << "]: (" << robot.pos.x << ", " << robot.pos.y << ")" << endl;
	cout << "[pid = " << getpid() << "]: (" << robot.pos.x << ", " << robot.pos.y << ")" << endl;

	pid_t pid = 0;

	bool isNotFound = true;
	int numRoute = getNumRoute();
	int status;

	int childNum = 0;
	int childPids[10] = {0};

	pid_t child_pid;
	
	/* test 
	cout << "[DEBUG!!!]迴圈外面，現在process是" << getpid() << "路線有" << numRoute << "條" << endl;
	*/
	while(isNotFinish())
	{
		/* test 
		cout << "[DEBUG!!!]現在process是" << getpid() << "路線有" << numRoute << "條" << endl;*/
		
		if(pid == 0)
		{
			/* test
			cout << "[DEBUG!!!]現在process是" << getpid() << "路線有" << numRoute << "條" << endl;
			*/
			

			while( isNotFound && (numRoute = getNumRoute()) == 1 )
			{
			    
			    /* test 
			    cout << "[DEBUG!!!] [process = " << getpid() << " Parent = " << getppid() << "]路線有" << numRoute << "條" << endl;
				*/
			
			    //Find direction to going
			    robot.direction = getDirection();

			    //going
			    robot.pos.x += direction[robot.direction][0];
			    robot.pos.y += direction[robot.direction][1];

			    /* test
			    cout << "\t pid = " << getpid() << " Parent = " << getppid() << " 移動到 (" << robot.pos.x << ", " << robot.pos.y << ")" << endl;
				*/
			
			    //isFound ?
			    isNotFound = !(isOre(robot.pos.x, robot.pos.y));

			    //set to wall
			    if(isNotFound)
			    {
			    	map[robot.pos.x][robot.pos.y] = MAP_WALL;
			    }
			}

			//cout << "[!!Debug!!] pid = " << getpid() << " Parent = " << getppid() << " 離開迴圈了" << endl;

			if(!isNotFound)
			{
				cout << getpid() << " (" << robot.pos.x << ", " << robot.pos.y << ") Found!" << endl;
				exit(1);
			}

			else if(numRoute > 1)
			{
				pid = getpid();
				refreshPassableDirection(passableDirection);

				/* debug 
				cout << "可正常執行到這" << endl;*/

				childNum = 0;

				for(size_t i = 0; i < 4; i++)
				{
					if(pid > 0 && passableDirection[i])
					{
						passableDirection[i] = false;
						pid = createRobot(i);
						childPids[childNum++] = pid;
						/*if(pid > 0)
							cout << "[!!Debug!!] pid = " << getpid() << " 生成 child process = " << pid << " 方向 = " << i << endl;*/
					}
					/*cout << "\t DirectionPassable = 左 " << passableDirection[0] 
						<< "上" << passableDirection[1] 
						<< "右" << passableDirection[2] 
						<< "下" << passableDirection[3] << endl;*/
						
				}
			}
			else
			{
				shmdt(map);
				shmdt(passableDirection);
				cout << getpid() << " (" << robot.pos.x << ", " << robot.pos.y << ") None!" << endl;
				exit(0);
			}

			//cout << "[DEBUG!!!]目前所在process是 << " << getpid() << " PID 是 " << pid << endl;
		}

		else if(pid > 0)
		{
			while( (child_pid = wait(&status)) != -1 )
			{
				//cout << "[DEBUG!!]目前 childe 數目 " << childNum << endl;
				//cout << "[DEBUG!!!]process " << child_pid << " 被結束了，狀態為 " << status << endl;
				if(isChild(childPids, child_pid, childNum))
				{
					childNum--;
				}

				//cout << "[DEBUG!!!] 剩餘child數目" << childNum << endl;

				if(status == 256)
				{
					isNotFound = false;
				}
			}
			

			if(isNotFound)
			{
				if(getpid() != mainPid)
					exit(0);
			}
			else
			{
				cout << getpid() << " (" << robot.pos.x << ", " << robot.pos.y << ") Found!" << endl;
				if(getpid() != mainPid)
					exit(1);
			}
		}
		else
		{
			cerr << "[!!! Fatal Error !!!] process (pid = " << getpid() << " ) fork error !" << endl;
			exit(-1);
		}

		/* test 
		cout << "[DEBUG!!!]外迴圈結尾，目前所在process是 << " << getpid() << " PID 是 " << pid << endl;
		*/
	
		/*cout << endl;
		cout << endl;*/
		/* test
		cout << "[!!Debug!!]目前地圖，視角 process " << getpid() << endl;
		printMap();
		cout << "[!!debug!!]address of passableDirection = " << passableDirection << endl;*/
		if(getpid() == mainPid)
			printMap();
		cout << endl;
		cout << endl;
		
		shmdt(map);
		shmdt(passableDirection);
		sleep(5);
	}


}

int createRobot(short int dir)
{
	pid_t pid = fork();

	if( pid < 0)
	{
		cerr << "[!!! Fatal Error !!!] process (pid = " << getpid() << " )fork error !" << endl;
		exit(-1);
	}
	else if( pid == 0)
	{
		//cout << "[pid = " << getpid() << " Parent = " << getppid() << "]: (" << robot.pos.x << ", " << robot.pos.y << ")" << endl;
		cout << "[pid = " << getpid() << "]: (" << robot.pos.x << ", " << robot.pos.y << ")" << endl;
		robot.pos.x += direction[dir][0];
		robot.pos.y += direction[dir][1];
		robot.direction = dir;

		//set memory share
		/*passableDirection = (bool *)shmat(passableDirection_shm_id, passableDirection, 0);*/
		//map = (short int (*)[22])shmat(map_shm_id, 0, 0);	

		/* test 
		cout << "[Debug !!] Share memory Size:\t passableDirection = " << sizeof(passableDirection) << "\tmap = " << sizeof(map) << endl;
		*/
		
		//printMap();

		//把parent關起來
		map[robot.pos.x][robot.pos.y] = MAP_WALL;
	}

	return pid;
}

int getNumRoute()
{
	int count = 0;
	for(size_t i = 0; i < 4; i++)
	{
		if(isPassable(robot.pos.x+direction[i][0], robot.pos.y+direction[i][1]))
			count++;
	}

	return count;
}

void refreshPassableDirection(bool* passableDirection)
{
	for(size_t i = 0; i < 4; i++)
	{
		/* debug 
		cout << "可正常執行到這 i = " << i << endl;
		cout << "passableDirection [" << i << "] 的內容是 = " << passableDirection[i] << endl;
		*/

		if(isPassable(robot.pos.x+direction[i][0], robot.pos.y+direction[i][1]))
			passableDirection[i] = true;
		else
			passableDirection[i] = false;
	}
}

bool isPassable(short int x, short int y)
{
	if(x < 1 || y < 1 || x > 20 || y > 20 )
		return false;

	if(map[x][y] == MAP_ROAD || map[x][y] == MAP_ORE)
		return true;

	return false;
}

bool isOre(short int x, short int y)
{
	if(x < 1 || y < 1 || x > 20 || y > 20 )
		return false;

	if(map[x][y] == MAP_ORE)
		return true;

	return false;
}

int getDirection()
{
	for(size_t i = 0; i < 4; i++)
	{
		if(isPassable(robot.pos.x+direction[i][0], robot.pos.y+direction[i][1]))
			return i;
	}

	return -1;
}

void findStartingPoint(struct Position &pos)
{
	for(size_t i = 0; i < 22; i++)
	{
		for(size_t j = 0; j < 22; j++)
		{
			if(map[i][j] == MAP_START)
			{
				pos.x = i;
				pos.y = j;
				return;
			}
		}
	}
}

bool isChild(int childPids[], int pid, int childNum)
{
	for(size_t i = 0; i < childNum; i++)
	{
		if(childPids[i] == pid)
		{
			childPids[i] = 0;
			return true;
		}
	}
	return false;
}

bool isNotFinish()
{
	for(size_t i = 1; i < 21; i++)
	{
		for(size_t j = 1; j < 21; j++)
		{
			if(map[i][j] == MAP_ROAD)
				return true;
		}
	}

	return false;
}