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

int createProcess(int &count, int process_number);

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
	//save robot position
	int pos[2];

	//save route num
	int numRoute = 0;

	//save direction is passable
	bool passable[4] = { 0 };

	//save isFound?
	bool isFound = false;

	//step1 find start position
	findStartPoint(map, pos);

	pid_t pid = 0;

	//起點
	cout << "[pid = " << getpid() << "]" << "(" << pos[0] << " ," << pos[1] << ")" << endl;
	
	if(pid < 0)
	{
		cout << "fork 出錯了QQ" << endl;
		exit(1);
	}
	else if(pid == 0)
	{
		//step3 child process 進行探險
		//有路才走~
		while((numRoute = getRoute(map, passable, pos)) > 0
			&& !(isFound = (map[pos[0]][pos[1]] == 'K' || map[pos[0]][pos[1]] == 'k' )))
		{
			int count = 0;
			printf("pid = %d, num = %d pos = (%d, %d)\n", getpid(), numRoute, pos[0], pos[1]);
			if(numRoute > 1)
			{
				//多條路就fork
				
				pid = createProcess(count, numRoute);
				if(pid == 0)
				{
					//fork後把自己印出來
					cout << "[pid = " << getpid() << "]" << "(" << pos[0] << " ," << pos[1] << ")" << endl;

					//再繼續走
					size_t i = 0;
					for(; i < 4 && !passable[i]; i++);
					passable[i] = false;
					//把原本的路堵死變牆壁
					map[pos[0]][pos[1]] = '*';
					//前進
					pos[0] += direction[i][0];
					pos[1] += direction[i][1];

					//檢查有沒有道牆外..
					if(pos[0] > 19 || pos[1] > 19)
					{
						//退回去
						pos[0] -= direction[i][0];
						pos[1] -= direction[i][1];
					}
				} else if(pid > 0) {
					for(size_t i = 0; i < 4; i++)
						passable[i] = false;
					waitpid(-1, NULL, 0);
				}
				
			}
			else
			{
				size_t i = 0;
				for(; i < 4 && !passable[i]; i++);
				passable[i] = false;
				//把原本的路堵死變牆壁
				map[pos[0]][pos[1]] = '*';
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
			sleep(2);
		}

		//step4 沒路了回傳訊息
		// Child process closes up input side of pipe //
        close(fd[0]);
        // Send "string" through the output side of pipe //
        char messages[80];
        if(isFound)
        {
        	sprintf(messages, "%d (%d, %d) Found !", getpid(), pos[0], pos[1]);
        	write(fd[1], messages, sizeof(messages));
        }
        else
        {
        	sprintf(messages, "%d (%d, %d) None !", getpid(), pos[0], pos[1]);
        	write(fd[1], messages, sizeof(messages));
        }
        exit(0);
	}
	else
	{
		//把水管一端關起來
		close(fd[1]);
		//等所有的child
		while (pid = waitpid(-1, NULL, 0)) {
			//有child結束了，應該要有訊息回來，把他印出來
			nbytes = read(fd[0], tubeBuffer, sizeof(tubeBuffer));
			cout << tubeBuffer << endl;
		}
	}
	
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

int createProcess(int &count, int process_number) {
	
	pid_t pid = fork();
	
	if ( pid < 0 ) {
		cout << "fork() error\n";
		exit(1);
	}
	
	else if ( pid == 0 ) { // create odd numbers of child process (a half of full binary tree)

		if ( ++count < process_number )
			createProcess(count, process_number);
	}

	return pid;
}