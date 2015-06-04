// BuyTickets.cpp
// Member-function definitions for class BuyTickets
#include <iostream>
#include <iomanip>
using namespace::std;
#include "BuyTickets.h" // BuyTickets class definition

extern char hours[ 17 ][ 8 ];

// BuyTickets default constructor
BuyTickets::BuyTickets( MovieDatabase &theMovieDatabase, BookingDatabase &theBookingDatabase, string theEmail )
   : movieDatabase( theMovieDatabase ),
     bookingDatabase( theBookingDatabase )
{
   int length = theEmail.size();
   for( int i = 0; i < length; i++ )
      email[ i ] = theEmail[ i ];
   email[ length ] = '\0';
}

int BuyTickets::inputAnInteger( int begin, int end )
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