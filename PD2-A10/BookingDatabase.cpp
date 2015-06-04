// BookingDatabase.cpp
// Member-function definitions for class BookingDatabase
#include <iostream>
#include <fstream>
#include "BookingDatabase.h" // BookingDatabase class definition

extern char hours[ 17 ][ 8 ];

// BookingDatabase default constructor loads bookings from the file Bookings.dat
BookingDatabase::BookingDatabase()
{
   loadBookings();
}

// BookingDatabase destructor saves bookings into the file Bookings.dat
BookingDatabase::~BookingDatabase()
{
   saveBookings();
}

void BookingDatabase::addBooking( Booking newBooking )
{
   bookings.push_back( newBooking );
}