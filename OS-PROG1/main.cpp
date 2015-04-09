#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/types.h>

using namespace std;

int direction[4][2] = {{0, -1}, {1, 0}, {0 ,1}, {-1, 0}};


void loadMap(char * , char [2][20][20]);
int route(char [20][20], int[2]);
int* findStartPoint(char [20][20]);
void robot(int, int , char[][20][20]);


int main(int argc, char* argv[])
{
	if(argc <= 1)
	{
		cout << "Please assign a map." << endl;
		fgetc(stdin);
		exit(1);
	}

	char map [2][20][20];
	loadMap(argv[1], map);
	int *startPoint = (findStartPoint(map[0]));
	robot(startPoint[0], startPoint[1], map);

	return 0;

}

void loadMap(char *filename, char map[2][22][22])
{
	ifstream mapFile(filename, ios::in);

	if ( !mapFile )
	{
		cout << "File could not be opened" << endl;
		exit( 1 );
	}

	char input[20];
	unsigned int row = 0;
	while( mapFile.getline(input,21) )
	{
		//cout << row;
		if(strlen(input))
		{
			//cout << " " << input;
			map[0][row][0] = map[1][row][0] = map[0][row][21] = map[1][row][21] = '*';
			strcpy(map[0][row][1], input);
			strcpy(map[1][row++][1], input);
		}
		//cout << endl;
	}

	mapFile.close();
}


int* findStartPoint(char map[20][20])
{
	int *position = new int[2];
	for(unsigned int i = 0; i < 20; i++)
	{
		for(unsigned int j = 0; j < 20; j++)
		{
			if(map[i][j] == 'S' || map[i][j] == 's')
			{
				
				position[0] = i;
				position[1] = j;
				return position;
			}
		}
	}
	return 0;
}

int route(char map[20][20], int pos[2])
{
	int count = 0;
	for(size_t i = 0; i < 4; i++)
	{
		if(map[pos[0] + direction[i][0]][pos[1] + direction[i][1]] == ' ')
			count++;
	}

	return count;
}

void robot(int x, int y, char map[][20][20])
{
	int pos[2];
	pos[0] = x, pos[1] = y;

	int numRoute = 0;

	while((numRoute = route(map[0], pos[0], pos[1])) > 0)
	{
		//路線數量大於1
		if(numRoute > 1)
		{
			for(size_t i = 0; i < numRoute; i++)
				fork();
		}


		
	}
}