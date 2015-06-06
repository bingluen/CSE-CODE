// MemberDatabase.cpp
// Member-function definitions for class MemberDatabase
#include <iostream>
#include <fstream>
#include "MemberDatabase.h" // MemberDatabase class definition

// MemberDatabase default constructor loads members from the file Members.dat
MemberDatabase::MemberDatabase()
{
   loadMembers();
}

// MemberDatabase destructor saves members into the file Members.dat
MemberDatabase::~MemberDatabase()
{
   saveMembers();
}

Vector< Member >::iterator MemberDatabase::end()
{
   return members.end();
}

void MemberDatabase::addMember( Member newMember )
{
   members.push_back( newMember );
}


bool MemberDatabase::existingId(string id)
{
	// returns true if there is a member object containing specified id
	for (Vector<Member>::iterator it = members.begin(); it < members.end(); it++)
	{
		if (it->getIdNumber() == id)
			return true;
	}
	return false;
}


bool MemberDatabase::existingEmail(string email)
{
	// returns true if there is a member object containing specified email
	for (Vector<Member>::iterator it = members.begin(); it < members.end(); it++)
	{
		if (it->getEmail() == email)
			return true;
	}
	return false;
}


Vector< Member >::iterator MemberDatabase::getMember(string email, string password)
{
	// returns an iterator which points to the member object containing specified email and password
	for (Vector<Member>::iterator it = members.begin(); it < members.end(); it++)
	{
		if (it->getEmail() == email && it->getPassword() == password)
			return it;
	}
	return members.end();
}

void MemberDatabase::loadMembers()
{
	// loads members from the file Members.dat
	ifstream loadFile("Members.dat", ios::in | ios::binary);

	loadFile.seekg(0, ios::end);

	int conut = loadFile.tellg() / sizeof(member);

	loadFile.seekg(0, ios::beg);

	for (size_t i = 0; i < conut; i++)
	{
		member data;
		loadFile.read(reinterpret_cast<char *> (&data), sizeof(member));

		Member newMember(data.email, data.password, data.idNumber, data.name, data.phone);

		members.push_back(newMember);

		if (!loadFile)
			break;
	}

	loadFile.close();
}
void MemberDatabase::saveMembers()
{
	// stores members into the file Members.dat
	ofstream saving("Members.dat", ios::out | ios::binary);

	for (Vector<Member>::iterator it = members.begin(); it < members.end(); it++)
	{
		member data;
		strcpy(data.email, it->getEmail().c_str());
		strcpy(data.idNumber, it->getIdNumber().c_str());
		strcpy(data.name, it->getName().c_str());
		strcpy(data.password, it->getPassword().c_str());
		strcpy(data.phone, it->getPhone().c_str());
		saving.write(reinterpret_cast<char *> (&data), sizeof(member));
	}

	saving.close();
}