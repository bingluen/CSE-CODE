#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <semaphore.h>
#include <time.h>

/* define constant */

const unsigned short int MATERIAL_BATTERY 1;
const unsigned short int MATERIAL_SENSOR 2;
const unsigned short int MATERIAL_WIFI 3;
const unsigned short int MATERIAL_CRAWLER 4;

const unsigned short int IDENTITY_PRODUCER 0;
const unsigned short int IDENTITY_DISPACHER 1;

const unsigned short int NUM_TYPE_MATERIAL 4;

/* define data structure */

typedef struct {
	bool material[NUM_TYPE_MATERIAL];
} Desk;


typedef struct {
	unsigned short int pid;
	unsigned short int identity;
	unsigned short int heldMaterials;
	unsigned short int numOutput;
} Thread;


/* Function prototype */
void basic();
void advance();
void threading(void*);
void producer(Thread*);
void dispacher(Thread*);

/* Declare global variable */

Desk desk;
sem_t threadSem[NUM_TYPE_MATERIAL + 1];
int numProduct = 0;

int main(int argc, char *argv[])
{
	switch(atoi(argv[1]))
	{
		case 2:
			advance();
			break;
		case 1:
		default:
			basic();
	}

	return 0;
}

void basic()
{
	/* 5個thread的資料 */
	Thread thread[5];
	pthread_t thread_id[5];
	pthread_attr_t thread_attr[5];

	/* setting thread */
	//Dispacher
	sem_init(&threadSem[0], 0, 0);
	thread[0].identity = IDENTITY_DISPACHER;
	thread[0].id = 0;
	//Producer
	for(size_t i = 1; i < 5; i++)
	{
		sem_init(&threadSem[i], 0, 0);
		thread[i].id = i;
		thread[i].identity = IDENTITY_PRODUCER;
		thread[i].heldMaterials = i;
		thread[i].numOutput = 0;
	}

	/* create thread */
	for(size_t i = 0; i < 5; i++)
	{
		pthread_attr_init(thread_attr+i);
		pthread_create(thread_id+i, thread_attr+i, threading, reinterpret_cast<void *> (thread+i));
	}

	for(size_t i = 0; i < 5; i++)
	{
		pthread_join(thread_id+i, thread_att+i, threading, reinterpret_cast<void *> (thread+i));
	}
}

void threading(void* threadContext)
{
	Thread *thread = ( reinterpret_cast<* Thread> threadContext );

	switch(thread.identity)
	{
		case IDENTITY_PRODUCER:
			producer(thread);
			break;
		case IDENTITY_DISPACHER:
			dispacher(thread);
			break;
	}
}

void producer(Thread* producerThread)
{
	while(numProduct < 40) {
		sem_wait(threadSem[producerThread->id]);

		//把東西取走
		for(size_t i = 0; i < NUM_TYPE_MATERIAL; i++)
			desk[i] = false;

		//數量++
		producerThread->numOutput++;
		numProduct++;

		//打開dispacher 的 sem
		sem_post(threadSem[0]);
		
	}

}

void dispacher(Thread* dispacherThread)
{
	srand(time(NULL));
	while(numProduct < 40) {
		sem_wait(threadSem[producerThread->id]);

		//隨機放上東西
		for(size_t i = 0; i < 3;)
		{
			int j = 0;
			if(!desk.material[j = rand()%4]) {
				desk.material[j] = true;
				i++;
			}
		}

		//啟用sem，找擁有桌上沒有的零件的producer來啟動
		for(size_t i = 0; i < 4; i++)
		{
			//因為produce的sem是1~4 所以要+1
			if(!desk.material[i])
				sem_post(threadSem[i+1]);
		}
	}
}