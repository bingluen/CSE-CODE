// BookingDatabase class definition
#ifndef BOOKING_DATABASE_H
#define BOOKING_DATABASE_H

#include "Vector.h"
#include "Booking.h" // Booking class definition

class BookingDatabase
{
public:
   BookingDatabase(); // calls loadBookings()

   ~BookingDatabase(); // calls saveBookings()

   // adds a booking object to the end of the vector bookings
   void addBooking( Booking newBooking );

   // returns true if there is a booking object containing specified email
   bool existingBooking( string email ); 

   void displayBookings( string email, MovieDatabase &movieDatabase,
                         char movieNames[][ 60 ], char availableDates[][ 12 ] );
private:
   Vector< Booking > bookings; // vector of the bookings

   void loadBookings(); // loads bookings from the file Bookings.dat
   void saveBookings(); // stores bookings into the file Bookings.dat
}; // end class BookingDatabase

typedef struct{
	char email[40];
	int movieCode;
	int dateCode;
	int sessionTimeCode;
	int numTickets[4];
	char seletedSeats[24][2];
} bookingdata;

#endif // BOOKING_DATABASE_H