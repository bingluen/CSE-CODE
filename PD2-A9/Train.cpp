#include "Train.h"

Train::Train(string trainNumber, string *departureTimes) {
	/* �z�Lset function ��l�Ƹ�� */
	setTrainNumber(trainNumber);
	setDepartureTimes(departureTimes);
}

void Train::setTrainNumber(string trainNumber)
{
	/* copy �r���char */
	strncpy(this->trainNumber, trainNumber.c_str(), trainNumber.length()*sizeof(char));
	/* ��0 */
	this->trainNumber[trainNumber.length()] = '\0';
}
void Train::setDepartureTimes(string *departureTimes)
{
	for (size_t i = 0; i < 8; i++)
	{
		/* copy �r���char */
		strncpy(this->departureTimes[i], departureTimes[i].c_str(), 8);
		/* ��0 */
		this->departureTimes[i][7] = '\0';
	}
}
string Train::getTrainNumber()
{
	return trainNumber;
}

string * Train::getDepartureTimes(string *saving)
{
	for (size_t i = 0; i < 8; i++)
	{
		saving[i] = this->departureTimes[i];
	}

	return saving;
}