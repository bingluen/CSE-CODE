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
	getline(cin, input);
	if (memberDatabase.existingId(input))
	{
		cout << "An account already exists with the ID number !\n" << endl;
		return;
	}
	newMember.setIdNumber(input);
	
	cout << "Enter your name: ";
	getline(cin, input);
	newMember.setName(input);

	cout << "Enter your email address: ";
	getline(cin, input);
	if (memberDatabase.existingEmail(input))
	{
		cout << "An account already exits with the email address !\n" << endl;
		return;
	}
	newMember.setEmail(input);

	cout << "Enter your password: ";
	getline(cin, input);
	newMember.setPassword(input);

	cout << "Enter your phone number: ";
	getline(cin, input);
	newMember.setPhone(input);

	memberDatabase.addMember(newMember);

	cout << "\nSuccessful!\n" << endl;
}