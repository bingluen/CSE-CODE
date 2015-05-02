// Deposit.cpp
// Member-function definitions for class Deposit.
#include <iostream>
#include <iomanip>
using namespace std;
#include "Deposit.h" // Deposit class definition

static const int CANCELED = 0; // constant representing cancel option 

// Deposit constructor initializes class's data members
Deposit::Deposit( int userAccountNumber, vector< Account > &atmAccounts )
   : accountNumber( userAccountNumber ),
     accounts( atmAccounts )
{
   // empty body
} // end Deposit constructor


/* Assignment 8 - implement */

void Deposit::execute()
{
	Account *accountPtr = getAccount(accountNumber, accounts);

	double amount = this->promptForDepositAmount();
	if (amount <= 0)
		return;
	else
	{
		cout << "Please insert a deposit envelope containing $" << fixed << setprecision(2) << amount << " in the deposit slot." << endl;
		cout << endl;
		cout << "Your envelope has been received." << endl;

		cout << "NOTE: The money deposited will not be available until we" << endl;
		cout << "verify the amount of any enclosed cash, and any enclosed checks clear." << endl;

		accountPtr->credit(amount);
	}


}

Account* Deposit::getAccount(int accountNumber, vector< Account > &accounts)
{
	for (vector< Account >::iterator it = accounts.begin(); it < accounts.end(); it++)
	{
		if (it->getAccountNumber() == accountNumber)
			return &*it;
	}
	return NULL;
}

double Deposit::promptForDepositAmount() const
{
	double cents;
	cout << "Please enter a deposit amount in CENTS (or 0 to cancel):";
	cin >> cents;

	if (cents > 0)
		return cents / 100;
	else
		return 0;
}