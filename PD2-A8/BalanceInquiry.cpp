// BalanceInquiry.cpp
// Member-function definitions for class BalanceInquiry.
#include <iostream>
#include <iomanip>
using namespace std;
#include "BalanceInquiry.h" // BalanceInquiry class definition

// BalanceInquiry constructor initializes base-class data members
BalanceInquiry:: BalanceInquiry( int userAccountNumber, vector< Account > &atmAccounts )
   : accountNumber( userAccountNumber ),
     accounts( atmAccounts )
{
   // empty body
} // end BalanceInquiry constructor

/* Assigment 8 - implement */

void BalanceInquiry::execute()
{
	Account* accountPtr = getAccount(accountNumber, accounts);
	this->displayInformation(accountPtr);
}

Account * BalanceInquiry::getAccount(int accountNumber, vector< Account > &accounts)
{
	/* 找出帳號 */
	for (vector< Account >::iterator it = accounts.begin(); it < accounts.end(); it++)
	{
		if (it->getAccountNumber() == accountNumber)
			return &(*it);
	}
	/* 沒有該帳號 */
	return NULL;
}

void BalanceInquiry::displayInformation(Account* accountPtr)
{
	cout << "Balance Information" << endl;
	cout << " - Available balance: $" << fixed << setprecision(2) << accountPtr->getAvailableBalance() << endl;
	cout << " - Total balance: $" << fixed << setprecision(2) << accountPtr->getTotalBalance() << endl;
}