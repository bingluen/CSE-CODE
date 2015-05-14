// Reservation.cpp
// Member-function definitions for class Reservation.
#include <iostream>
#include <iomanip>
using namespace std;
#include "SouthboundTimetable.h" // SouthboundTimetable class definition
#include "NorthboundTimetable.h" // NorthboundTimetable class definition
#include "Reservation.h" // Reservation class definition

int adultTicketPrice[8][8] = {    0,  260,  440,  640, 1250, 1820, 2230, 2440,
                                 40,    0,  400,  590, 1210, 1780, 2180, 2390,
                                160,  130,    0,  400, 1010, 1100, 1990, 2200,
                                290,  260,  130,    0,  820, 1390, 1790, 2000,
                                700,  670,  540,  410,    0,  770, 1180, 1390,
                               1080, 1050,  920,  790,  380,    0,  620,  820,
                               1350, 1320, 1190, 1060,  650,  280,    0,  410,
                               1490, 1460, 1330, 1200,  790,  410,  140,    0 };

int concessionTicketPrice[8][8] = {   0, 130, 220, 320, 625, 910, 1115, 1220,
                                     20,   0, 220, 295, 605, 890, 1090, 1195,
                                     80,  65,   0, 220, 505, 790,  995, 1100,
                                    145, 130,  65,   0, 410, 695,  895, 1000,
                                    350, 335, 270, 205,   0, 385,  590,  695,
                                    540, 525, 460, 395, 190,   0,  310,  410,
                                    675, 660, 595, 530, 325, 140,    0,  205,
                                    745, 730, 665, 600, 395, 205,   70,    0 };

const char stationName[8][9] = { "Taipei", "Banqiao", "Taoyuan", "Hsinchu",
									"Taichung", "Chiayi", "Tainan", "Zuoying" };


/* Assignment 9 - Implement */

Reservation::Reservation(string reservationNumber, string trainNumber, string idNumber, string phone,
	string date, int originStation, int destinationStation, int carClass, int adultTickets, int concessionTickets)
{
	this->setReservationNumber(reservationNumber);
	this->setTrainNumber(trainNumber);
	this->setIdNumber(idNumber);
	this->setPhone(phone);
	this->setDate(date);
	this->setOriginStation(originStation);
	this->setDestinationStation(destinationStation);
	this->setCarClass(carClass);
	this->setAdultTickets(adultTickets);
	this->setConcessionTickets(concessionTickets);
}

void Reservation::setReservationNumber(string reservationNumber)
{
	strncpy(this->reservationNumber, reservationNumber.c_str(), reservationNumber.length());
	this->reservationNumber[reservationNumber.length()] = '\0';
}

string Reservation::getReservationNumber()
{
	return reservationNumber;
}

void Reservation::setTrainNumber(string trainNumber)
{
	strncpy(this->trainNumber, trainNumber.c_str(), trainNumber.length());
	this->trainNumber[trainNumber.length()] = '\0';
}

string Reservation::getTrainNumber()
{
	return this->trainNumber;
}

void Reservation::setIdNumber(string idNumber)
{
	strncpy(this->idNumber, idNumber.c_str(), idNumber.length());
	this->idNumber[idNumber.length()] = '\0';
}

string Reservation::getIdNumber()
{
	return idNumber;
}

void Reservation::setPhone(string phone)
{
	strncpy(this->phone, phone.c_str(), phone.length());
	this->phone[phone.length()] = '\0';
}

string Reservation::getPhone()
{
	return this->phone;
}

void Reservation::setDate(string date)
{
	strncpy(this->date, date.c_str(), date.length());
	this->date[date.length()] = '\0';
}

string Reservation::getDate()
{
	return this->date;
}

void Reservation::setOriginStation(int originStation)
{
	if (originStation < 8 && originStation >= 0)
		this->originStation = originStation;
}

int Reservation::getOriginStation()
{
	return originStation;
}

void Reservation::setDestinationStation(int destinationStation)
{
	if (destinationStation >= 0 && destinationStation < 8)
		this->destinationStation = destinationStation;
}

int Reservation::getDestinationStation()
{
	return destinationStation;
}

void Reservation::setCarClass(int carClass)
{
	this->carClass = carClass;
}

int Reservation::getCarClass()
{
	return this->carClass;
}

void Reservation::setAdultTickets(int adultTickets)
{
	this->adultTickets = adultTickets;
}

int Reservation::getAdultTickets()
{
	return adultTickets;
}

void Reservation::setConcessionTickets(int concessionTickets)
{
	this->concessionTickets = concessionTickets;
}

int Reservation::getConcessionTickets()
{
	return concessionTickets;
}

void Reservation::displayReservationDetails()
{
	/*
		找車子出來= =
		因為沒有開由Train No.獲得車子資訊的API，所以來逐個找吧ˊ_>ˋ

	*/
	string departure, arrival;


	/* 判斷北上OR南下 */
	if (this->originStation > this->destinationStation)
	{
		/* 北上 */
		NorthboundTimetable northboundTimeTable;
		for (size_t i = 0; i < northboundTimeTable.getNumberOfTrains(); i++)
		{
			if (northboundTimeTable.getTrain(i).getTrainNumber() == trainNumber)
			{
				string table[8];
				northboundTimeTable.getTrain(i).getDepartureTimes(table);
				/* 北上可能要反過來... 因為表格順序是反的 */
				departure = table[this->originStation];
				arrival = table[this->destinationStation];
			}
		}
	} 
	else if (this->originStation < this->destinationStation)
	{
		/* 南下 */
		SouthboundTimetable sourthboundTimeTable;
		for (size_t i = 0; i < sourthboundTimeTable.getNumberOfTrains(); i++)
		{
			if (sourthboundTimeTable.getTrain(i).getTrainNumber() == trainNumber)
			{
				string table[8];
				sourthboundTimeTable.getTrain(i).getDepartureTimes(table);
				departure = table[this->originStation];
				arrival = table[this->destinationStation];
			}
		}
	}


	/* 找票價... */
	int AdultFare = 0, ConcessionFare = 0;
	if (carClass == 1)
	{
		/* 標準車廂 - 查下三角形 */

		/* 車站index大的要在前面 */
		AdultFare = (destinationStation > originStation) ? adultTicketPrice[destinationStation][originStation] : adultTicketPrice[originStation][destinationStation];
		ConcessionFare = (destinationStation > originStation) ? concessionTicketPrice[destinationStation][originStation] : adultTicketPrice[originStation][destinationStation];
	}
	else if (carClass == 2) 
	{
		/* 商務車廂 - 查上三角形 */

		/* 車站index小的要再前面 */
		AdultFare = (destinationStation < originStation) ? adultTicketPrice[destinationStation][originStation] : adultTicketPrice[originStation][destinationStation];
		ConcessionFare = (destinationStation < originStation) ? concessionTicketPrice[destinationStation][originStation] : concessionTicketPrice[originStation][destinationStation];
	}

	cout << setw(10) << "Train No."
		<< setw(6) << "From"
		<< setw(8) << "To"
		<< setw(10) << "Date"
		<< setw(10) << "Departure"
		<< setw(10) << "Arrival"
		<< setw(8) << "Adult"
		<< setw(14) << "Concession"
		<< setw(8) << "Fare"
		<< setw(8) << "Class" 
		<< endl;

	cout << setw(6) << this->trainNumber
		<< setw(10) << stationName[this->originStation]
		<< setw(10) << stationName[this->destinationStation]
		<< setw(8) << this->date
		<< setw(8) << departure
		<< setw(10) << arrival
		<< setw(8) << AdultFare << "*" << this->adultTickets
		<< setw(10) << ConcessionFare << "*" << this->concessionTickets
		<< setw(10) << AdultFare * this->adultTickets + ConcessionFare * this->concessionTickets
		<< setw(10) << (carClass == 1 ? "Standard" : "Business")
		<< endl;

}