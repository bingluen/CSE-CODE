#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdio.h>
#include <syscall.h>


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

const int MAP_WALL = 0;
const int MAP_ROAD = 1;
const int MAP_ORE = 2;
const int MAP_START = 3;
const int MAP_MARGIN = 4;
const int MAP_WARP_UP = 5;
const int MAP_WARP_DOWN = 6;

using namespace std;

int globalVariable = 10;
void *threadActivity(void* param);

int main (int argc, char *argv[])
{

	pthread_t tid[20];
	pthread_attr_t attr[20];

	cout << "MAIN讀取到全域變數 globalVariable 是 " << globalVariable << endl;


	int param = 44;

	cout << "param address " << &param << endl;

	for(size_t i = 0; i < 20; i++)
	{
		/* 初始化attr */
		pthread_attr_init(&attr[i]);

		/* create thread */
		pthread_create(&tid[i], &attr[i], threadActivity, &param);

		/* 等thread 跑完 */
		pthread_join(tid[i], NULL);
	}
	

	cout << "MAIN讀取到全域變數 globalVariable 是 " << globalVariable << endl;

	return 0;
}

void *threadActivity(void* param)
{
	cout << "這裡是一個thread 我的id是" << syscall(SYS_gettid) << endl;
	cout << "我可以讀取到全域變數XD globalVariable 是 " << globalVariable << endl;
	globalVariable += 10;
	cout << "然後把它+10 globalVariable 是 " << globalVariable << endl;
	cout << "參數是 ?? " << param << " value 是" << *(reinterpret_cast<int *> (param)) << endl;
	cout << "然後我要跟你說掰掰" << endl;
	pthread_exit(0);
}