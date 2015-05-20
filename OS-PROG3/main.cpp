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
	struct Map* startLayer;
	struct Map* endLayer;
};

struct Map
{
	short int data[22][22];
	struct Map* downLayer;
	struct Map* upLayer;
};

/* Global data */

struct Pit pit = { 0, 0, 0 };

void *robot(struct Robot&);

void loadPitMap(char* filename);

int main (int argc, char *argv[])
{

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

	//set top wall
	for (size_t i = 0; i < 22; i++)
		map[row][i] = MAP_MARGIN;
	row++;

	//load file
	char input[20];

	/* 先讀第一行 */
	mapFile.getline(input, 21, '\n');

	/* 判斷長度  若長度是20則 */

	cout << strlen(input) << endl;

	/*
	while(mapFile.getline(input, 21, '\n'))
	{
		//set left wall
		map[row][0] = MAP_MARGIN;
		for()
	}
	*/
}

void addMapToPil(unsigned short int map[22][22], size_t row)
{
	/* allocate momoery for map */
	struct Map *pMap;
	pMap = new Map;

	/* copy data */
	memcpy(pMap->data, map, sizeof(unsigned short int) * row * 22);

	if(pit.floors == 0)
	{
		pit.startLayer = pit.endLayer = pMap;
		pit.floors = 1;
		pMap->upLayer = pMap->downLayer = NULL;
	}
	else if(pit.floors >= 1)
	{
		pMap->upLayer = pit.endLayer;
		pMap->downLayer = NULL;
		pit.endLayer->downLayer = pMap;
		pit.endLayer = pMap;
		pit.floors += 1;
	}
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

void *robot(struct Robot&)
{
}