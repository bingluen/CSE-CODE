#include "logger.h"
#include <iostream>
#include "exception.h"
using namespace std;

Logger::Logger()
:userSignedIn(false)
{
}

void Logger::execute()
{
	if (userSignedIn)
		return;

	bool isErrorInput = false;
	char input[3];
	cout << "Please select the action you want to perform" << endl;
	cout << "(1) Login \n(2) Registered" << endl;

	do {
		cin >> input;
		if (!isNumber(input) || atoi(input) > 2 || atoi(input) < 1)
		{
			isErrorInput = true;
			cout << "You enter a wrong number !\n Please select again!" << endl;
		}
	} while (isErrorInput);


	switch (atoi(input))
	{
	case 1:
		doSignIn();
		break;
	case 2:
		doRegister();
		break;
	}
}

bool Logger::doSignIn()
{
	size_t errorCount = 0;
	string id, password;
	cout << "Please input your ID : ";
	cin >> id;
	try
	{
		this->user = userData.get(id);
	}
	catch (const UserError& e)
	{
		cout << e.getMessages() << endl;
		cout << "you need to register first!" << endl;
		cout << endl;
		return false;
	}

	while (errorCount < 3)
	{
		cout << "Please input your Password : ";
		cin >> password;

		if (user.getPassword() == password)
		{
			userSignedIn = true;
			return true;
		}
		errorCount++;
		cout << "Wrong password! Please enter again!" << endl;
	}

	cout << "Password is entered incorrectly three times \n Goodbye" << endl;
	return false;
}

void Logger::doRegister()
{
	User newUser;
	string input;
	bool loopFlag = false;
	do{
		if (loopFlag)
			cout << "' " << input << " ' has benn used!\n" << endl;
		cout << "Please input an ID you want: ";
		cin >> input;
	} while (loopFlag = userData.idDuplicate(input));
	newUser.setId(input);
	
	cout << "Please input a password you want: ";
	cin >> input;
	newUser.setPassword(input);

	cout << "Please input the name: ";
	cin >> input;
	newUser.setName(input);

	cout << "Please input ID number: ";
	cin >> input;
	newUser.setIdNumber(input);

	cout << "Please input E-mail: ";
	cin >> input;
	newUser.setEmail(input);

	cout << "Please input phone: ";
	cin >> input;
	newUser.setPhone(input);

	cout << "Please input address: ";
	cin >> input;
	newUser.setAddress(input);

	if (userData.Insert(newUser))
	{
		cout << newUser.getName() << ", Welcome to join CSE auction system!\n" << endl;
	}

	user = userData.get(newUser.getId());

	userSignedIn = true;
}

bool Logger::isSingedIn()
{
	return userSignedIn;
}