#ifndef MEMBER_DATABASE_H
#define MEMBER_DATABASE_H

// MemberDatabase class definition
#include "Vector.h"
#include "Member.h" // Member class definition

class MemberDatabase
{
public:
   MemberDatabase(); // calls loadMembers()

   ~MemberDatabase(); // calls saveMembers()

   Vector< Member >::iterator end(); // returns members.end()

   // returns true if there is a member object containing specified id
   bool existingId( string id );

   // returns true if there is a member object containing specified email
   bool existingEmail( string email );

   // adds a member object to the end of the vector members
   void addMember( Member newMember );

   // returns an iterator which points to the member object containing specified email and password
   Vector< Member >::iterator getMember( string email, string password );
private:
   Vector< Member > members; // vector of the members

   void loadMembers(); // loads members from the file Members.dat
   void saveMembers(); // stores members into the file Members.dat
}; // end class MemberDatabase

#endif // MEMBER_DATABASE_H