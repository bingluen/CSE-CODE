// Reservation.h
// Reservation class definition. Represents a reservation.
#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>
using namespace std;



class Reservation
{
public:
   Reservation( string = "", string = "", string = "", string = "",
                string = "", int = 0, int = 7, int = 1, int = 1, int = 0 );
   void setReservationNumber( string );
   string getReservationNumber();
   void setTrainNumber( string );
   string getTrainNumber();
   void setIdNumber( string );
   string getIdNumber();
   void setPhone( string );
   string getPhone();
   void setDate( string );
   string getDate();
   void setOriginStation( int );
   int getOriginStation();
   void setDestinationStation( int );
   int getDestinationStation();
   void setCarClass( int );
   int getCarClass();
   void setAdultTickets( int );
   int getAdultTickets();
   void setConcessionTickets( int );
   int getConcessionTickets();
   void displayReservationDetails(); // display the information of a reservation
private:
   char reservationNumber[12]; // used to identify a reservation
   char trainNumber[8]; // used to identify a train
   char idNumber[12]; // the id number of the contact person
   char phone[12]; // the (local or mobile) phone number of the contact person
   char date[12]; // outbound date
   int originStation; // the origin station code
   int destinationStation; // the destination station code
   int carClass; // the car class code; 1:standard car, 2:business car
   int adultTickets; // the number of adult tickets
   int concessionTickets; // the number of concession tickets
};

#endif