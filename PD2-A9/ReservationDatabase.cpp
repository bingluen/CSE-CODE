#include "ReservationDatabase.h"

#include <iostream>
#include <fstream>

using namespace std;


ReservationDatabase::ReservationDatabase() {
	loadReservations();
}

ReservationDatabase::~ReservationDatabase() {
	storeReservations();
}


int ReservationDatabase::searchReservation(string idNumber, string reservationNumber)
{
	for (size_t i = 0; i < reservations.size(); i++)
	{
		if (reservations[i].getIdNumber() == idNumber && reservations[i].getReservationNumber() == reservationNumber)
			return i;
	}

	return -1;
}

void ReservationDatabase::displayReservation(int index)
{
	reservations[index].displayReservationDetails();
}

void ReservationDatabase::cancelReservation(int index)
{
	reservations.erase(reservations.begin() + index);
	storeReservations();
}

void ReservationDatabase::addReservation(Reservation reservation)
{
	reservations.push_back(reservation);
	storeReservations();
}

void ReservationDatabase::reduceSeats(int index)
{
	this->displayReservation(index);

	int adult = -1, concession = -1;
	while (adult < 0 || adult > reservations[index].getAdultTickets())
	{
		cout << "How many adult tickets to cancel？";
		cin >> adult;
	}

	while (concession < 0 || concession > reservations[index].getConcessionTickets())
	{
		cout << "How many concession tickets to cancel？";
		cin >> concession;
	}

	reservations[index].setAdultTickets(reservations[index].getAdultTickets() - adult);

	reservations[index].setConcessionTickets(reservations[index].getConcessionTickets() - concession);

	storeReservations();

}
void ReservationDatabase::loadReservations() {
	ifstream load("Reservation details.dat", ios::in | ios::binary);
	/*
	Reservation(string reservationNumber, string trainNumber, string idNumber, string phone,
	string date, int originStation, int destinationStation, int carClass, int adultTickets, int concessionTickets);
	*/
	while (!load.eof())
	{
		char reservationNumber[12], trainNumber[8], idNumber[12], phone[12], date[12];
		int originStation, destinationStation, carClass, adultTickets, concessionTickets;
		
		load.read(reinterpret_cast<char *> (&reservationNumber), sizeof(char)* 12);
		load.read(reinterpret_cast<char *> (&trainNumber), sizeof(char)* 8);
		load.read(reinterpret_cast<char *> (&idNumber), sizeof(char)* 12);
		load.read(reinterpret_cast<char *> (&phone), sizeof(char)* 12);
		load.read(reinterpret_cast<char *> (&date), sizeof(char)* 12);
		load.read(reinterpret_cast<char *> (&originStation), sizeof(int));
		load.read(reinterpret_cast<char *> (&destinationStation), sizeof(int));
		load.read(reinterpret_cast<char *> (&carClass), sizeof(int));
		load.read(reinterpret_cast<char *> (&adultTickets), sizeof(int));
		load.read(reinterpret_cast<char *> (&concessionTickets), sizeof(int));

			/* 
			cout << "讀入\n"
				<< reservationNumber << "\t"
				<< trainNumber << "\t"
				<< idNumber << "\t"
				<< phone << "\t"
				<< date << "\t"
				<< originStation << "\t"
				<< destinationStation << "\t"
				<< carClass << "\t"
				<< adultTickets << "\t"
				<< concessionTickets << "\t"
				<< endl;
			*/

			reservations.push_back(*(new
				Reservation(reservationNumber, trainNumber,
				idNumber, phone, date, originStation,
				destinationStation, carClass, adultTickets, concessionTickets)));
	}

	//最後一個會因為eof還沒升起，而被重複
	reservations.pop_back();
}

void ReservationDatabase::storeReservations() {
	ofstream store("Reservation details.dat", ios::out | ios::binary);

	/* 
	for (size_t i = 0; i < reservations.size(); i++) {
		store.write((reservations[i].getReservationNumber().c_str()), sizeof(char)* 12);
		store.write((reservations[i].getTrainNumber().c_str()), sizeof(char)* 8);
		store.write((reservations[i].getIdNumber().c_str()), sizeof(char)* 12);
		store.write((reservations[i].getPhone().c_str()), sizeof(char)* 12);
		store.write((reservations[i].getDate().c_str()), sizeof(char)* 12);
		store.write(to_string(reservations[i].getOriginStation()).c_str(), sizeof(int));
		store.write(to_string(reservations[i].getDestinationStation()).c_str(), sizeof(int));
		store.write(to_string(reservations[i].getCarClass()).c_str(), sizeof(int));
		store.write(to_string(reservations[i].getAdultTickets()).c_str(), sizeof(int));
		store.write(to_string(reservations[i].getConcessionTickets()).c_str(), sizeof(int));
	}
	*/

	/* 利用iterator 來寫...*/
	for (vector<Reservation>::iterator it = reservations.begin(); it < reservations.end(); it++)
	{

		int aidWrite;
		store.write(it->getReservationNumber().c_str(), sizeof(char)* 12);
		store.write(it->getTrainNumber().c_str(), sizeof(char)* 8);
		store.write(it->getIdNumber().c_str(), sizeof(char)* 12);
		store.write(it->getPhone().c_str(), sizeof(char)* 12);
		store.write(it->getDate().c_str(), sizeof(char)* 12);
		aidWrite = it->getOriginStation();
		store.write(reinterpret_cast<char*> (&aidWrite), sizeof(int));
		aidWrite = it->getDestinationStation();
		store.write(reinterpret_cast<char*> (&aidWrite), sizeof(int));
		aidWrite = it->getCarClass();
		store.write(reinterpret_cast<char*> (&aidWrite), sizeof(int));
		aidWrite = it->getAdultTickets();
		store.write(reinterpret_cast<char*> (&aidWrite), sizeof(int));
		aidWrite = it->getConcessionTickets();
		store.write(reinterpret_cast<char*> (&aidWrite), sizeof(int));
		/*
		cout << "寫入\n"
			<< it->getReservationNumber().c_str() << "\t"
			<< it->getTrainNumber().c_str() << "\t"
			<< it->getIdNumber().c_str() << "\t"
			<< it->getPhone().c_str() << "\t"
			<< it->getDate().c_str() << "\t"
			<< to_string(it->getOriginStation()).c_str() << "\t"
			<< to_string(it->getDestinationStation()).c_str() << "\t"
			<< to_string(it->getCarClass()).c_str() << "\t"
			<< to_string(it->getAdultTickets()).c_str() << "\t"
			<< to_string(it->getConcessionTickets()).c_str() << "\t"
			<< endl;
			*/
			
	}

	store.close();
}