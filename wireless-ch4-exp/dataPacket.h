#ifndef DATAPACKET_H
#define DATAPACKET_H
#include <string>
#include <iostream>
#include <ctime>

using namespace std;
class DataPacket {
	friend ostream &operator<<(ostream &output, DataPacket &dataPacket);
public:
	void setData(string data);
	string getData();
	size_t getDataLength();
	void append(string pattern);
	string getPattern(size_t pos,size_t length);
	bool isError();
	void setError(bool );
	void noiseGenerator(size_t noiseLength);
private:
	string data;
	bool error;
};

void DataPacket::setData(string data)
{
	this->data = data;
}

string DataPacket::getData()
{
	return this->data;
}

size_t DataPacket::getDataLength()
{
	return this->data.length();
}

void DataPacket::append(string pattern)
{
	this->data.append(pattern);
}

string DataPacket::getPattern(size_t pos, size_t length)
{
	return this->data.substr(pos, length);
}

bool DataPacket::isError() {
	return error;
}
void DataPacket::setError(bool v) {
	error = v;
}

void DataPacket::noiseGenerator(size_t noiseLength) {
	if (noiseLength > data.length())
		return;
	int *randomPosition = new int[noiseLength];

	size_t randomCount = 0;

	srand(time(NULL));

	/* generate noise position*/
	while (randomCount < noiseLength)
	{
		randomPosition[randomCount++] = rand() % data.length();

		/* check duplicate */
		for (size_t i = 0; i < randomCount - 1; i++)
		{
			if (randomPosition[i] == randomPosition[randomCount - 1])
			{
				randomCount--;
				break;
			}
		}
	}

	/* add noise */
	for (size_t i = 0; i < noiseLength; i++)
	{
		data[randomPosition[i]] = (data[randomPosition[i]] == '1') ? '0' : '1';
	}
}

ostream &operator<<(ostream &output, DataPacket &dataPacket) {
	output << dataPacket.getData();
	return output;
}
#endif