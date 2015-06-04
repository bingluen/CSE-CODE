// MemberDetails class definition
#ifndef MEMBER_DETAILS_H
#define MEMBER_DETAILS_H

#include "MemberDatabase.h" // MemberDatabase class definition

class MemberDetails
{
public:
   MemberDetails( MemberDatabase &theMemberDatabase );

   void execute( Vector< Member >::iterator it );

private:
   MemberDatabase &memberDatabase; // reference to memberDatabase

   int inputAnInteger( int begin, int end );
}; // end class MemberDetails

#endif // MEMBER_DETAILS_H