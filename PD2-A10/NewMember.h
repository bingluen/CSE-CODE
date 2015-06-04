// NewMember class definition
#ifndef NEW_MEMBER_H
#define NEW_MEMBER_H

#include "MemberDatabase.h" // MemberDatabase class definition

class NewMember
{
public:
   NewMember( MemberDatabase &theMemberDatabase );

   void execute(); // add a new member

private:
   MemberDatabase &memberDatabase; // reference to memberDatabase
}; // end class NewMember

#endif // NEW_MEMBER_H