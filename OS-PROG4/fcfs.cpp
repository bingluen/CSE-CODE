#include "FCFS.h"

void FCFSQueue::produceQueue()
{
	while (list.size() > 0)
	{
		queue.push_back(list[findFirstCome()]);
		list.erase(list.begin() + findFirstCome());
	}

	/* ­pºâ®É¶¡ */
	int elapsedTime = 0;
	float avgWaiting = 0;;
	for (size_t i = 0; i < queue.size(); i++)
	{
		queue[i].start = elapsedTime;
		queue[i].waiting += (elapsedTime - queue[i].arrival);
		queue[i].end = elapsedTime + queue[i].burst;
		elapsedTime += queue[i].burst;
		avgWaiting += queue[i].waiting;
	}
	avgWaiting /= queue.size();

	setAvgWaiting(avgWaiting);
}

size_t FCFSQueue::queueSize() const
{
	return queue.size();
}

struct process FCFSQueue::getQueue(size_t index) const
{
	return queue[index];
}

size_t FCFSQueue::findFirstCome()
{
	size_t firstComeId = 0;
	for (size_t i = 0; i < list.size(); i++)
	{
		if (list[i].arrival < list[firstComeId].arrival)
			firstComeId = i;
	}
	return firstComeId;
}