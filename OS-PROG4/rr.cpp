#include "RR.h"
#include <queue>

void RRQueue::produceQueue()
{
	std::queue<struct process> available, execute, finish;
	int timeCount = 0;
	int frameCount = 0;
	size_t index = 0;

	/* ����l�� */
	while (hasNewProcess(0, index))
	{
		available.push(list[index]);
		list.erase(list.begin() + index);
	}

	while (list.size() > 0 || available.size() > 0 || execute.size() > 0)
	{
		/* ��execute�����{��time require ��� */
		if (execute.size() > 0)
			execute.front().timeRequire--;

		/* �p�GTQ��F��execute����process�w�g���ݭn����ɶ�
			�A�ӥBexecute�W���F��A�����ʦ^Queue 
		*/
		if (!execute.empty() && (frameCount == 10 || execute.front().timeRequire == 0))
		{
			/* �qexecute���X */

			/* ��^available */
			if (execute.front().timeRequire > 0)
				available.push(execute.front());
			else
			{
				/* �Yexecute�W���w�g���ݭn�b����h����^available�W */
				execute.front().end = timeCount;
				finish.push(execute.front());
			}
			frameCount = 0;
			execute.pop();				
		}

		/* �Yqueue �W���F��A ��i�h */
		if (execute.empty() && available.size() > 0)
		{
			/* �p�G�O�Ĥ@������ ����start */
			available.front().start = timeCount;
			available.front().executeTimes++;
			available.front().end = timeCount + (available.front().timeRequire > tq ? tq : available.front().timeRequire);
			execute.push(available.front());
			queue.push_back(available.front());
			available.pop();
		}

		/* �Y���ɦ��観�s��process�i�ӡA��JQueue */
		while (hasNewProcess(timeCount, index))
		{
			available.push(list[index]);
			list.erase(list.begin() + index);
		}
		timeCount++;
		frameCount++;
	}

	/* compute average waiting */
	float avgWaiting = 0.0;
	int length = finish.size();
	while (finish.size() > 0)
	{
		avgWaiting += finish.front().end - (finish.front().burst % tq) - tq * (finish.front().executeTimes - 1);
		finish.pop();
	}
	avgWaiting /= length;
	setAvgWaiting(avgWaiting);

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

bool RRQueue::hasNewProcess(int timeCount, size_t &index)
{
	for (size_t i = 0; i < list.size(); i++)
	{
		if (list[i].arrival == timeCount)
		{
			index = i;
			return true;
		}
	}
	return false;
}