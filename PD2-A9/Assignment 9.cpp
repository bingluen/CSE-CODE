#include <iostream>
using namespace std;
#include "ReservationHistory.h" // ReservationHistory class definition
#include "MakingReservation.h" // MakingReservation class definition

int enterChoice();

int main()
{
   cout << "Taiwan High Speed Rail Booking System\n";

   SouthboundTimetable southboundTimetable;
   NorthboundTimetable northboundTimetable;
   ReservationDatabase reservationDatabase;
   MakingReservation makingReservation( reservationDatabase, southboundTimetable, northboundTimetable );
   ReservationHistory reservationHistory( reservationDatabase, southboundTimetable, northboundTimetable );

   int choice;
   while ( ( choice = enterChoice() ) != 3 )
   {
      switch ( choice )
      {
      case 1:
         makingReservation.execute();
         break;
      case 2:
         reservationHistory.execute();
         break;
      default:
         cerr << "Incorrect Choice" << endl;
         break;
      }
   }

   system("pause");
   return 0;
}

int enterChoice()
{
   cout << "\nEnter Your Choice\n"
      << "1. Booking\n"
      << "2. Booking History\n"
      << "3. End Program\n? ";

   int menuChoice;
   cin >> menuChoice;
   return menuChoice;
}