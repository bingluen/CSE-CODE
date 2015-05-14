#include "Train.h"

Train::Train(string trainNumber, string *departureTimes) {
	/* 透過set function 初始化資料 */
	setTrainNumber(trainNumber);
	setDepartureTimes(departureTimes);
}

void Train::setTrainNumber(string trainNumber)
{
	/* copy 字串到char */
	strncpy(this->trainNumber, trainNumber.c_str(), trainNumber.length()*sizeof(char));
	/* 補0 */
	this->trainNumber[trainNumber.length()] = '\0';
}
void Train::setDepartureTimes(string *departureTimes)
{
	for (size_t i = 0; i < 8; i++)
	{
		/* copy 字串到char */
		strncpy(this->departureTimes[i], departureTimes[i].c_str(), 8);
		/* 補0 */
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