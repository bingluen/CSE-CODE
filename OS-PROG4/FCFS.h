#ifndef FCFS_H
#define FCFS_H
#include "Queue.h"
class FCFSQueue : public Queue {
public:
	void produceQueue();
	size_t queueSize() const;
	struct process getQueue(size_t index) const;
private:
	size_t findFirstCome();
	vector<struct process> queue;
};
#endif