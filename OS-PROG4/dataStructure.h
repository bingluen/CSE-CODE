#ifndef PROCESS_H
#define PROCESS
struct process {
	unsigned int id;
	float arrival, burst, start, end, waiting, timeRequire;
};
#endif