#include <iostream>
#include <string>
#include <iomanip>

#include "crc16.h"
#include "dataPacket.h"
#include "hamming.h"

using namespace std;

int main() {

	Hamming hammingCode;

	string messages;

	cout << "input messages which want to send" << endl;
	cin >> messages;

	cout << endl;

	/* Packaged packet */
	DataPacket packet;
	/* convert to hamming code */
	packet = hammingCode.convertToHammingCode(messages);
	cout << "Hamming Code \n\t" << packet << endl;

	/* CRC16 encode */
	packet = CRC16::encodeCRC16(packet);
	cout << "Data sent \n\t" << packet << endl;

	cout << "Transmitting messages in error free " << endl;
	cout << "Sending..." << endl;


	cout << endl;
	cout << endl;

	cout << "Receiving..." << endl;

	DataPacket receivedData;

	receivedData = packet;

	cout << "Data received \n\t" << receivedData << endl;
		
	/* CRC16 decode */
	receivedData = CRC16::decodeCRC16(receivedData);

	cout << "CRC16 Decode \n\t" << receivedData << endl;

	/* Hamming decode */
	string decodedMessages = hammingCode.decodeHammingCode(receivedData);
	
	cout << "Received Messages: \t" << decodedMessages << endl;

	cout << endl;
	cout << endl;

	cout << "Transmitting messages with noise " << endl;
	cout << "Sending..." << endl;


	cout << endl;
	cout << endl;

	cout << "Receiving..." << endl;
	/* generator noise */

	DataPacket receivedDataWithNoise;

	receivedDataWithNoise = packet;

	receivedDataWithNoise.noiseGenerator(5);

	cout << "Data received \n\t" << receivedDataWithNoise << endl;

	/* CRC16 decode */
	receivedDataWithNoise = CRC16::decodeCRC16(receivedDataWithNoise);

	cout << "CRC16 Decode \n\t" << receivedDataWithNoise << endl;

	if (receivedDataWithNoise.isError())
	{
		cout << "Received Messages(with noise): \t" << hammingCode.decodeHammingCode(receivedDataWithNoise) << endl;
		receivedDataWithNoise = hammingCode.errorCorrection(receivedDataWithNoise);
		cout << "Error correction \n\t" << receivedDataWithNoise << endl;
	}

	/* Hamming decode */
	string decodedMessagesWithNoise = hammingCode.decodeHammingCode(receivedDataWithNoise);

	cout << "Received Messages: \t" << decodedMessagesWithNoise << endl;


	system("pause");
	return 0;
}