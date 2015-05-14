// ReservationDatabase.h
// ReservationDatabase class definition. Represents the reservation database.
#ifndef RESERVATION_DATABASE_H
#define RESERVATION_DATABASE_H
#include <vector>
#include "Reservation.h" // Reservation class definition

class ReservationDatabase
{
public:
   ReservationDatabase(); // constructor loads train reservations from the file Reservation details.dat
   ~ReservationDatabase(); // destructor stores train reservations into the file Reservation details.dat
   int searchReservation( string idNumber, string reservationNumber ); // returns a reservation with specified idNumber and reservationNumber
   void displayReservation( int index ); // calls displayReservationDetails() in the object reservations[ index ]
   void cancelReservation( int index ); // cancels reservations[ index ] from the vector reservations
   void addReservation( Reservation reservation ); // adds a new reservation to end of reservations
   void reduceSeats( int index ); // reduces adultTickets and concessionTickets in the object reservations[ index ]
private:
   vector< Reservation > reservations; // vector of the train reservations

   void loadReservations(); // loads train reservations from the file Reservation details.dat
   void storeReservations(); // stores train reservations into the file Reservation details.dat
}; // end class ReservationDatabase

#endif // RESERVATION_DATABASE_H