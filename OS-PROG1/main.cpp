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
void loadMap(char *filename, short int(*map)[22]);
short int encodeMapSymbol(char);
char decodeMapSymbol(short int);
void explore();
void findStartingPoint(struct Position&);
int createRobot(short int dir);
int getNumRoute();
int getDirection();
void refreshPassableDirection(bool* passableDirection);
bool isPassable(short int, short int);
bool isOre(short int, short int);
bool isChild(int[], int, int);
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
short int(*map)[22];
bool *passableDirection = new bool[4];
unsigned int row = 0;

/* Direction const */
short int direction[4][2] = { { 0, -1 }, { 1, 0 }, { 0, 1 }, { -1, 0 } };

//shared memory setting
int map_shm_id = 0;
int totalNumOre_shm_id = 0;

//Total Ore
int *totalNumOre;

//main pid
pid_t mainPid;

int main(int argc, char* argv[])
{
	struct timespec begin, end;
	double timeCost = 0;

	//紀錄Root process的pid
	mainPid = getpid();

	// get begin time 
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin); 

	if (argc <= 1)
	{
		cerr << "Please assignment map data file." << endl;
		exit(1);
	}

	/* set shared memory */
	map_shm_id = shmget(IPC_PRIVATE, sizeof(short int)* 22 * 22, IPC_CREAT | 0666);
	totalNumOre_shm_id = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);

	/* load map */
	loadMap(argv[1], map);

	/* Find starting point */
	findStartingPoint(robot.pos);

	/* start to explore */
	explore();

	/* get begin time  */
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

	/* Print number of ore */
	totalNumOre = (int*)shmat(totalNumOre_shm_id, 0, 0);
	cout << "共有 " << *totalNumOre << " 個礦源" << endl;
	shmdt(totalNumOre);

	/* Nanosecond to millisecond */
	timeCost = (end.tv_nsec - begin.tv_nsec) / 1000.0 / 1000.0;
	cout << "總執行時間：" << timeCost << " ms" << endl;

	return 0;
}

void loadMap(char *filename, short int(*map)[22])
{
	/* 
		取得map所使用的shared memory位址
		呼叫shmat後，該block會被呼叫的process鎖定
	*/
	map = (short int(*)[22])shmat(map_shm_id, 0, 0);

	ifstream mapFile(filename, ios::in);

	if (!mapFile)
	{
		cout << "File could not be opened." << endl;
		exit(1);
	}

	//load file
	char input[20];

	//set top wall
	for (size_t i = 0; i < 22; i++)
		map[row][i] = MAP_MARGIN;

	row++;

	//load map
	while (mapFile.getline(input, 21, '\n'))
	{
		//set left wall
		map[row][0] = MAP_MARGIN;
		for (size_t i = 1; i < 22; i++)
		{
			map[row][i] = encodeMapSymbol(input[i - 1]);
		}
		//set right wall
		map[row++][21] = MAP_MARGIN;
	}

	//set bottom wall
	for (size_t i = 0; i < 22; i++)
		map[row][i] = MAP_MARGIN;

	row++;

	/* 
		解開map的存取，避免被process鎖定
	*/
	shmdt(map);
}

/*
	將讀入的地圖資料轉換為數值來儲存
*/
short int encodeMapSymbol(char symbol)
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
	}
}


/*
	為了印出地圖，將資料轉回文字
*/
char decodeMapSymbol(short int code)
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
	case MAP_MARGIN:
		return '#';
	}
}

void printMap()
{

	/* 
		取得map所使用的shared memory位址
		呼叫shmat後，該block會被呼叫的process鎖定
	*/
	map = (short int(*)[22])shmat(map_shm_id, 0, 0);

	/* 盡量不要在多process時執行，容易印歪。 */
	cout << "     \t 012345678901234567890" << endl;
	for (size_t i = 0; i < row; i++)
	{
		if(i > 0 && i < row - 1)
			cout << "i = " << i - 1 << "\t";
		else
			cout << "     \t";
		for (size_t j = 0; j < 22; j++)
		{
			cout << decodeMapSymbol(map[i][j]);
		}
		if(i > 0 && i < row - 1)
			cout << "\tAddress = " << &map[i];
		cout << endl;
	}

	/* 
		解開map的存取，避免被process鎖定
	*/
	shmdt(map);
}

void explore()
{
	
	cout << "[pid = " << getpid() << "]: (" << robot.pos.x - 1 << ", " << robot.pos.y - 1 << ")" << endl;

	pid_t pid = 0;

	bool isNotFound = true;
	int numRoute = getNumRoute();
	int status;

	int numOre = 0;

	int childNum = 0;
	int childPids[10] = { 0 };

	pid_t child_pid;

	while (isNotFinish())
	{
		if (pid == 0)
		{
			/*
				child process要做的事情=>向前探勘
			 */

			while (isNotFound && (numRoute = getNumRoute()) == 1)
			{
				/*
					當child process所在位置並非礦石所在地且沒有岔路時，不斷前進
				 */

				//Find direction to going
				robot.direction = getDirection();


				//going
				robot.pos.x += direction[robot.direction][0];
				robot.pos.y += direction[robot.direction][1];


				//isFound ?
				isNotFound = !(isOre(robot.pos.x, robot.pos.y));


				
				//set to wall
				
				map = (short int(*)[22])shmat(map_shm_id, 0, 0);	//存取map記憶體
				if (isNotFound)
				{
					map[robot.pos.x][robot.pos.y] = MAP_WALL;
				}
				shmdt(map);	//釋放掉map的鎖定


				/* 
					進階功能 ii 和 iii 可將此printMap()註解取消，來觀看地圖變化狀況，
					另外，若啟用printMap()，地圖印歪，或過程中出現負值的執行時間，可嘗試加大sleep。
					出現負值執行時間原因在於，時間間隔，導致多個process嘗試存取map，(分別是列印和行走)
					因為同時只能有一個process存取，n個process同時存取，只會有一個成功存取
					剩下n-1個會失敗，並直接exit掉...
				*/
				/* 
					printMap();
					sleep(5);
				*/
				
				/* 不要讓程式跑太快所以....睡一下 */
				sleep(1);

			}

			/* 離開迴圈有三種CASE */

			if (!isNotFound)
			{
				/*  CASE 1
					如果找到了，先印出來。
					並透過結束status回傳給parent process（將1傳入exit）
				 */
				
				//找到的礦源數加回儲存於shared memory的統計資料中
				totalNumOre = (int*)shmat(totalNumOre_shm_id, 0, 0);
				*totalNumOre += 1;
				shmdt(totalNumOre);

				cout << getpid() << " (" << robot.pos.x - 1 << ", " << robot.pos.y - 1 << ") Found!" << endl;
				exit(1);
			}

			else if (numRoute > 1)
			{
				/*
					CASE 2
					有岔路的case
				 */
				
				/*
					產生child process之前，先把pid重設成自己的。
					如此一來在之後的迴圈當中會被視為是parent，就會停在原地不前進
				 */
				pid = getpid();


				/* 計算可前進路線，因為會需要讀取地圖資料，所以先行鎖定 */
				map = (short int(*)[22])shmat(map_shm_id, 0, 0);
				refreshPassableDirection(passableDirection);
				shmdt(map);

				/* 初始化child數目 */
				childNum = 0;

				for (size_t i = 0; i < 4; i++)
				{
					/* 
						pid > 0 亦即要剛剛pid已經被重設，要產生child的process，
						(執行增加process的subroutine後pid會是child的pid，此時也會>0)
						防止被產生child也呼叫增加process的subroutine 
					*/
					if (pid > 0 && passableDirection[i])
					{
						passableDirection[i] = false;
						pid = createRobot(i);

						//紀錄child的pid
						childPids[childNum++] = pid;
					}
				}
			}
			else
			{
				/*
					CASE 3 走到死路了
					印出None並利用 status = 0告訴 parent沒找到
				 */
				cout << getpid() << " (" << robot.pos.x - 1 << ", " << robot.pos.y - 1 << ") None!" << endl;
				exit(0);
			}
		}

		else if (pid > 0)
		{
			/* 已經有child 的 process 在第二次外層迴圈會到這裡，等待child結束 */
			while ((child_pid = wait(&status)) != -1)
			{
				/*
					（此紀錄清單主要是要debug）
					child_pid會收集被結束的process pid
					將該pid與先前紀錄的child清單比對，確實為child，
					則將其除名
				 */
				if (isChild(childPids, child_pid, childNum))
				{
					childNum--;
				}

				/* 
					若process 執行exit(1) 在wait 會得到status == 256
					前述設計exit(1)表示找到礦石
					此處 得知自己第一子代找到礦石，印出found，
					並將isNotFound這個flag設為false用以在自己結束時
					決定exit所傳入之值，進而在往上一層process回報
				 */

				if (status == 256)
				{
					numOre++;
					cout << getpid() << " (" << robot.pos.x - 1 << ", " << robot.pos.y - 1 << ") Found! 其child累計搜尋到 "<< numOre << " 個礦源" << endl;
					isNotFound = false;
				}
			}


			/* 
				isNotFound意義已在上方說明
				當執行到此處（脫離while），表示其child都已經結束（找到/或未找到）
				依照isNotFound的value回報parent

				另外，為了要能夠回到main function，在process結束前一律檢查是不是Root Process
				不是root process的process才呼叫exit，並傳入status。
			*/
			if (isNotFound)
			{
				if (getpid() != mainPid)
					exit(0);
			}
			else
			{
				if (getpid() != mainPid)
					exit(1);
			}
		}
		else
		{
			cerr << "[!!! Fatal Error !!!] process (pid = " << getpid() << " ) fork error !" << endl;
			exit(-1);
		}
	
		/* 不要讓程式跑太快所以....睡一下 */
		sleep(1);
	}


}

int createRobot(short int dir)
{
	pid_t pid = fork();

	if (pid < 0)
	{
		cerr << "[!!! Fatal Error !!!] process (pid = " << getpid() << " )fork error !" << endl;
		exit(-1);
	}
	else if (pid == 0)
	{
		cout << "[pid = " << getpid() << "]: (" << robot.pos.x - 1 << ", " << robot.pos.y - 1 << ")" << endl;
		robot.pos.x += direction[dir][0];
		robot.pos.y += direction[dir][1];
		robot.direction = dir;

		/* 若新的位置即礦源，直接離開 */
		if(isOre(robot.pos.x, robot.pos.y))
		{
			totalNumOre = (int*)shmat(totalNumOre_shm_id, 0, 0);
			*totalNumOre += 1;
			shmdt(totalNumOre);

			cout << getpid() << " (" << robot.pos.x - 1 << ", " << robot.pos.y - 1 << ") Found!" << endl;
			exit(1);
		}
		

		/*
			把parent用牆壁關起來，確保即使parent prcess call getNumRouter會得到回傳值為0，而停留原地
		*/
		
		map = (short int(*)[22])shmat(map_shm_id, 0, 0);	//存取map共用記憶體
		map[robot.pos.x][robot.pos.y] = MAP_WALL;
		shmdt(map);	//釋放掉map
	}
	return pid;
}

int getNumRoute()
{
	int count = 0;
	for (size_t i = 0; i < 4; i++)
	{
		if (isPassable(robot.pos.x + direction[i][0], robot.pos.y + direction[i][1]))
			count++;
	}

	return count;
}

void refreshPassableDirection(bool* passableDirection)
{
	for (size_t i = 0; i < 4; i++)
	{

		if (isPassable(robot.pos.x + direction[i][0], robot.pos.y + direction[i][1]))
			passableDirection[i] = true;
		else
			passableDirection[i] = false;
	}
}

bool isPassable(short int x, short int y)
{
	map = (short int(*)[22])shmat(map_shm_id, 0, 0);
	if (x < 1 || y < 1 || x > 20 || y > 20)
	{
		shmdt(map);
		return false;
	}

	if (map[x][y] == MAP_ROAD || map[x][y] == MAP_ORE)
	{
		shmdt(map);
		return true;
	}

	shmdt(map);
	return false;
}

bool isOre(short int x, short int y)
{
	map = (short int(*)[22])shmat(map_shm_id, 0, 0);
	if (x < 1 || y < 1 || x > 20 || y > 20)
	{
		shmdt(map);
		return false;
	}

	map = (short int(*)[22])shmat(map_shm_id, 0, 0);
	if (map[x][y] == MAP_ORE)
	{
		shmdt(map);
		return true;
	}

	shmdt(map);
	return false;
}

int getDirection()
{
	for (size_t i = 0; i < 4; i++)
	{
		if (isPassable(robot.pos.x + direction[i][0], robot.pos.y + direction[i][1]))
			return i;
	}

	return -1;
}

void findStartingPoint(struct Position &pos)
{
	map = (short int(*)[22])shmat(map_shm_id, 0, 0);
	for (size_t i = 0; i < 22; i++)
	{
		for (size_t j = 0; j < 22; j++)
		{
			if (map[i][j] == MAP_START)
			{
				pos.x = i;
				pos.y = j;
				shmdt(map);
				return;
			}
		}
	}
}

bool isChild(int childPids[], int pid, int childNum)
{
	for (size_t i = 0; i < childNum; i++)
	{
		if (childPids[i] == pid)
		{
			childPids[i] = 0;
			return true;
		}
	}
	return false;
}

bool isNotFinish()
{
	map = (short int(*)[22])shmat(map_shm_id, 0, 0);
	for (size_t i = 1; i < 21; i++)
	{
		for (size_t j = 1; j < 21; j++)
		{
			if (map[i][j] == MAP_ROAD)
			{
				shmdt(map);
				return true;
			}

		}
	}

	shmdt(map);
	return false;
}