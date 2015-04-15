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

void loadMap(char *,char [20][20]);
void findStartPoint(char *[20], int*);

int getRouteNum(char map[20][20], struct Robot robot);

void getDirection(char map[20][20], struct Robot robot);
int getDirection(char map[20][20], int pos[]);
void getPassable(char map[20][20], bool passable[], int pos[]);

bool isOrePosition(char map[20][20], struct Robot robot);

void explore();

void createRobot(struct Robot &monther, int direction);

struct Robot
{
	int pos_x;
	int pos_y;
	int direction;
};

//direction of robot
int direction[4][2] = {{0, -1}, {1, 0}, {0 ,1}, {-1, 0}};

char map[20][20];

//儲存可以走得路
bool *passable = new bool[4];
int shm_id = 0;

int main(int argc, char* argv[])
{

	shm_id = shmget(IPC_PRIVATE,sizeof(passable),IPC_CREAT|0666);

	if(argc <= 1)
	{
		cout << "Please assign a map." << endl;
		exit(1);
	}

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
		if((robot.pos_x + direction[i][0] < 20 && robot.pos_y + direction[i][1] < 20
			&& map[robot.pos_x + direction[i][0]][robot.pos_y + direction[i][1]] == ' ')
			|| (robot.pos_x + direction[i][0] < 20 && robot.pos_y + direction[i][1] < 20
			&& map[robot.pos_x + direction[i][0]][robot.pos_y + direction[i][1]] == 'k')
			|| (robot.pos_x + direction[i][0] < 20 && robot.pos_y + direction[i][1] < 20
			&& map[robot.pos_x + direction[i][0]][robot.pos_y + direction[i][1]] == 'K'))
        {
            count++;
        }
	}

	return count;
}

void getDirection(char map[20][20], struct Robot robot)
{
	for(size_t i = 0; i < 4; i++)
	{
		if((robot.pos_x + direction[i][0] < 20 && robot.pos_y + direction[i][1] < 20
			&& map[robot.pos_x + direction[i][0]][robot.pos_y + direction[i][1]] == ' ')
			|| (robot.pos_x + direction[i][0] < 20 && robot.pos_y + direction[i][1] < 20
			&& map[robot.pos_x + direction[i][0]][robot.pos_y + direction[i][1]] == 'k')
			|| (robot.pos_x + direction[i][0] < 20 && robot.pos_y + direction[i][1] < 20
			&& map[robot.pos_x + direction[i][0]][robot.pos_y + direction[i][1]] == 'K'))
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
		if((pos[0] + direction[i][0] < 20 && pos[1] + direction[i][1] < 20
			&& map[pos[0] + direction[i][0]][pos[1] + direction[i][1]] == ' ')
			|| (pos[0] + direction[i][0] < 20 && pos[1] + direction[i][1] < 20
			&& map[pos[0] + direction[i][0]][pos[1] + direction[i][1]] == 'k')
			|| (pos[0] + direction[i][0] < 20 && pos[1] + direction[i][1] < 20
			&& map[pos[0] + direction[i][0]][pos[1] + direction[i][1]] == 'K'))
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
		if((pos[0] + direction[i][0] < 20 && pos[1] + direction[i][1] < 20
			&& map[pos[0] + direction[i][0]][pos[1] + direction[i][1]] == ' ')
			||(pos[0] + direction[i][0] < 20 && pos[1] + direction[i][1] < 20
			&& map[pos[0] + direction[i][0]][pos[1] + direction[i][1]] == 'k')
			|| (pos[0] + direction[i][0] < 20 && pos[1] + direction[i][1] < 20
			&& map[pos[0] + direction[i][0]][pos[1] + direction[i][1]] == 'K'))
        {
        	passable[i] = true;
        }
        else
        	passable[i] = false;
	}
}


void explore()
{
	struct Robot robot;
	int startPoint[2];
	findStartPoint(map, startPoint);

	//set robot
	robot.pos_x = startPoint[0];
	robot.pos_y = startPoint[1];
	robot.direction = getDirection(map, startPoint);
	getDirection(map, robot);

	//儲存是否找到
	bool isFound;

	//創造第一隻機器人
	pid_t pid = fork();

	int process_id = 0; // recognize different child process
	int count = 0; // count how many times does createProcess() execute

	//save Route number
	int numRoute = getRouteNum(map, robot);


	while( map[robot.pos_x][robot.pos_y] != '*' && !(isFound = isOrePosition(map, robot)) && robot.pos_x < 20 && robot.pos_y < 20)
	{
		if(pid == 0)
		{	
			//cout << "[pid = " << getpid() << "] (" << robot.pos_x << ", " << robot.pos_y << ")" << endl;

			//設定共享記憶體
			passable = (bool *)shmat(shm_id,0,0);
			while( (numRoute = getRouteNum(map, robot)) == 1 && !(isFound = isOrePosition(map, robot)) )
			{
				//cout << getpid() << "要從 (" << robot.pos_x << ", " << robot.pos_y << ") 前進了" << endl;
				//cout << getpid() << "方向是 (" << direction[robot.direction][0] << ", " << direction[robot.direction][1] << ")" << endl;
				//變牆壁，若是礦石就不要變成牆壁XD
				if(!(map[robot.pos_x][robot.pos_y] == 'k' || map[robot.pos_x][robot.pos_y] == 'K'))
					map[robot.pos_x][robot.pos_y] = '*';
				robot.pos_x += direction[robot.direction][0];
				robot.pos_y += direction[robot.direction][1];
				cout << "\t" << getpid() << "到達了 (" << robot.pos_x << ", " << robot.pos_y <<")  這裡樣子是 = \""<< map[robot.pos_x][robot.pos_y] << "\" 所以 isFound = " << isFound << endl;
				//刷新方向
				int point[2];
				point[0] = robot.pos_x;
				point[1] = robot.pos_y;
				robot.direction = getDirection(map, point);
			}

			cout << getpid() << "(" << robot.pos_x << ", " << robot.pos_y << ")" << " 離開while 目前numRoute = " << numRoute << " isFound = " << isFound << endl;

			if( numRoute == 0)
			{
				//沒路了
				cout << getpid() << " (" << robot.pos_x << ", " << robot.pos_y << ") None!" << endl;
				exit(0);
			}

			else if( numRoute > 1)
			{
				//把現在也設定為牆壁
				cout << endl;
				cout << endl;
				cout << "[FORK] " << getpid() << " in (" << robot.pos_x << ", " << robot.pos_y << ")!" << endl;
				map[robot.pos_x][robot.pos_y] = '*';
				//cout << "要生孩子囉" << endl;
				int point[2];
				point[0] = robot.pos_x;
				point[1] = robot.pos_y;
				//找可行方向
				getPassable(map, passable, point);
				for(size_t i = 0; i < 4; i++)
				{
					if(passable[i] == true)
					{
						//cout << "生了一個孩子 在 i = " << i << "時" << endl;
						passable[i] = false;
						createRobot(robot, i);
					}
				}
			}

			shmdt(passable); // detach shared memory

			cout << "[DEBUG !!][pid = " << getpid() << " parent =  "<< getppid() << "] (" << robot.pos_x << ", " << robot.pos_y << ")" << endl;

		}
		else if( pid > 0 )
		{
			wait(NULL);
		}

		sleep(10);
	}
}

void createRobot(struct Robot &monther, int dir)
{
	pid_t pid = fork();


	if ( pid < 0 ) {
		cout << "fork() error\n";
		exit(1);
	}
	
	else if ( pid == 0 ) { // create odd numbers of child process (a half of full binary tree)
		monther.pos_x += direction[dir][0];
		monther.pos_y += direction[dir][1];
		monther.direction = dir;
	}

	
	
}