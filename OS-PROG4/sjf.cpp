#include "SJF.h"

void SJFQueue::produceQueue()
{

}

size_t SJFQueue::queueSize() const
{
	return queue.size();
}

struct process SJFQueue::getQueue(size_t index) const
{
	return queue[index];
}