#include "exception.h"
#include <iostream>
#include <string>

using namespace std;

bool isNumber(char*, size_t);
bool isNumber(char*, size_t, int&);

int main() {
	char size[10];
	cout << "Please input a size of the array \n";
	cin >> size;

	int value;

	try {
		if (isNumber(size, strlen(size), value))
		{
			if (value >= 1 && value <= 5)
				throw NoTrouble();
			else
				throw Trouble();
		}
		else 
		{
			throw BigTrouble();
		}
	}

	catch (Trouble t) {
		cout << "Trouble object caught: There's a problem" << endl;
	}

	catch (BigTrouble bt) {
		cout << "Trouble object caught: Really big problem" << endl;
	}

	catch (NoTrouble nt) {
		cout << "Trouble object caught: There's no problem" << endl;
	}

	system("pause");

	return 0;
}

bool isNumber(char* string, size_t length)
{
	for (size_t i = 0; i < length; i++)
	{
		if (string[i] < '0' || string[i] > '9')
			return false;
	}

	return true;
}

bool isNumber(char* string, size_t length, int &value)
{
	value = 0;
	if (isNumber(string, length))
	{
		for (size_t i = 0; i < length; i++)
		{
			value = value * 10 + string[i] - '0';
		}
		return true;
	}
	else 
	{
		return false;
	}
}