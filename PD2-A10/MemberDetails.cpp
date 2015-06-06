// MemberDetails.cpp
// Member-function definitions for class MemberDetails
#include <iostream>
using namespace std;
#include "MemberDetails.h" // MemberDetails class definition

MemberDetails::MemberDetails( MemberDatabase &theMemberDatabase )
   : memberDatabase( theMemberDatabase )
{
}

int MemberDetails::inputAnInteger( int begin, int end )
{
   char string[ 80 ];

   cin.getline( string, 80, '\n' );

   if( strlen( string ) == 0 || strlen( string ) >= 3 )
      return -1;

   for( unsigned int i = 0; i < strlen( string ); i++ )
      if( string[ i ] < '0' || string[ i ] > '9' )
         return -1;

   int number = atoi( string );
   if( number >= begin && number <= end )
      return number;
   else
      return -1;
}

void MemberDetails::execute(Vector< Member >::iterator it)
{
	cout << "1. Name: " << it->getName() << endl;
	cout << "2. Email address: " << it->getEmail() << endl;
	cout << "3. Phone number: " << it->getPhone() << endl;
	cout << "4. ID Number: " << it->getIdNumber() << endl;
	cout << "5. Password: " << it->getPassword() << endl;

	int choice;
	do { cout << "Which one do you want to modify (0 -  not modify)?";  } while ((choice = inputAnInteger(0, 5)) == -1);

	if (choice == 0)
		return;

	bool loopFlag = true;

	while (loopFlag)
	{
		cout << "Enter correct data: ";
		string input;
		getline(cin, input);

		switch (choice) {
		case 1:
			it->setName(input);
			loopFlag = false;
			break;
		case 2:
			loopFlag = memberDatabase.existingEmail(input);
			if(!loopFlag)
				it->setEmail(input);
			else
				cout << "An account already exits with the email address !" << endl;
			break;
		case 3:
			it->setPhone(input);
			loopFlag = false;
			break;
		case 4:
			loopFlag = memberDatabase.existingId(input);
			if (!loopFlag)
				it->setIdNumber(input);
			else
				cout << "An account already exists with the ID number !" << endl;
			break;
		case 5:
			it->setPassword(input);
			loopFlag = false;
			break;
		}
	}

	cout << "Successful!" << endl;
	
}