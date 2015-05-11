#ifndef CRC16_H
#define CRC16_H
#include "dataPacket.h"
class CRC16 {
public:
	static DataPacket encodeCRC16(DataPacket data);
	static DataPacket decodeCRC16(DataPacket data);
	static bool isValidData(string pattern);
private:
	const static int CRC16Length;

};

const int CRC16::CRC16Length = 16;

DataPacket CRC16::encodeCRC16(DataPacket data) {
	string dividend;
	dividend = data.getData();
	
	for (size_t i = 0; i < CRC16Length; i++)
		dividend.append("0");

	for (size_t i = 0; i < data.getDataLength(); i++)
	{
		if (dividend[i] == '0')
			continue;
		for (size_t j = 0; j < CRC16Length; j++)
		{
			if ((j == 4 || j == 11 || j == 15) && i+j <= data.getDataLength())
			{
				dividend[i + j] = (dividend[i + j] == '1') ? '0' : '1';
			}
		}
	}

	DataPacket code;
	code.setData(data.getData());
	code.append(dividend.substr(data.getDataLength(), CRC16Length));

	return code;
}

DataPacket CRC16::decodeCRC16(DataPacket data) {
	string dividend;
	dividend = data.getData();

	for (size_t i = 0; i < data.getDataLength(); i++)
	{
		if (dividend[i] == '0')
			continue;
		for (size_t j = 0; j < CRC16Length; j++)
		{
			if ((j == 4 || j == 11 || j == 15) && i + j <= data.getDataLength())
			{
				dividend[i + j] = (dividend[i + j] == '1') ? '0' : '1';
			}
		}
	}

	DataPacket decodedData;
	if (isValidData(dividend)) 
	{
		decodedData.setData(data.getPattern(0, data.getDataLength() - CRC16Length));
		decodedData.setError(false);
	}
	else 
	{
		decodedData.setError(true);
		decodedData.setData(data.getPattern(0, data.getDataLength() - CRC16Length));
	}
	return decodedData;
}

bool CRC16::isValidData(string pattern)
{
	for (size_t i = pattern.length() - CRC16Length; i < pattern.length(); i++)
	{
		if (pattern[i] != '0')
			return false;
	}
	return true;
}
#endif CRC16_H