#ifndef PROCESS_H
#define PROCESS
struct process {
	unsigned int id;
	int executeTimes;
	int arrival, burst, start, end, waiting, timeRequire;
};
#endif