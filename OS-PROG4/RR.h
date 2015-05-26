#ifndef RR_H
#define RR_H
#include "Queue.h"
class RRQueue : public Queue {
public:
	void produceQueue();
	void setTQ(int tq);
	int getTQ();
	size_t queueSize() const;
	struct process getQueue(size_t index) const;
private:
	vector<struct process> queue;
	int tq;
	bool hasNewProcess(int timeCount, size_t &index);
};

#endif