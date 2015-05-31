#include <iostream>
#include "hander.h"

int main()
{
	cout << "------------------------------------" << endl;
	cout << "| Welcome  to CSE auction System ! |" << endl;
	cout << "------------------------------------" << endl;
	bool loopFlag = true;
	Hander hander;
	while (loopFlag) {
		cout << "Please select the  action you want to perform" << endl;
		cout << "(1) Login" << endl;
		cout << "(2) Post auction itmes" << endl;
		cout << "(3) Visit the website commoditites" << endl;
		cout << "(0) Exit" << endl;
		int choice;
		cin >> choice;

		switch (choice)
		{
			case 0:
				cout << "Good-bye" << endl;
				loopFlag = false;
				break;
			case 1:
				hander.login();
				break;
			case 2:
				hander.post();
				break;
			case 3:
				hander.view();
				break;
			default:
				cout << "You enter a wrong number !\n Please select again!" << endl;
		}
		cout << endl;
	}
	return 0;
}