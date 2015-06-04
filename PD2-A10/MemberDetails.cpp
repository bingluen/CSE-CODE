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