#include "Queue.h"
ostream &operator<<(ostream &stream, const Queue &queue)
{
	stream << "( "
		<< setw(5) << "id" << ", "
		<< setw(5) << "start" << ", "
		<< setw(5) << "end"
		<< " )" << endl;
	for (size_t i = 0; i < queue.queueSize(); i++)
	{
		stream << "( "
			<< setw(5) << queue.getQueue(i).id << ", "
			<< setw(5) << queue.getQueue(i).start << ","
			<< setw(5) << queue.getQueue(i).end
			<< " )" << endl;
	}

	cout << "average waiting time :" << fixed << setprecision(2) << queue.getAvgWaiting() << "ms" << endl;
	return stream;
}

float Queue::getAvgWaiting() const
{
	return avgWaiting;
}

void Queue::setAvgWaiting(float time)
{
	avgWaiting = time;
}

void Queue::push(struct process newP)
{
	list.push_back(newP);
}