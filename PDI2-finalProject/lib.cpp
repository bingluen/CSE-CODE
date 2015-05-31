#include "lib.h"
bool isNumber(string str)
{
	for (size_t i = 0; i < str.length(); i++)
	{
		if (!isdigit(str[i]))
			return false;
	}
	return true;
}
bool isNumber(char *str)
{
	for (size_t i = 0; i < strlen(str); i++)
	{
		if (!isdigit(str[i]))
			return false;
	}
	return true;
}