// Booking.cpp
// Member-function definitions for class Booking
#include <iostream>
#include <iomanip>
#include "Booking.h" // Booking class definition

Booking::Booking()
{
}

void Booking::setEmail( string theEmail )
{
   int length = theEmail.size();
   length = ( length < 40 ? length : 39 );
   for( int i = 0; i < length; i++ )
      email[ i ] = theEmail[ i ];
   email[ length ] = '\0';
}

string Booking::getEmail()
{
   return string( email );
}

void Booking::setMovieCode( int theMovieCode )
{
   movieCode = ( theMovieCode > 0 ? theMovieCode : 0 );
}

int Booking::getMovieCode()
{
   return movieCode;
}

void Booking::setDateCode( int theDateCode )
{
   dateCode = ( theDateCode > 0 ? theDateCode : 0 );
}

int Booking::getDateCode()
{
   return dateCode;
}

void Booking::setSessionTimeCode( int theSessionTimeCode )
{
   sessionTimeCode = ( theSessionTimeCode > 0 ? theSessionTimeCode : 0 );
}

int Booking::getSessionTimeCode()
{
   return sessionTimeCode;
}

void Booking::setNumTickets( int theNumTickets[] )
{
   for( int i = 0; i < 4; i++ )
      numTickets[ i ] = ( theNumTickets[ i ] > 0 ? theNumTickets[ i ] : 0 );
}

int Booking::getNumTickets( int ticketType )
{
   return numTickets[ ticketType ];
}

void Booking::setSeletedSeats( string theSeletedSeats[], int numSeats )
{
   for( int i = 0; i < numSeats; i++ )
   {
      seletedSeats[ i ][ 0 ] = theSeletedSeats[ i ][ 0 ];
      seletedSeats[ i ][ 1 ] = theSeletedSeats[ i ][ 1 ];
	  seletedSeats[ i ][ 2 ] = '\0';
   }
}

string Booking::getSeletedSeat( int number )
{
   return seletedSeats[ number ];
}


/* Assignment 10 - implement */

void Booking::displayBooking(MovieDatabase &movieDatabase)
{
	const char ticketType[][20] = { "Adult ticket", "Concession tickets", "Disability ticket", "elderly tickets" };


	cout << setw(20) << " "
		<< "No. of Tickets"
		<< "Price"
		<< "Subtotal"
		<< endl;

	int total = 0;

	for (size_t i = 0; i < 4; i++)
	{
		cout << setw(20) << ticketType[i]
			<< setw(15) << this->numTickets[i]
			<< setw(6) << this->numTickets[i] * movieDatabase.getMovie(this->movieCode).getPrice(i)
			<< endl;

		total += this->numTickets[i] * movieDatabase.getMovie(this->movieCode).getPrice(i);
	}

	cout << "Total Amount For Tickets: " << total << endl;
}

int Booking::getNumTickets()
{
	int total = 0;
	for (size_t i = 0; i < 4; i++)
	{
		total += numTickets[i];
	}
	return total;
}