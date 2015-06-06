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

/* Assignment 10 - implement */

bool BookingDatabase::existingBooking(string email)
{
	for (Vector<Booking>::iterator it = bookings.begin(); it < bookings.end(); it++)
	{
		if (email == it->getEmail())
			return true;
	}
	return false;
}

void BookingDatabase::displayBookings(string email, MovieDatabase &movieDatabase,
	char movieNames[][60], char availableDates[][12])
{
	cout << "Booking History:" << endl;

	for (Vector<Booking>::iterator it = bookings.begin(); it < bookings.end(); it++)
	{
		if (email == it->getEmail())
		{
			cout << "Movie: " << movieNames[it->getMovieCode()] << endl;
			cout << "Date: " << availableDates[it->getDateCode()] << endl;
			cout << "Show Time: " << hours[it->getSessionTimeCode()] << endl;
			cout << "Seats: ";
			for (size_t i = 0; i < it->getNumTickets(); i++)
				cout << it->getSeletedSeat(i) << " ";

			cout << endl;
		}
	}
}

void BookingDatabase::loadBookings()
{
	// loads bookings from the file Bookings.dat
	ifstream loadFile("Bookings.dat", ios::in | ios::binary);


	loadFile.seekg(0, ios::end);

	int conut = loadFile.tellg() / sizeof(bookingdata);

	loadFile.seekg(0, ios::beg);

	for (size_t i = 0; i < conut; i++)
	{
		bookingdata data;

		Booking newbooking;
		

		/* 讀出來 */
		loadFile.read(reinterpret_cast<char*> (&data), sizeof(bookingdata));

		/* 打包裝箱(? */
		newbooking.setEmail(data.email);
		newbooking.setMovieCode(data.movieCode);
		newbooking.setDateCode(data.dateCode);
		newbooking.setSessionTimeCode(data.sessionTimeCode);
		newbooking.setNumTickets(data.numTickets);

		/* 把2-D array 轉成 1-D string array (ノ｀Д´)ノ彡┻━┻　 */
		Vector<string> temp;
		for (size_t i = 0; i < newbooking.getNumTickets(); i++)
			temp.push_back(data.seletedSeats[i]);

		newbooking.setSeletedSeats(&*(temp.begin()), newbooking.getNumTickets());


		this->bookings.push_back(newbooking);

	}

	loadFile.close();
}

void BookingDatabase::saveBookings()
{
	// stores bookings into the file Bookings.dat
	ofstream saving("Bookings.dat", ios::binary | ios::out);

	for (Vector<Booking>::iterator it = bookings.begin(); it < bookings.end(); it++)
	{
		bookingdata data;
		strcpy(data.email, it->getEmail().c_str());
		data.dateCode = it->getDateCode();
		data.movieCode = it->getMovieCode();
		for (size_t i = 0; i < 4; i++)
			data.numTickets[i] = it->getNumTickets(i);
		for (size_t i = 0; i < it->getNumTickets(); i++)
			strncpy(data.seletedSeats[i], it->getSeletedSeat(i).c_str(), 2);
		data.sessionTimeCode = it->getSessionTimeCode();
		saving.write(reinterpret_cast<char *>( &data), sizeof(bookingdata));
	}
	saving.close();
}