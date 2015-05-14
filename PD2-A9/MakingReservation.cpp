// MakingReservation.cpp
// Member-function definitions for class MakingReservation.
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
#include "MakingReservation.h" // MakingReservation class definition

#include "time.h"

char departureTimes[ 36 ][ 8 ] =
     { "06:00", "06:30", "07:00", "07:30", "08:00", "08:30", "09:00", "09:30", "10:00", "10:30",
       "11:00", "11:30", "12:00", "12:30", "13:00", "13:30", "14:00", "14:30", "15:00", "15:30",
       "16:00", "16:30", "17:00", "17:30", "18:00", "18:30", "19:00", "19:30", "20:00", "20:30",
       "21:00", "21:30", "22:00", "22:30", "23:00", "23:30" };


/* Assignment 9 - Implement */

MakingReservation::MakingReservation(ReservationDatabase &reservationDatabase, SouthboundTimetable &southTimeTable, NorthboundTimetable &northTimeTable )
:reservationDatabase(reservationDatabase), southboundTimetable(southTimeTable), northboundTimetable(northTimeTable)
{
}

void MakingReservation::execute() {

	int originStation, destinationStation, carClsss, departureTime;
	string departureDate;
	/* select origin station */
	cout << "Origin Station" << endl;
	cout << "0. Taipei" << endl;
	cout << "1. Banqiao" << endl;
	cout << "2. Taoyuan" << endl;
	cout << "3. Hsinchu" << endl;
	cout << "4. Taichung" << endl;
	cout << "5. Chiayi" << endl;
	cout << "6. Tainan" << endl;
	cout << "7. Zuoying" << endl;
	cout << "? ";
	cin >> originStation;
	this->reservation.setOriginStation(originStation);

	/* select destination station */
	cout << "Destination Station" << endl;
	cout << "0. Taipei" << endl;
	cout << "1. Banqiao" << endl;
	cout << "2. Taoyuan" << endl;
	cout << "3. Hsinchu" << endl;
	cout << "4. Taichung" << endl;
	cout << "5. Chiayi" << endl;
	cout << "6. Tainan" << endl;
	cout << "7. Zuoying" << endl;
	cout << "? ";
	cin >> destinationStation;
	this->reservation.setDestinationStation(destinationStation);

	/* car class */
	cout << "Car class" << endl;
	cout << "1. Standard car" << endl;
	cout << "2. Business car" << endl;
	cout << "? ";
	cin >> carClsss;
	this->reservation.setCarClass(carClsss);


	cout << "Departure Date:";
	cin >> departureDate;
	this->reservation.setDate(departureDate);

	/* print departure time table */
	for (size_t i = 0; i < 36; i++)
	{
		if (i % 5 == 0) cout << endl;
		cout << setw(3) << i << "." << departureTimes[i];
	}
	cout << endl;
	cout << endl;
	cout << "Enter Departure Time Code:";
	cin >> departureTime;
	inputReservationDetails(departureTime);
	chooseTrain(departureTime);
	inputContactPersonInfo();

	/* Random 產生一個 reservationNumber */
	srand(time(NULL));
	int randomReservationNumber = rand() % 100000000;

	this->reservation.setReservationNumber(to_string(randomReservationNumber));

	this->reservationDatabase.addReservation(this->reservation);

	cout << "Reservation Number: " << this->reservation.getReservationNumber() << endl;

	this->reservation.displayReservationDetails();

	cout << "Reservation Completed!" << endl;

}

void MakingReservation::inputReservationDetails(int &departureTime) {
	
	int adultTickets, concessionTickets;

	cout << "How many adult tickets ? ";
	cin >> adultTickets;
	this->reservation.setAdultTickets(adultTickets);

	cout << "How many concession tickets ? ";
	cin >> concessionTickets;
	this->reservation.setConcessionTickets(concessionTickets);



}

void MakingReservation::chooseTrain(int departureTime)
{
	vector<string> legalTrainNumber;

	/* 撈出列車 */
	if (this->reservation.getOriginStation() > this->reservation.getDestinationStation())
	{
		/* 北上 */
		for (size_t i = 0; i < northboundTimetable.getNumberOfTrains(); i++)
		{
			string departure[8];
			northboundTimetable.getTrain(i).getDepartureTimes(departure);
			if (departure[reservation.getOriginStation()] == "-" || departure[reservation.getDestinationStation()] == "-")
				continue;
			Time trainDepartureTime(departure[reservation.getOriginStation()]);
			Time OneHour("01:00");
			Time tragetTime(departureTimes[departureTime]);
			if ((trainDepartureTime >(tragetTime - OneHour)) && (trainDepartureTime < (tragetTime + OneHour)))
			{
				legalTrainNumber.push_back(northboundTimetable.getTrain(i).getTrainNumber());
				cout << setw(10) << northboundTimetable.getTrain(i).getTrainNumber()
					<< setw(10) << departure[reservation.getOriginStation()]
					<< setw(10) << departure[reservation.getDestinationStation()]
					<< endl;
			}
		}
	}
	else
	{
		/* 南下 */

		cout << setw(10) << "Train No."
			<< setw(10) << "Departure"
			<< setw(10) << "Arrival"
			<< endl;

		for (size_t i = 0; i < southboundTimetable.getNumberOfTrains(); i++)
		{
			string departure[8];
			southboundTimetable.getTrain(i).getDepartureTimes(departure);
			if (departure[reservation.getOriginStation()] == "-" || departure[reservation.getDestinationStation()] == "-")
				continue;
			Time trainDepartureTime(departure[reservation.getOriginStation()]);
			Time OneHour("01:00");
			Time tragetTime(departureTimes[departureTime]);
			if ((trainDepartureTime > (tragetTime - OneHour)) && (trainDepartureTime < (tragetTime + OneHour)))
			{
				legalTrainNumber.push_back(southboundTimetable.getTrain(i).getTrainNumber());
				cout << setw(10) << southboundTimetable.getTrain(i).getTrainNumber()
					<< setw(10) << departure[reservation.getOriginStation()]
					<< setw(10) << departure[reservation.getDestinationStation()]
					<< endl;
			}
		}
	}

	bool inputError = false;
	string inputTrainNumber;
	do {
		if (inputError)
			cout << "Train Number error, please tray again.\n" << endl;
		cout << "Enter Train Number: ";
		cin >> inputTrainNumber;
	} while (inputError = (find(legalTrainNumber.begin(), legalTrainNumber.end(), inputTrainNumber) == legalTrainNumber.end()));
	
	this->reservation.setTrainNumber(inputTrainNumber);
}

void MakingReservation::inputContactPersonInfo() {
	cout << "Enter Contact Person Information" << endl;
	string idNumber, phone;
	cout << "ID Number : ";
	cin >> idNumber;
	cout << "Phone : ";
	cin >> phone;

	this->reservation.setIdNumber(idNumber);
	this->reservation.setPhone(phone);
}