#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <semaphore.h>
#include <time.h>

using namespace std;

/* define constant */

const unsigned short int MATERIAL_BATTERY = 1;
const unsigned short int MATERIAL_SENSOR = 2;
const unsigned short int MATERIAL_WIFI = 3;
const unsigned short int MATERIAL_CRAWLER = 4;
const char MATERIAL_NAME[][8] = {"Battery", "Sensor", "Wifi", "Carwler"};

const unsigned short int IDENTITY_PRODUCER = 0;
const unsigned short int IDENTITY_DISPATCHER = 1;

const unsigned short int NUM_TYPE_MATERIAL = 4;

/* define data structure */

typedef struct {
	bool material[NUM_TYPE_MATERIAL];
} Desk;


typedef struct {
	size_t id;
	unsigned short int identity;
	unsigned short int heldMaterials;
	unsigned short int numOutput;
} Thread;


/* Function prototype */
void basic();
void advance();
void *threading(void*);
void producer(Thread*);
void dispatcher(Thread*);

void producerAdvance(Thread*);
void dispatcherAdvance(Thread*);
void *threadingAdvance(void*);

int compareNumOutput(const void*, const void*);

/* Declare global variable */

Desk desk;
sem_t threadSem[NUM_TYPE_MATERIAL + 1];
int numProduct = 0;

sem_t ADV_threadSemProducer[NUM_TYPE_MATERIAL];
sem_t ADV_threadSemDispatcher[2];
int ADV_materialOnDesk;

int main(int argc, char *argv[])
{

	if(argc > 1)
	{
		switch(atoi(argv[1]))
		{
			case 2:
				advance();
				break;
			case 1:
			default:
				basic();
				break;
		}
	} else {
		basic();
	}
	

	return 0;
}

void basic()
{

	//cout << "[Debug]" << "準備thread" << endl;

	/* 5個thread的資料 */
	Thread thread[5];
	pthread_t thread_id[5];
	pthread_attr_t thread_attr[5];

	/* setting thread */
	//Dispatcher
	sem_init(&threadSem[0], 0, 0);
	thread[0].identity = IDENTITY_DISPATCHER;
	thread[0].id = 0;
	thread[0].heldMaterials = 0;
	//Producer
	for(size_t i = 1; i < 5; i++)
	{
		sem_init(&threadSem[i], 0, 0);
		thread[i].id = i;
		thread[i].identity = IDENTITY_PRODUCER;
		thread[i].heldMaterials = i;
		thread[i].numOutput = 0;
	}

	/* thread 設定印出 
	for(size_t i = 0; i < 5; i++)
	{
		cout << "[id = " << thread[i].id << "] identity = " << thread[i].identity 
		<< " ,heldMaterials = " << thread[i].heldMaterials
		<< " ,numOutput = " << thread[i].numOutput << endl;
	}*/

	//cout << "[Debug]" << "產生thread" << endl;
	/* create thread */
	for(size_t i = 0; i < 5; i++)
	{
		pthread_attr_init(thread_attr+i);
		pthread_create(thread_id+i, thread_attr+i, threading, reinterpret_cast<void *> (thread+i));
	}

	/* thread 設定印出 
	for(size_t i = 0; i < 5; i++)
	{
		cout << "[id = " << thread[i].id << "] identity = " << thread[i].identity 
		<< " ,heldMaterials = " << thread[i].heldMaterials
		<< " ,numOutput = " << thread[i].numOutput << endl;
	}*/

	/* open dispatcher */
	sem_post(&threadSem[0]);

	//cout << "[Debug]" << "等待thread" << endl;
	for(size_t i = 0; i < 5; i++)
	{
		pthread_join(*(thread_id+i), NULL);
	}

	/* 總結 */
	qsort(thread+1, 4, sizeof(Thread), compareNumOutput);
	cout << "-----------------" << endl;
	for(size_t i = 1; i < 5; i++)
	{
		cout << "Producer(" << MATERIAL_NAME[thread[i].heldMaterials - 1]
			<< ") :" << thread[i].numOutput << " Robot(s)" << endl;
	}
}

void* threading(void* threadContext)
{
	Thread *thread = ( reinterpret_cast<Thread* > (threadContext) );
	
	switch(thread->identity)
	{
		case IDENTITY_PRODUCER:
			producer(thread);
			break;
		case IDENTITY_DISPATCHER:
			dispatcher(thread);
			break;
	}
}

void producer(Thread* producerThread)
{
	while(true) {
		sem_wait(&threadSem[producerThread->id]);

		if (numProduct >= 40)
			break;

		//把東西取走
		for(size_t i = 0; i < NUM_TYPE_MATERIAL; i++)
			desk.material[i] = false;

		//數量++
		producerThread->numOutput++;
		numProduct++;

		cout << "Producer(" 
			<< MATERIAL_NAME[producerThread->heldMaterials - 1] 
			<< ") : OK, " << producerThread->numOutput << " Robot(s), Total: " 
			<< numProduct << " Robot(s)." << endl;

		//打開dispatcher 的 sem
		//只有在numProduct < 40 才開
		if(numProduct < 40)
		{
			sem_post(&threadSem[0]);
		} else {
		//若 numProduct == 40
		//同時喚醒所有block的thread 讓他們離開
			for(size_t i = 0; i < 5; i++)
			{
				int semVal;
				sem_getvalue(&threadSem[i], &semVal);
				if(semVal >= 0)
				{
					sem_post(&threadSem[i]);
				}
			}
		}
		
		
	}

}

void dispatcher(Thread* dispatcherThread)
{
	srand(time(NULL));
	while(true) {
		sem_wait(&threadSem[dispatcherThread->id]);

		if (numProduct >= 40)
			break;

		//隨機放上東西
		for(size_t i = 0; i < 3;)
		{
			int j = 0;
			if(!desk.material[j = rand()%4]) {
				desk.material[j] = true;
				i++;
				cout << "Dispatcher: " << MATERIAL_NAME[j] << endl;
			}
		}

		//啟用sem，找擁有桌上沒有的零件的producer來啟動
		for(size_t i = 0; i < 4; i++)
		{
			//因為produce的sem是1~4 所以要+1
			if(!desk.material[i])
				sem_post(&threadSem[i+1]);
		}
	}
}

void advance() {
	/* 6個thread的資料 */
	Thread thread_producer[4];
	Thread thread_dispatcher[2];
	pthread_t thread_id[6];
	pthread_attr_t thread_attr[6];

	/* 設定Dispatcher */
	//A
	thread_dispatcher[0].id = 0;
	thread_dispatcher[0].identity = IDENTITY_DISPATCHER;
	thread_dispatcher[0].heldMaterials = MATERIAL_CRAWLER; //不發的
	//B
	thread_dispatcher[1].id = 1;
	thread_dispatcher[1].identity = IDENTITY_DISPATCHER;
	thread_dispatcher[1].heldMaterials = MATERIAL_SENSOR; //不發的

	/* 設定Producer */
	for(size_t i = 0; i < 4; i++)
	{
		thread_producer[i].id = i;
		thread_producer[i].identity = IDENTITY_PRODUCER;
		thread_producer[i].heldMaterials = i+1;
		thread_producer[i].numOutput = 0;
	}

	/* init pthread attr */
	for(size_t i = 0; i < 6; i++)
		pthread_attr_init(thread_attr+i);

	/* Create thread */
	//Dispatcher
	for(size_t i = 0; i < 2; i++)
		pthread_create(thread_id+i, thread_attr+i, threadingAdvance, reinterpret_cast<void *> (thread_dispatcher+i));
	//Producer
	for(size_t i = 0; i < 4; i++)
		pthread_create(thread_id+i+2, thread_attr+i+2, threadingAdvance, reinterpret_cast<void *> (thread_producer+i));


	//先隨機開一個dispatcher
	sem_post(&ADV_threadSemDispatcher[rand()%2]);

	/* Waiting Thread */
	for(size_t i = 0; i < 6; i++)
	{
		pthread_join(*(thread_id+i), NULL);
	}

	/* 總結 */
	qsort(thread_producer, 4, sizeof(Thread), compareNumOutput);
	cout << "-----------------" << endl;
	for(size_t i = 0; i < 4; i++)
	{
		cout << "Producer(" << MATERIAL_NAME[thread_producer[i].heldMaterials - 1]
			<< ") :" << thread_producer[i].numOutput << " Robot(s)" << endl;
	}
}

void *threadingAdvance(void* threadContext)
{
	Thread *thread = ( reinterpret_cast<Thread* > (threadContext) );
	
	switch(thread->identity)
	{
		case IDENTITY_PRODUCER:
			producerAdvance(thread);
			break;
		case IDENTITY_DISPATCHER:
			dispatcherAdvance(thread);
			break;
	}
}

void producerAdvance(Thread* thread_producer) 
{
	srand(time(NULL));
	while(true) {
		sem_wait(&ADV_threadSemProducer[thread_producer->id]);

		if (numProduct >= 40)
			break;

		//撿零件
		for(size_t i = 0; i < NUM_TYPE_MATERIAL; i++)
			desk.material[i] = false;

		//數量++
		thread_producer->numOutput++;
		numProduct++;

		cout << "Producer(" 
			<< MATERIAL_NAME[thread_producer->heldMaterials - 1] 
			<< ") : OK, " << thread_producer->numOutput << " Robot(s), Total: " 
			<< numProduct << " Robot(s)." << endl;

		if (numProduct < 40)
		{
			//隨機呼叫dispatcher
			sem_post(&ADV_threadSemDispatcher[rand()%2]);
		} else {
			//喚醒所有block的thread
			
			//dispatcher
			for(size_t i = 0; i < 2; i++)
				sem_post(&ADV_threadSemDispatcher[i]);
			//producer
			for(size_t i = 0; i < 4; i++) {
				int semVal;
				sem_getvalue(&ADV_threadSemProducer[i], &semVal);
				if(semVal >= 0)
				{
					sem_post(&ADV_threadSemProducer[i]);
				}
			}
				
		}


	}
}

void dispatcherAdvance(Thread* thread_dispatcher)
{
	
	srand(time(NULL));
	while(true) {
		sem_wait(&ADV_threadSemDispatcher[thread_dispatcher->id]);

		if (numProduct >= 40)
			break;

		//隨機選一個自己可以給的，且桌上沒有的
		int option;
		while( (option = rand()%4) + 1 == thread_dispatcher->heldMaterials 
			|| desk.material[option] == true);

		char id[][2] = { "A", "B"};

		//放上零件
		cout << "Dispatcher(" << id[thread_dispatcher->id] << "): " << MATERIAL_NAME[option] << endl;
		desk.material[option] = true;

		//數量++
		ADV_materialOnDesk++;

		//桌上否有三件零件了
		if (ADV_materialOnDesk < 3)
		{
			//零件沒發完，再隨機選一個dispatcher
			sem_post(&ADV_threadSemDispatcher[rand()%2]);
		} else {
			//找擁有桌上沒有的零件的producer啟動
			ADV_materialOnDesk = 0;
			for(size_t i = 0; i < 4; i++)
			{
				if (!desk.material[i])
				{
					sem_post(&ADV_threadSemProducer[i]);
				}
			}
		}
	}
}

int compareNumOutput(const void* a, const void* b)
{
	return ((Thread*)a)->numOutput - ((Thread*)b)->numOutput;
}