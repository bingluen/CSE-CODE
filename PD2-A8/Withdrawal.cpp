// Withdrawal.cpp
// Member-function definitions for class Withdrawal.
#include <iostream>
#include <iomanip>
using namespace std;
#include "Withdrawal.h" // Withdrawal class definition

// global constant that corresponds to menu option to cancel
static const int CANCELED = 6;

// Withdrawal constructor initialize class's data members
Withdrawal::Withdrawal( int userAccountNumber, vector< Account > &atmAccounts )
  : accountNumber( userAccountNumber ),
    accounts( atmAccounts ),
    remainingBills( INITIAL_REMAINING_BILLS )
{
   // empty body
} // end Withdrawal constructor

/* Assignment 8 - implement */

void Withdrawal::execute()
{
	int option[] = {20, 40, 60, 100, 200};
	Account* accountPtr = getAccount(this->accountNumber, this->accounts);
	int choice;
	
	choice = displayMenuOfAmounts();

	if (option[choice] > accountPtr->getAvailableBalance())
	{
		cout << "Available balance is not enough" << endl;
		cout << endl;
		return;
	}

	cout << "Please take your cash from the cash dispenser" << endl;

	accountPtr->debit(option[choice]);

}

Account * Withdrawal::getAccount(int accountNumber, vector< Account > &accounts)
{
	/* 找出帳號 */
	Account* accountPtr = NULL;
	for (vector< Account >::iterator it = accounts.begin(); it < accounts.end(); it++)
	{
		if (it->getAccountNumber() == accountNumber)
			return &(*it);
	}

	/* 沒有該帳號 */
	return NULL;
}

int Withdrawal::displayMenuOfAmounts() const
{
	int option;

	cout << "Withdrawal options:" << endl;
	cout << "1 - $20" << endl;
	cout << "2 - $40" << endl;
	cout << "3 - $60" << endl;
	cout << "4 - $100" << endl;
	cout << "5 - $200" << endl;
	cout << "6 - Cancel transaction" << endl;

	cout << "Choose a withdrawal option (1-6):";
	do
	{
		cin >> option;
	} while (option < 1 || option > 6);

	return option - 1;
}