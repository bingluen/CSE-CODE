// Member.cpp
// Member-function definitions for class Member
#include <iostream>
#include "Member.h" // Member class definition

Member::Member( string theEmail, string thePassword, string theIdNumber,
                string theName, string thePhone )
{
   setEmail( theEmail );
   setPassword( thePassword );
   setIdNumber( theIdNumber );
   setName( theName );
   setPhone(  thePhone );
}

void Member::setEmail( string theEmail )
{
   int length = theEmail.size();
   length = ( length < 40 ? length : 39 );
   for( int i = 0; i < length; i++ )
      email[ i ] = theEmail[ i ];
   email[ length ] = '\0';
}

string Member::getEmail()
{
   return string( email );
}

void Member::setPassword( string thePassword )
{
   int length = thePassword.size();
   length = ( length < 24 ? length : 23 );
   for( int i = 0; i < length; i++ )
      password[ i ] = thePassword[ i ];
   password[ length ] = '\0';
}

string Member::getPassword()
{
   return string( password );
}

void Member::setIdNumber( string theIdNumber )
{
   int length = theIdNumber.size();
   length = ( length < 12 ? length : 11 );
   for( int i = 0; i < length; i++ )
      idNumber[ i ] = theIdNumber[ i ];
   idNumber[ length ] = '\0';
}

string Member::getIdNumber()
{
   return string( idNumber );
}

void Member::setName( string theName )
{
   int length = theName.size();
   length = ( length < 12 ? length : 11 );
   for( int i = 0; i < length; i++ )
      name[ i ] = theName[ i ];
   name[ length ] = '\0';
}

string Member::getName()
{
   return string( name );
}

void Member::setPhone( string thePhone )
{
   int length = thePhone.size();
   length = ( length < 12 ? length : 11 );
   for( int i = 0; i < length; i++ )
      phone[ i ] = thePhone[ i ];
   phone[ length ] = '\0';
}

string Member::getPhone()
{
   return string( phone );
}

void Member::display()
{
   cout << "1. Name: " << name
      << "\n2. Email Address: " << email
      << "\n3. Phone Number: " << phone
      << "\n4. ID Number: " << idNumber
      << "\n5. Password: " << password;
}