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