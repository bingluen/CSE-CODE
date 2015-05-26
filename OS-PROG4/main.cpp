#include "SJF.h"
#include "FCFS.h"
#include "RR.h"
#include <fstream>
#include <string>
#include <stdlib.h>
#include <string.h>

using namespace std;



void loadFile(char *fileName, FCFSQueue& fcfs, SJFQueue& sjf, RRQueue& rr);

int main(int argc, char *argv[])
{
	FCFSQueue fcfs;
	SJFQueue sjf;
	RRQueue rr;

	if (argc > 1)
	{
		loadFile(argv[1], fcfs, sjf, rr);
	}

	cout << "FCFS" << endl;
	cout << fcfs << endl;

	cout << "SJF" << endl;
	cout << sjf << endl;

	cout << "RR" << endl;
	cout << rr << endl;
	return 0;
}

void loadFile(char* fileName, FCFSQueue& fcfs, SJFQueue& sjf, RRQueue& rr)
{
	ifstream loadfile(fileName, ios::in);
	if (!loadfile)
	{
		cout << "Can't open file." << endl;
		exit(0);
	}

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
		struct process newProcess;

		/* add process data */
		sscanf(line, "%d,%d,%d", &(newProcess.id), &(newProcess.arrival), &(newProcess.burst));

		newProcess.timeRequire = newProcess.burst;
		newProcess.waiting = newProcess.executeTimes = 0;

		/* add to queue */
		fcfs.push(newProcess);
		sjf.push(newProcess);
		rr.push(newProcess);
	}
	fcfs.produceQueue();
	sjf.produceQueue();
	rr.produceQueue();
}

