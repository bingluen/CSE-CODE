#include <iostream>
#include <fstream>

using namespace std;

int direction[4][2] = {{0, -1}, {1, 0}, {0 ,1}, {-1, 0}};


void loadMap(char * , char [2][20][20]);
bool isSingleRoute(char [20][20], unsigned int[2]);
int* findStartPoint(char [20][20]);


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
	//cout << "row = " << startPoint[0] << " column = " << startPoint[1] << endl;


	return 0;

}

void loadMap(char *filename, char map[2][20][20])
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
	for(unsigned int i = 0; i < 20; i++)
	{
		for(unsigned int j = 0; j < 20; j++)
		{
			if(map[i][j] == 'S' || map[i][j] == 's')
			{
				int *position = new int[2];
				position[0] = i;
				position[1] = j;
				return position;
			}
		}
	}
}
