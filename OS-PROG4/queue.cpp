#include "Queue.h"
ostream &operator<<(ostream &stream, const Queue &queue)
{
	stream << "("
		<< setw(5) << "id, "
		<< setw(5) << "arrival, "
		<< setw(5) << "burst, "
		<< setw(5) << "start, "
		<< setw(5) << "end, "
		<< setw(5) << "waiting, "
		<< setw(5) << "execute"
		<< ")" << endl;
	for (size_t i = 0; i < queue.queueSize(); i++)
	{
		stream << "( "
			<< setw(5) << queue.getQueue(i).id << ", "
			<< setw(5) << queue.getQueue(i).arrival << ", "
			<< setw(5) << queue.getQueue(i).burst << ", "
			<< setw(5) << queue.getQueue(i).start << ","
			<< setw(5) << queue.getQueue(i).end << ", "
			<< setw(5) << queue.getQueue(i).waiting << ", "
			<< setw(5) << queue.getQueue(i).timeRequire
			<< " )" << endl;
	}

	cout << "average waiting time :" << queue.getAvgWaiting() << "ms" << endl;
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