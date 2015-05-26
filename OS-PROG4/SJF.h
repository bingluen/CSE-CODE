#ifndef SJF_H
#define SJF_H
#include "Queue.h"
class SJFQueue : public Queue {
public:
	void produceQueue();
	size_t queueSize() const;
	struct process getQueue(size_t index) const;
private:
	vector<struct process> queue;
};
#endif