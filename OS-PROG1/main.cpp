#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/time.h>

using namespace std;

void loadMap(char *,char [20][20]);
int getRoute(char [20][20], bool *, int*);
void findStartPoint(char *[20], int*);
void explore();

void robot(int numRoute,  int pos[]);

struct single
{
	bool isFound;
};

//direction of robot
int direction[4][2] = {{0, -1}, {1, 0}, {0 ,1}, {-1, 0}};

int fd[2], nbytes;
char tubeBuffer[80];

char map[20][20];

int main(int argc, char* argv[])
{
	if(argc <= 1)
	{
		cout << "Please assign a map." << endl;
		exit(1);
	}

	pipe(fd);

	loadMap(argv[1], map);
	/* Test */
	cout << "map load successful! " << endl;
	explore();

	return 0;
}

void loadMap(char *filename, char map[20][20])
{
	ifstream mapFile(filename, ios::in);

	if ( !mapFile )
	{
		cout << "File could not be opened" << endl;
		exit( 1 );
	}

	char input[20];
	unsigned int row = 0;
	while( mapFile.getline(input, 21, '\n') )
	{
		if(strlen(input))
		{
+			strcpy(map[row++], input);
		}
	}

	mapFile.close();
}

void findStartPoint(char map[20][20], int* position)
{
	for(unsigned int i = 0; i < 20; i++)
	{
		for(unsigned int j = 0; j < 20; j++)
		{
			if(map[i][j] == 'S' || map[i][j] == 's')
			{
				
				position[0] = i;
				position[1] = j;
			}
		}
	}
}

void explore()
{

	//save position
	int pos[2] = { 0 };

	//get start position
	findStartPoint(map, pos);

	/* For every robot */

	//save direction passable
	bool passable[4] = { 0 };
	
	//save number of Route
	int numRoute = 0;

	//起點
	cout << "[pid = " << getpid() << "]" << "(" << pos[0] << " ," << pos[1] << ")" << endl;

	//讓robot 行動
	robot(getRoute(map, passable, pos), pos);
}

int getRoute(char map[20][20], bool *passable, int *pos)
{
	int count = 0;
	for(size_t i = 0; i < 4; i++)
	{
		if(pos[0] + direction[i][0] < 20 && pos[1] + direction[i][1]
			&& map[pos[0] + direction[i][0]][pos[1] + direction[i][1]] == ' ')
        {
            count++;
            passable[i] = true;
        }else{
            passable[i] = false;
        }
	}

	return count;
}

void robot(int numRoute, int pos[])
{
	//is fonud ?
	bool isFound = false;

	//來fork一隻機器人前進
	pid_t pid = fork();

	if(pid == 0)
	{
		//起點
		cout << "[pid = " << getpid() << "]" << "(" << pos[0] << " ," << pos[1] << ")" << endl;

		//save direction passable
		bool passable[4] = { 0 };

		//只有一條路
		if(numRoute == 1)
		{
			
			//前進條件
			//1.只有一條路
			//AND
			//2.沒找到礦石
			while((numRoute = getRoute(map, passable, pos)) == 1
				&& !(isFound = (map[pos[0]][pos[1]] == 'K' || map[pos[0]][pos[1]] == 'k' )))
			{
				//把原本的路堵死變牆壁
				map[pos[0]][pos[1]] = '*';

				//找方向
				size_t i = 0;
				for(; i < 4 && !passable[i]; i++);

				//前進
				pos[0] += direction[i][0];
				pos[1] += direction[i][1];

				//檢查有沒有道牆外..
				if(pos[0] > 19 || pos[1] > 19)
				{
					//退回去
					pos[0] -= direction[i][0];
					pos[1] -= direction[i][1];
					break;
				}
			}

			//不前進的原因
			//1.找到了
			//OR
			//2.有岔路
			//OR
			//3.死路了
			if(isFound)
			{
				cout << getpid() << " (" << pos[0] << ", " << pos[1] << ") Found !" << endl;
			}
			else if(numRoute == 0)
			{
				//死路狀態
				//寫下訊息
				cout << getpid() << " (" << pos[0] << ", " << pos[1] << ") None !" << endl;
				
			}
			else if(numRoute > 1)
			{
				for(size_t i = 0; i < 4; i++)
				{
					if(passable[i])
					{
						passable[i] = false;
						int newPos[2];
						newPos[0] = pos[0] + direction[i][0];
						newPos[1] = pos[1] + direction[i][1];
						robot(1, newPos);
					}
				}
			}
		}
		else(numRoute > 1)
		{
			for(size_t i = 0; i < 4; i++)
			{
				if(passable[i])
				{
					passable[i] = false;
					int newPos[2];
					newPos[0] = pos[0] + direction[i][0];
					newPos[1] = pos[1] + direction[i][1];
					robot(1, newPos);
				}
			}
		}
	}else if(pid > 0)
	{
		wait();
		//把child給的訊息印出
	}
	
}