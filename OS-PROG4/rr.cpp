#include "RR.h"
#include <queue>

void RRQueue::produceQueue()
{
	std::queue<struct process> available, execute, finish;
	int timeCount = 0;
	int frameCount = 0;
	size_t index = 0;

	/* 先初始化 */
	while (hasNewProcess(0, index))
	{
		available.push(list[index]);
		list.erase(list.begin() + index);
	}

	while (list.size() > 0 || available.size() > 0 || execute.size() > 0)
	{
		/* 把execute中的程式time require 減少 */
		if (execute.size() > 0)
			execute.front().timeRequire--;

		/* 如果TQ到了或execute中的process已經不需要執行時間
			，而且execute上有東西，先移動回Queue 
		*/
		if (!execute.empty() && (frameCount == 10 || execute.front().timeRequire == 0))
		{
			/* 從execute移出 */

			/* 丟回available */
			if (execute.front().timeRequire > 0)
				available.push(execute.front());
			else
			{
				/* 若execute上的已經不需要在執行則不丟回available上 */
				execute.front().end = timeCount;
				finish.push(execute.front());
			}
			frameCount = 0;
			execute.pop();				
		}

		/* 若queue 上有東西， 放進去 */
		if (execute.empty() && available.size() > 0)
		{
			/* 如果是第一次執行 紀錄start */
			available.front().start = timeCount;
			available.front().executeTimes++;
			available.front().end = timeCount + (available.front().timeRequire > tq ? tq : available.front().timeRequire);
			execute.push(available.front());
			queue.push_back(available.front());
			available.pop();
		}

		/* 若此時此刻有新的process進來，丟入Queue */
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