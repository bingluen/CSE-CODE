// NewMember.cpp
// Member-function definitions for class NewMember
#include <iostream>
#include <fstream>
#include "NewMember.h" // NewMember class definition

NewMember::NewMember( MemberDatabase &theMemberDatabase )
   : memberDatabase( theMemberDatabase )
{
}

/* Assignment 10 - implement */

void NewMember::execute()
{
	string input;

	Member newMember;

	cout << "Enter your ID Number: ";
	cin.ignore();
	getline(cin, input);
	if (memberDatabase.existingId(input))
	{
		cout << "An account already exists with the ID number !" << endl;
		return;
	}
	newMember.setIdNumber(input);
	
	cout << "Enter your name: ";
	cin.ignore();
	getline(cin, input);
	newMember.setName(input);

	cout << "Enter your email address: ";
	cin.ignore();
	getline(cin, input);
	if (memberDatabase.existingEmail(input))
	{
		cout << "An account already exits with the email address !" << endl;
		return;
	}
	newMember.setEmail(input);

	cout << "Enter your password: ";
	cin.ignore();
	getline(cin, input);
	newMember.setPassword(input);

	cout << "Enter your phone number: ";
	cin.ignore();
	getline(cin, input);
	newMember.setPhone(input);

	memberDatabase.addMember(newMember);

	cout << "Successful!" << endl;
}