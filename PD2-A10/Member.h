// Member class definition
#ifndef MEMBER_H
#define MEMBER_H

#include <string>
using namespace std;

class Member
{
public:
   Member( string theEmail = "", string thePassword = "", string theIdNumber = "",
           string theName = "", string thePhone = "" );
   void setEmail( string theEmail );
   string getEmail();
   void setPassword( string thePassword );
   string getPassword();
   void setIdNumber( string theIdNumber );
   string getIdNumber();
   void setName( string theName );
   string getName();
   void setPhone( string thePhone );
   string getPhone();
   void display();

private:
   char email[ 40 ];
   char password[ 24 ];
   char idNumber[ 12 ];
   char name[ 12 ];
   char phone[ 12 ];
};

#endif