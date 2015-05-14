#include <iostream>
#include "ReservationHistory.h"
using namespace std;

ReservationHistory::ReservationHistory(ReservationDatabase &reservationDatabase, SouthboundTimetable &southboundTimetable, NorthboundTimetable &northboundTimetable)
:reservationDatabase(reservationDatabase), southboundTimetable(southboundTimetable), northboundTimetable(northboundTimetable)
{
}

void ReservationHistory::execute()
{
	cout << "Enter ID Number : ";
	cin >> idNumber;

	cout << "Enter Reservation Number : ";
	cin >> reservationNumber;

	int reservationIndex = reservationDatabase.searchReservation(idNumber, reservationNumber);

	if (reservationIndex < 0)
	{
		cout << "No resrvation histroy " << endl;
		return;
	}

	while (true) {
		reservationDatabase.displayReservation(reservationIndex);

		cout << "Enter Your Choice" << endl;
		cout << "1. Cancellation" << endl;
		cout << "2. Reduce" << endl;
		cout << "3. Back to Main Menu" << endl;
		cout << "? ";
		int choice = enterChoice();

		switch (choice) {
		case 1:
			reservationDatabase.cancelReservation(reservationIndex);
			cout << "Reservation Cancelled!" << endl;
			return;
		case 2:
			reservationDatabase.reduceSeats(reservationIndex);
			cout << "You have successfully reduced the number of tickets!" << endl;
			break;
		case 3:
			return;
		}
	}

	

}

int ReservationHistory::enterChoice() {
	int choice;
	do {
		cin >> choice;
	} while (choice < 1 && choice > 3);

	return choice;
}