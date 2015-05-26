#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

struct process {
	unsigned int id;
	float arrival, burst, start, end, waiting, timeRequire;
	unsigned int execute;
	struct process* next;
};

class Queue {
	friend ostream &operator<<(ostream &, const Queue &);
public:
	virtual struct process* next() = 0;
	virtual struct process* front() const = 0;
	virtual struct process* back() const = 0;
	virtual void push(struct process*) = 0;
	virtual void execute() = 0;
	virtual float getAvgWaiting() const = 0;
};

class FCFSQueue : public Queue {
	friend ostream &operator<<(ostream &, const Queue &);
public:
	FCFSQueue();
	struct process* next();
	struct process* front() const;
	struct process* back() const;
	void push(struct process*);
	void execute();
	float getAvgWaiting() const;
private:
	struct process *pHead, *pTail, *pCurrent;
	size_t length;
	float avgWaiting;
};

class SJFQueue : public Queue {
public:
	SJFQueue();
	struct process* next();
	struct process* front() const;
	struct process* back() const;
	void push(struct process*);
	void execute();
	float getAvgWaiting() const;
private:
	struct process *pHead, *pTail, *pCurrent;
	size_t length;
	float avgWaiting;
};

class RRQueue : public Queue {
public:
	RRQueue();
	struct process* next();
	struct process* front() const;
	struct process* back() const;
	void push(struct process*);
	void setTQ(int tq);
	int getTQ();
	void execute();
	float getAvgWaiting() const;
private:
	struct process *pHead, *pTail, *pCurrent;
	size_t length;
	int TimeQuantum;
	float avgWaiting;
};

ostream &operator<<(ostream &, const Queue &);
void loadFile(string fileName, FCFSQueue& fcfs, SJFQueue& sjf, RRQueue& rr);

int main(int argc, char *argv[])
{
	FCFSQueue fcfs;
	SJFQueue sjf;
	RRQueue rr;

	if (argc > 1)
	{
		loadFile(argv[1], fcfs, sjf, rr);
	}

	fcfs.execute();

	cout << "FCFS" << endl;
	cout << fcfs << endl;

	sjf.execute();



	cout << "SJF" << endl;
	cout << sjf << endl;

	system("pause");
	return 0;
}

void loadFile(string fileName, FCFSQueue& fcfs, SJFQueue& sjf, RRQueue& rr)
{
	ifstream loadfile(fileName, ios::in);
	if (!loadfile)
	{
		cout << "Can't open file." << endl;
		exit(0);
	}

	struct process* pProcess;

	char line[100];
	string lineString;
	while (loadfile.getline(line, 100, '\n'))
	{
		lineString = line;

		/* get time quantum */
		if (strcmp(lineString.substr(0, 3).c_str(), "TQ=") == 0 || strcmp(lineString.substr(0, 3).c_str(), "tq=") == 0)
		{
			rr.setTQ(atoi(lineString.substr(3, lineString.length()).c_str()));
			continue;
		}

		/* skip #  */
		if (strcmp(lineString.substr(0, 1).c_str(), "#") == 0)
			continue;

		/* new process */
		pProcess = new struct process;
		pProcess->next = NULL;
		pProcess->waiting = pProcess->start = pProcess->end = 0;

		/* add process data */
		sscanf(line, "%d,%f,%f", &(pProcess->id), &(pProcess->arrival), &(pProcess->burst));

		/* add to queue */
		fcfs.push(pProcess);
		sjf.push(pProcess);
		//rr.push(pProcess);
	}
}

FCFSQueue::FCFSQueue()
:pHead(0), pTail(0), pCurrent(0), length(0), avgWaiting(0)
{
}

SJFQueue::SJFQueue()
: pHead(0), pTail(0), pCurrent(0), length(0), avgWaiting(0)
{
}

RRQueue::RRQueue()
: pHead(0), pTail(0), pCurrent(0), length(0), TimeQuantum(0), avgWaiting(0)
{
}

void FCFSQueue::push(struct process* pProcess)
{
	struct process* pNewProcess = new struct process;
	memcpy(pNewProcess, pProcess, sizeof(struct process));
	if (this->length == 0)
	{
		pHead = pTail = pNewProcess;
		length++;
	}
	else
	{
		/* 找適當的位置插入 */
		/* 從頭開始 */
		pCurrent = pHead;
		struct process* previous = NULL;
		while (pCurrent && pCurrent->arrival < pNewProcess->arrival)
		{
			previous = pCurrent;
			next();
		}

		pNewProcess->next = pCurrent;
		if (previous == NULL)
			pHead = pNewProcess;
		else
			previous->next = pNewProcess;

		if (pCurrent == NULL)
			pTail = pNewProcess;

		length++;
	}
}

void SJFQueue::push(struct process* pProcess)
{
	struct process* pNewProcess = new struct process;
	memcpy(pNewProcess, pProcess, sizeof(struct process));
	if (this->length == 0)
	{
		pHead = pTail = pNewProcess;
		length++;
	}
	else
	{
		/* 找適當的位置插入 */
		/* 從頭開始 */
		pCurrent = pHead;
		struct process* previous = NULL;
		float elapsedTime = 0;
		
		/**
			step1
			從head開始往下找node，直到經過時間大於等於新process的arrival time 
			每走過一個process，時間加上burst time
		*/
		while (elapsedTime < pNewProcess->arrival)
		{
			elapsedTime += pCurrent->burst;
			previous = pCurrent;
			next();
		}

		/*
			step2
			判斷是 pCurrent 和 新 process 的burst time
		*/
		bool loopFlag = true;
		while (loopFlag)
		{
			if (pCurrent->burst == pNewProcess->burst)
			{
				/*
				step 2 - 1
				早到的放前面
				*/
				if (pCurrent->arrival <= pNewProcess->arrival)
				{
					pNewProcess->next = pCurrent->next;
					pCurrent->next = pNewProcess;
				}
				else
				{
					pNewProcess->next = pCurrent;
					if (previous == NULL)
						pHead = pNewProcess;
					else
						previous->next = pNewProcess;
				}
				loopFlag = false;
			}
			else
			{
				if (pNewProcess->burst < pCurrent->burst)
				{
					if (previous == NULL)
						pHead = pNewProcess;
					else
						previous->next = pNewProcess;
					pNewProcess->next = pCurrent;
					loopFlag = false;
				}
				else
				{
					previous = pCurrent;
					next();
				}
			}
		}
		length++;
	}
}

void RRQueue::push(struct process* pProcess)
{

}

struct process* FCFSQueue::front() const
{
	return pHead;
}

struct process* SJFQueue::front() const
{
	return pHead;
}

struct process* RRQueue::front() const
{
	return pHead;
}

struct process* FCFSQueue::back() const
{
	return pTail;
}

struct process* SJFQueue::back() const
{
	return pTail;
}

struct process* RRQueue::back() const
{
	return pTail;
}

struct process* FCFSQueue::next()
{
	if (length > 0)
	{
		if (pCurrent == NULL)
			pCurrent = pHead;
		pCurrent = pCurrent->next;
	}

	return pCurrent;
}

struct process* SJFQueue::next()
{
	if (length > 0)
	{
		if (pCurrent == NULL)
			pCurrent = pHead;
		pCurrent = pCurrent->next;
	}

	return pCurrent;
}

struct process* RRQueue::next()
{
	if (length > 0)
	{
		if (pCurrent == NULL)
			pCurrent = pHead;
		pCurrent = pCurrent->next;
	}

	return pCurrent;
}

void RRQueue::setTQ(int tq)
{
	this->TimeQuantum = tq;
}

ostream &operator<<(ostream &stream, const Queue &queue)
{
	struct process* pProcess = queue.front();
	stream << "("
		<< setw(5) << "id, "
		<< setw(5) << "arrival, "
		<< setw(5) << "burst, "
		<< setw(5) << "start, "
		<< setw(5) << "end, "
		<< setw(5) << "waiting"
		<< ")" << endl;
	while (pProcess)
	{
		stream << "( " 
			<< setw(5) << pProcess->id << ", " 
			<< setw(5) << pProcess->arrival << ", "
			<< setw(5) << pProcess->burst << ", "
			<< setw(5) << pProcess->start << ","
			<< setw(5) << pProcess->end << ", "
			<< setw(5) << pProcess->waiting
			<< " )" << endl;

		pProcess = pProcess->next;
	}

	cout << "average waiting time :" << queue.getAvgWaiting() << "ms" << endl;
	return stream;
}

void FCFSQueue::execute()
{
	struct process* p;
	float timeCount = 0;
	float totalWaiting = 0;
	while (p = this->next())
	{
		p->start = timeCount;
		p->waiting = timeCount - p->arrival;
		totalWaiting += p->waiting;
		for (unsigned int i = 0; i < p->burst; i++)
			timeCount++;
		p->end = timeCount;
	}
	
	avgWaiting = totalWaiting / this->length;
}

void SJFQueue::execute()
{
	struct process* p;
	float timeCount = 0;
	float totalWaiting = 0;
	while (p = this->next())
	{
		p->start = timeCount;
		p->waiting = timeCount - p->arrival;
		totalWaiting += p->waiting;
		for (unsigned int i = 0; i < p->burst; i++)
			timeCount++;
		p->end = timeCount;
	}
	avgWaiting = totalWaiting / this->length;
}

void RRQueue::execute()
{

}

float FCFSQueue::getAvgWaiting() const
{
	return avgWaiting;
}
float SJFQueue::getAvgWaiting() const
{
	return avgWaiting;
}
float RRQueue::getAvgWaiting() const
{
	return avgWaiting;
}