#include <cstring>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>


using namespace std;


//direction of robot
int direction[4][2] = {{0, -1}, {1, 0}, {0 ,1}, {-1, 0}};


void loadMap(char * , char [2][20][20]);
int route(char [20][20], int[2], bool[4]);
int* findStartPoint(char [20][20]);
//void explore();


//map
char map [2][20][20];

//robot
struct robot{
    int pos_x;
    int pos_y;
    int direction;
};

int main(int argc, char* argv[])
{
    struct timespec begin, end;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin);
	if(argc <= 1)
	{
		cout << "Please assign a map." << endl;
		fgetc(stdin);
		exit(1);
	}

	loadMap(argv[1], map);
	
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
			strcpy(map[0][row], input);
			strcpy(map[1][row++], input);
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

int route(char map[20][20], int pos[2], bool available[4])
{
	int count = 0;
	for(size_t i = 0; i < 4; i++)
	{
		if(map[pos[0] + direction[i][0]][pos[1] + direction[i][1]] == ' ')
        {
            count++;
            available[i] = true;
        }else{
            available[i] = false;
        }
	}

	return count;
}

void explore()
{
    int *startPoint = (findStartPoint(map[0]));
    int numRoute;
    bool available[4];
    while(numRoute = route(map[0], startPoint, available))
    {
        //Only one route
        if(numRoute == 1)
        {
            //set currently position be wall
            map[0][startPoint[0]][startPoint[1]] = '*';
            int i = 0;
            for(; i < 4 && !available[i];i++);
            startPoint[0] += direction[i][0];
            startPoint[1] += direction[i][1];
        }

        //multi route
        if(numRoute > 1)
        {
            //multi route
        }
    }
}
