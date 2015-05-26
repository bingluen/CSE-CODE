#include "RR.h"

void RRQueue::produceQueue()
{

}

size_t RRQueue::queueSize() const
{
	return queue.size();
}

struct process RRQueue::getQueue(size_t index) const
{
	return queue[index];
}

void RRQueue::setTQ(int tq)
{
	this->tq = tq;
}

int RRQueue::getTQ()
{
	return this->tq;
}