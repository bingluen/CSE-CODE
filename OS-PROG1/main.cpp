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
void findStartPoint(char *[20], int*);

int createRobot(struct Robot robot, int direction);

int getRouteNum(char map[20][20], struct Robot robot);

void getDirection(char map[20][20], struct Robot robot);
int getDirection(char map[20][20], int pos[]);
void getPassable(char map[20][20], bool passable[], int pos[]);

bool isOrePosition(char map[20][20], struct Robot robot);

void explore();

struct Robot
{
	int pos_x;
	int pos_y;
	int direction;
	bool isFound;
};

//direction of robot
int direction[4][2] = {{0, -1}, {1, 0}, {0 ,1}, {-1, 0}};

int fd[2], nbytes;
char tubeBuffer[80];

char map[20][20];

//count process num;
int countProcess;

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

	cout << "Main process pid = " << getpid() << endl;

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

int getRouteNum(char map[20][20], struct Robot robot)
{
	int count = 0;
	for(size_t i = 0; i < 4; i++)
	{
		if(robot.pos_x + direction[i][0] < 20 && robot.pos_y + direction[i][1] < 20
			&& map[robot.pos_x + direction[i][0]][robot.pos_y + direction[i][1]] == ' ')
        {
            count++;
        }
	}

	return count;
}


int createRobot(struct Robot robot, int dir)
{
	pid_t pid = fork();

	if(pid < 0)
	{
		cout << "fork error QAQ" << endl;
	} else if( pid == 0)
	{
		countProcess++;
		/*		test
		cout << "I\'m " << getpid() << " in (" << robot.pos_x << ", " << robot.pos_y << ") and count is" << countProcess << endl;
		*/
		/* Create process success */
		cout << "[pid = " << getpid() << "] (" << robot.pos_x << ", " << robot.pos_y << ")" << endl;
	}



	return pid;
}

void explore()
{
	struct Robot robot;
	int startPoint[2];
	findStartPoint(map, startPoint);

	//set robot
	robot.pos_x = startPoint[0];
	robot.pos_y = startPoint[1];
	robot.isFound = false;
	getDirection(map, robot);


	//儲存可以走得路
	bool passable[4];

	//儲存是否找到
	bool isFound;
	

	//創造第一隻機器人
	pid_t pid = createRobot(robot, getDirection(map, startPoint));

	//save Route number
	int numRoute;

	/* robot (child process)*/
	if(pid == 0)
	{
		//判別main or robot
		if(countProcess > 0) 
		{
			/* 剛被創造出來的robot */
			cout << "路線有 " << (numRoute = getRouteNum(map, robot)) << endl;
			//一條路往他的方向走
			while(numRoute == 1
				&& !(isFound = isOrePosition(map, robot)))
			{
				cout << getpid() << "要從 (" << robot.pos_x << ", " << robot.pos_y << ") 前進了" << endl;
				cout << getpid() << "方向是" << direction[robot.direction][0] << ", " << direction[robot.direction][1] << ")" << endl;
				//變牆壁
				map[robot.pos_x][robot.pos_y] = '*';
				robot.pos_x += direction[robot.direction][0];
				robot.pos_y += direction[robot.direction][1];
				cout << getpid() << "到達了 (" << robot.pos_x << ", " << robot.pos_y <<")" << endl;
				//刷新方向
				numRoute = getRouteNum(map, robot);
				getDirection(map, robot);
			}

			cout << getpid() << "離開回圈了= =" << endl;

			if(isFound)
			{
				cout << getpid() << " (" << robot.pos_x << ", " << robot.pos_y << ") Found!" << endl;
			}

			//如果有岔路
			if(numRoute > 1)
			{
				cout << "在 (" << robot.pos_x << ", "<< robot.pos_y <<") 發現岔路!!" << endl;

				/* 依照岔路產生機器人 */

				//先取得可行方向有哪些
				int currentPos[2];
				currentPos[0] = robot.pos_x;
				currentPos[1] = robot.pos_y;
				getPassable(map, passable, currentPos);

				//依照方向產生機器人
				for(size_t i = 0; i < 4; i++)
				{
					if(passable[i])
					{
						pid = createRobot(robot, i);
						cout << pid << endl;
					}
				}
					
			} 
			else if( numRoute == 0)
			{
				//沒路了
				cout << getpid() << " (" << robot.pos_x << ", " << robot.pos_y << ") None!" << endl;
			}

		}
		
	}
	else if (pid > 0)
	{
		/* 等child 的 robot */	
		while(pid = waitpid(-1, NULL, 0))
		{
			if(countProcess > 0) 
			{
				cout << "機器人在等小孩" << endl;
			}
			else if(countProcess == 0)
			{
				cout << "main 在等機器人" << endl;
				sleep(2);
			}
		}
	}
	/*
	else if(countProcess == 0)
	{
		//main
		cout << "主程式在等機器人" << endl;
		waitpid(pid, NULL, 0);
	}
	*/
}

void getDirection(char map[20][20], struct Robot robot)
{
	for(size_t i = 0; i < 4; i++)
	{
		if(robot.pos_x + direction[i][0] < 20 && robot.pos_y + direction[i][1] < 20
			&& map[robot.pos_x + direction[i][0]][robot.pos_y + direction[i][1]] == ' ')
        {
        	robot.direction = i;
        	break;
        }
	}

}

int getDirection(char map[20][20], int pos[])
{
	for(size_t i = 0; i < 4; i++)
	{
		if(pos[0] + direction[i][0] < 20 && pos[1] + direction[i][1]
			&& map[pos[0] + direction[i][0]][pos[1] + direction[i][1]] == ' ')
        {
            return i;
        }
	}
	return -1;
}

bool isOrePosition(char map[20][20], struct Robot robot)
{
	if(map[robot.pos_x][robot.pos_y] == 'k' || map[robot.pos_x][robot.pos_y] == 'K')
		return true;
	else
		return false;
}

void getPassable(char map[20][20], bool passable[], int pos[])
{
	for(size_t i = 0; i < 4; i++)
	{
		if(pos[0] + direction[i][0] < 20 && pos[1] + direction[i][1]
			&& map[pos[0] + direction[i][0]][pos[1] + direction[i][1]] == ' ')
        {
        	passable[i] = true;
        }
        else
        	passable[i] = false;
	}
}