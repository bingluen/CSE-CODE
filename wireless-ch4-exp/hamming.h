#ifndef HAMMING_H
#define HAMMING_H

#include <string>
#include "dataPacket.h"

using namespace std;

const size_t HAMMING_TABLE_SIZE = 52;
const size_t HAMMING_LENGTH = 20;
const size_t HAMMING_RANDOM_SIZE = 10;
const string HAMMING_INIT = "00000000000000000000";

class Hamming{
public:
	Hamming();
	int getHammingIndex(char character);
	int getHammingIndex(string HammingCode);
	bool isHammingCode(string pattern);
	string getHammingCode(char character);
	DataPacket convertToHammingCode(string messages);
	DataPacket errorCorrection(DataPacket dataPacket);
	string decodeHammingCode(DataPacket dataPacket);
private:
	const static char charTable[HAMMING_TABLE_SIZE];
	string HammingTable[HAMMING_TABLE_SIZE];
	int HammingTableCompare(size_t index, string pattern);
};


const char Hamming::charTable[HAMMING_TABLE_SIZE] = {
	'a', 'A', 'b', 'B', 'c', 'C', 'd', 'D', 'e', 'E',
	'f', 'F', 'g', 'G', 'h', 'H', 'i', 'I', 'j', 'J',
	'k', 'K', 'l', 'L', 'm', 'M', 'n', 'N', 'o', 'O',
	'p', 'P', 'q', 'Q', 'r', 'R', 's', 'S', 't', 'T',
	'u', 'U', 'v', 'V', 'w', 'W', 'x', 'X', 'y', 'Y',
	'z', 'Z'
};

Hamming::Hamming()
{
	int random[HAMMING_RANDOM_SIZE] = { 0 };

	HammingTable[0] = HAMMING_INIT;

	srand(time(NULL));

	for (size_t i = 1; i < HAMMING_TABLE_SIZE; i++)
	{
		HammingTable[i] = HammingTable[i - 1];

		size_t randomCount = 0;

		/* get Random number */
		while (randomCount < HAMMING_RANDOM_SIZE)
		{
			random[randomCount++] = rand() % HAMMING_LENGTH;

			/* check duplicated */
			for (size_t j = 0; j < randomCount - 1; j++)
			{
				if (random[j] == random[randomCount - 1])
				{
					randomCount--;
					break;
				} /* end if */
			} /* end for - check duplicated */

		} /* end while - get Random number */

		/* inverse */
		for (size_t j = 0; j < HAMMING_RANDOM_SIZE; j++)
		{
			(HammingTable[i - 1][random[j]] == '0') ? HammingTable[i][random[j]] = '1' : HammingTable[i][random[j]] = '0';
		}/* end for - inverse */

		/* check duplicated of hamming code */
		for (size_t j = 0; j < i; j++)
		{
			if (HammingTable[j] == HammingTable[i])
			{
				i--;
				break;
			}
		}/* end for - check duplicated of hamming code  */

	}/* end for */
}

int Hamming::getHammingIndex(char character) {
	for (size_t i = 0; i < HAMMING_TABLE_SIZE; i++)
	{
		if (charTable[i] == character)
			return i;
	}
	return -1;
}

int Hamming::getHammingIndex(string HammingCode) {
	for (size_t i = 0; i < HAMMING_TABLE_SIZE; i++)
	{
		if (this->HammingTable[i] == HammingCode)
			return i;
	}
	return -1;
}

bool Hamming::isHammingCode(string pattern) {
	for (size_t i = 0; i < HAMMING_TABLE_SIZE; i++)
	{
		if (HammingTable[i] == pattern)
			return true;
	}
	return false;
}

string Hamming::getHammingCode(char character){
	return HammingTable[getHammingIndex(character)];
}

DataPacket Hamming::convertToHammingCode(string messages) {
	DataPacket data;
	for (size_t i = 0; i < messages.length(); i++)
	{
		cout << messages[i] << " == " << getHammingCode(messages[i]) << endl;
		data.append(getHammingCode(messages[i]));
	}
	return data;
}

DataPacket Hamming::errorCorrection(DataPacket dataPacket) {
	DataPacket correctData;
	for (size_t i = 0; i < dataPacket.getDataLength() / HAMMING_LENGTH; i++){
		string pattern = dataPacket.getPattern(i*HAMMING_LENGTH, HAMMING_LENGTH);
		if (!isHammingCode(pattern)) {
			/* calculate the hamming distance between error occured binary string and each hamming code in hamming table */
			int dist[HAMMING_TABLE_SIZE] = { 0 };
			for (size_t i = 0; i < HAMMING_TABLE_SIZE; i++)
				dist[i] = HammingTableCompare(i, pattern);

			/* find minimum mistake */
			int minMistakeHammingCode = 0;
			for (size_t i = 0; i < HAMMING_TABLE_SIZE; i++)
			{
				if (dist[i] < dist[minMistakeHammingCode])
					minMistakeHammingCode = i;
			}

			correctData.append(HammingTable[minMistakeHammingCode]);
		}
		else 
		{
			correctData.append(pattern);
		}
	}

	return correctData;
}

int Hamming::HammingTableCompare(size_t index, string pattern) {
	int diffNum = 0;
	for (size_t i = 0; i < HAMMING_LENGTH; i++) {
		if (HammingTable[index][i] != pattern[i])
			diffNum++;
	}
	return diffNum;
}

string Hamming::decodeHammingCode(DataPacket dataPacket) {
	string decodedData;
	for (size_t i = 0; i < dataPacket.getDataLength() / HAMMING_LENGTH; i++)
	{
		string pattern = dataPacket.getPattern(i*HAMMING_LENGTH, HAMMING_LENGTH);
		cout << pattern << " == " << charTable[getHammingIndex(pattern)] << endl;
		decodedData += charTable[getHammingIndex(pattern)];
	}
	return decodedData;
}

#endif