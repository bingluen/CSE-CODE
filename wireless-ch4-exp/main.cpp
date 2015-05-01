#include <iostream>
#include <ctime>
#include <string>
#include <stdlib.h>
#include <windows.h>
#include <iomanip>

using namespace std;

namespace Hamming{
	

	const char charTable[52] = {
		'a', 'A', 'b', 'B', 'c', 'C', 'd', 'D', 'e', 'E',
		'f', 'F', 'g', 'G', 'h', 'H', 'i', 'I', 'j', 'J',
		'k', 'K', 'l', 'L', 'm', 'M', 'n', 'N', 'o', 'O',
		'p', 'P', 'q', 'Q', 'r', 'R', 's', 'S', 't', 'T',
		'u', 'U', 'v', 'V', 'w', 'W', 'x', 'X', 'y', 'Y',
		'z', 'Z'
	};

	const size_t HAMMING_TABLE_SIZE = 52;
	
	string HammingTable[HAMMING_TABLE_SIZE];

	const size_t RANDOM_SIZE = 5;

	const size_t HAMMING_LENGTH = 10;
	const string HAMMING_INIT = "0000000000";

	void initTable()
	{
		int random[RANDOM_SIZE];

		HammingTable[0] = HAMMING_INIT;

		srand(time(NULL));

		for (int i = 1; i < HAMMING_TABLE_SIZE; i++)
		{
			HammingTable[i] = HammingTable[i - 1];

			size_t randomCount = 0;

			/* get Random number */
			while (randomCount < RANDOM_SIZE)
			{
				random[randomCount++] = rand() % HAMMING_LENGTH;

				/* check duplicated */
				for (int j = 0; j < randomCount - 1; j++)
				{
					if (random[j] == random[randomCount - 1])
					{
						randomCount--;
						break;
					} /* end if */
				} /* end for - check duplicated */

			} /* end while - get Random number */

			/* inverse */
			for (int j = 0; j < RANDOM_SIZE; j++)
			{
				(HammingTable[i - 1][random[j]] == '0') ? HammingTable[i][random[j]] = '1' : HammingTable[i][random[j]] = '0';
			}/* end for - inverse */

			/* check duplicated of hamming code */
			for (int j = 0; j < i; j++)
			{
				if (HammingTable[j] == HammingTable[i])
				{
					i--;
					break;
				}
			}/* end for - check duplicated of hamming code  */

		}/* end for */
	}/* end init function */

	int getHammingIndex(char character)
	{
		for (int i = 0; i < HAMMING_TABLE_SIZE; i++)
		{
			if (charTable[i] == character)
				return i;
		}
		return -1;
	}

	int getHammingIndex(string hammingCode)
	{
		for (int i = 0; i < HAMMING_TABLE_SIZE; i++)
		{
			if (HammingTable[i] == hammingCode)
				return i;
		}
		return -1;
	}

	bool isHammingCode(string pattern)
	{
		for (int i = 0; i < HAMMING_TABLE_SIZE; i++)
		{
			if (HammingTable[i] == pattern)
				return true;
		}

		return false;
	}

	void covertToHammingCode(string messages, int* &data, int &dataLength)
	{
		int pattern[HAMMING_LENGTH] = { 0 };

		data = new int[messages.length() * Hamming::HAMMING_LENGTH];
		dataLength = 0;

		for (int i = 0; i < messages.length(); i++)
		{
			int indexOfCharacter = Hamming::getHammingIndex(messages[i]);

			/* map to hamming code for character */
			for (int j = 0; j < Hamming::HAMMING_LENGTH; j++)
			{
				pattern[j] = Hamming::HammingTable[indexOfCharacter][j] - '0';
			}

			/* copy hamming code to data */
			memcpy(data + dataLength, pattern, Hamming::HAMMING_LENGTH * sizeof(int));
			dataLength += Hamming::HAMMING_LENGTH;
		}

	}

	void errorCorrection(int *&data, int dataLength, int *&code, int codeLength)
	{
		int pattern[HAMMING_LENGTH];

		memcpy(data, code, dataLength * sizeof(int));

		for (int i = 0; i < dataLength; i += HAMMING_LENGTH)
		{
			for (int j = 0; j < HAMMING_LENGTH; j++)
			{
				pattern[j] = data[i + j];
			}

			/* convert to String */
			string patternString;
			for (int j = 0; j < HAMMING_LENGTH; j++)
			{
				char buffer[10];
				sprintf(buffer, "%d", pattern[j]);
				patternString += buffer;
			}/* end for - convert to String */

			if (!isHammingCode(patternString))
			{
				/* calculate the hamming distance between error occured binary string and each hamming code in hamming table */
				int dist[HAMMING_TABLE_SIZE] = { 0 };

				for (int j = 0; j < HAMMING_TABLE_SIZE; j++)
				{
					for (int k = 0; k < HAMMING_LENGTH; k++)
					{
						if (patternString[k] != HammingTable[j][k])
						{
							dist[j]++;
						} /* end if */
					} /* end for */
				} /* end for */

				int hammingIndex = 0;
				int minMistakes = dist[0];

				for (int j = 1; j < HAMMING_TABLE_SIZE; j++)
				{
					if (dist[j] < minMistakes)
					{
						minMistakes = dist[hammingIndex = j];
					}
				}

				patternString = HammingTable[hammingIndex];

				for (int j = 0; j < HAMMING_LENGTH; j++)
				{
					data[i + j] = patternString[j] - '0';
				}

			} /* end if - isHammingCode */
		}
	}

};

namespace CRC16 {
	int const CRC16Length = 16;

	void encodeCRC16(int *&data, int dataLength, int *&code, int &codeLength)
	{
		codeLength = dataLength + CRC16Length;

		int *dividend = new int[codeLength];

		/* copy data */
		memcpy(dividend, data, dataLength * sizeof(int));

		/* fill with zero */
		memset(dividend + dataLength, 0, CRC16Length * sizeof(int));

		/* do CRC-16 encode */
		for (int i = 0; i < dataLength; i++)
		{
			/* skip if bit is zero */
			if (dividend[i] == 0)
				continue;

			for (int j = 0; j <= CRC16Length; j++)
			{
				if (j == 0 || j == 4 || j == 11 || j == 16)
				{
					dividend[i + j] = (dividend[i + j] == 1) ? 0 : 1;
				}
			}

			/* debug
			for (int i = 0; i < codeLength; i++)
			{
				cout << dividend[i];
			}
			cout << endl;
			debug */

		}
		

		code = new int[codeLength];

		memcpy(code, data, dataLength * sizeof(int));

		memcpy(code + dataLength, dividend + dataLength, CRC16Length * sizeof(int));

		delete[] dividend;
	}

	bool isValidData(int *&data, int codeLength)
	{
		for (int i = codeLength - CRC16Length; i < codeLength; i++)
		{
			if (data[i] != 0)
				return false;
		}
		return true;
	}

	void decodeCRC16(int *&data, int &dataLength, int *&code, int codeLength)
	{
		dataLength = codeLength - CRC16Length;

		int *dividend = new int[codeLength];

		/* copy data */
		memcpy(dividend, code, codeLength * sizeof(int));

		/* decodeing */
		for (int i = 0; i < codeLength; i++)
		{
			if (dividend[i] == 0)
				continue;

			for (int j = 0; j <= CRC16Length; j++)
			{
				if (j == 0 || j == 4 || j == 11 || j == 16)
				{
					dividend[i + j] = (dividend[i + j] == 1) ? 0 : 1;
				}
			}/* end for - XOR */
		}/* end for - decodeing */

		//data = new int[dataLength];

		/* CRC Check Data is correct or not */
		if (isValidData(dividend, codeLength))
		{
			/* copy data if data is correct */
			memcpy(data, code, dataLength * sizeof(int));
		}
	}
};

void noiseGenerator(int *&code, int codeLength, int errorLength)
{
	if (errorLength > codeLength)
		return;

	int *randomPosition = new int[errorLength];

	size_t randomCount = 0;

	/* generate noise position*/
	while (randomCount < errorLength)
	{
		randomPosition[randomCount++] = rand() % errorLength;

		/* check duplicate */
		for (int i = 0; i < randomCount - 1; i++)
		{
			if (randomPosition[i] == randomPosition[randomCount - 1])
			{
				randomCount--;
				break;
			}
		}
	}

	/* add noise */
	for (int i = 0; i < errorLength; i++)
	{
		code[randomPosition[i]] = (code[randomPosition[i]] == 1) ? 0 : 1;
	}
	
}

void printMessages(int *&data, int dataLength, int *&code, int codeLength)
{
	if (!CRC16::isValidData(data, codeLength))
	{
		Hamming::errorCorrection(data, dataLength, code, codeLength);
	}

	int pattern[Hamming::HAMMING_LENGTH];
	string s, messages;

	
	for (int i = 0; i < dataLength; i+= Hamming::HAMMING_LENGTH)
	{
		/* split pattern */
		for (int j = 0; j < Hamming::HAMMING_LENGTH; j++)
		{
			pattern[j] = data[i + j];
		}

		string patternString;

		for (int j = 0; j < Hamming::HAMMING_LENGTH; j++)
		{
			char buffer[10];
			sprintf(buffer, "%d", pattern[j]);
			patternString += buffer;
		}

		messages += Hamming::charTable[Hamming::getHammingIndex(patternString)];
	}

	cout << messages << endl;
}

void printPattern(int *&data, int dataLength)
{
	for (int i = 0; i < dataLength; i++)
	{
		cout << data[i];
	}
	cout << endl;
}

int main()
{
	string messages;
	int *data = 0, *code = 0;
	int dataLength, codeLength;

	Hamming::initTable();

	cout << "input messages whiche want to send" << endl;
	cin >> messages;

	cout << endl;
	
	cout << "Transmitting messages in error free " << endl;
	cout << "Sending..." << endl;
	Hamming::covertToHammingCode(messages, data, dataLength);
	CRC16::encodeCRC16(data, dataLength, code, codeLength);

	Sleep(5);

	cout << "Receiving..." << endl;
	CRC16::decodeCRC16(data, dataLength, code, codeLength);
	
	printMessages(data, dataLength, code, codeLength);

	cout << endl;
	

	cout << "Transmitting messages in noise " << endl;
	cout << "Sending..." << endl;
	Hamming::covertToHammingCode(messages, data, dataLength);
	CRC16::encodeCRC16(data, dataLength, code, codeLength);

	Sleep(5);

	cout << endl;

	cout << setw(25) << "before Noise : ";

	printPattern(code, codeLength);

	noiseGenerator(code, codeLength, 5);

	cout << setw(25) << "After Noise : ";

	printPattern(code, codeLength);

	cout << endl;

	cout << "Receiving..." << endl;
	CRC16::decodeCRC16(data, dataLength, code, codeLength);

	printMessages(data, dataLength, code, codeLength);

	getchar();
	return 0;
}