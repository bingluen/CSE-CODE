#ifndef QUEUE_H
#define QUEUE_H
#include "dataStructure.h"
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
class Queue {
	friend ostream &operator<<(ostream &, const Queue &);
public:
	float getAvgWaiting() const;
	void setAvgWaiting(float time);
	void push(struct process);
	virtual struct process getQueue(size_t index) const = 0;
	virtual void produceQueue() = 0;
	virtual size_t queueSize() const = 0;
protected:
	vector<struct process> list;
	float avgWaiting;
};

#endif