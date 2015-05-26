#include "SJF.h"

void SJFQueue::produceQueue()
{
	int offset = 0;
	while (list.size() > 0)
	{
		int index;
		if ((index = findShortBurst(offset)) >= 0)
		{
			queue.push_back(list[index]);
			offset += list[index].burst;
			list.erase(list.begin() + index);
		}
		else
		{
			offset++;
		}
		
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

size_t SJFQueue::queueSize() const
{
	return queue.size();
}

struct process SJFQueue::getQueue(size_t index) const
{
	return queue[index];
}

int SJFQueue::findShortBurst(int offset)
{

	int shortBurst = -1;
	for (size_t i = 0; i < list.size(); i++)
	{
		if (list[i].arrival <= offset)
		{
			shortBurst = i;
			break;
		}
	}
	for (size_t i = 0; i < list.size(); i++)
	{
		if (list[i].arrival <= offset && list[i].burst < list[shortBurst].burst)
		{
				shortBurst = i;
		}
	}

	return shortBurst;
}