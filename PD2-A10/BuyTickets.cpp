// BuyTickets.cpp
// Member-function definitions for class BuyTickets
#include <iostream>
#include <iomanip>
using namespace::std;
#include "BuyTickets.h" // BuyTickets class definition

extern char hours[ 17 ][ 8 ];

// BuyTickets default constructor
BuyTickets::BuyTickets( MovieDatabase &theMovieDatabase, BookingDatabase &theBookingDatabase, string theEmail )
   : movieDatabase( theMovieDatabase ),
     bookingDatabase( theBookingDatabase )
{
   int length = theEmail.size();
   for( int i = 0; i < length; i++ )
      email[ i ] = theEmail[ i ];
   email[ length ] = '\0';
}

int BuyTickets::inputAnInteger( int begin, int end )
{
   char string[ 80 ];

   cin.getline( string, 80, '\n' );

   if( strlen( string ) == 0 || strlen( string ) >= 3 )
      return -1;

   for( unsigned int i = 0; i < strlen( string ); i++ )
      if( string[ i ] < '0' || string[ i ] > '9' )
         return -1;

   int number = atoi( string );
   if( number >= begin && number <= end )
      return number;
   else
      return -1;
}

/* Assignment 10 - implement */
void BuyTickets::execute(char movieNames[][60], char availableDates[][12], int numDates)
{
	movieDatabase.displaySessionTimes(movieNames, availableDates);

	Booking newBooking;
	int flag = -1;
	while (flag == -1)
	{
		cout << "Enter movie code (0 - " << movieDatabase.getNumMovies() - 1 << "): ";
		newBooking.setMovieCode(flag = inputAnInteger(0, movieDatabase.getNumMovies() - 1));
	}

	flag = -1;
	while (flag == -1)
	{
		cout << "Enter date code (0 - " << numDates << "): ";
		newBooking.setDateCode(flag = inputAnInteger(0, numDates));
		if (!movieDatabase.getMovie(newBooking.getMovieCode()).getDate(newBooking.getDateCode()))
			flag = -1;
	}
	
	flag = -1;
	while (flag == -1)
	{
		cout << "Enter session time code (0 - 16): ";
		newBooking.setSessionTimeCode(flag = inputAnInteger(0, 16));
		if (!movieDatabase.getMovie(newBooking.getMovieCode()).getSessionTime(newBooking.getSessionTimeCode()))
			flag = -1;
	}
	

	cout << "Movie: " << movieNames[newBooking.getMovieCode()] << endl;
	cout << "Date : " << availableDates[newBooking.getDateCode()] << endl;
	cout << "Show Time : " << hours[newBooking.getSessionTimeCode()] << endl;
	cout << "Price : Adult - " << movieDatabase.getMovie(newBooking.getMovieCode()).getPrice(0)
		<< ", Concession - " << movieDatabase.getMovie(newBooking.getMovieCode()).getPrice(1)
		<< ", Disability - " << movieDatabase.getMovie(newBooking.getMovieCode()).getPrice(2)
		<< ", Elderly - " << movieDatabase.getMovie(newBooking.getMovieCode()).getPrice(3) << endl;


	int numTicket[4] = { -1, -1, -1, -1 };

	while (numTicket[0] + numTicket[1] + numTicket[2] + numTicket[3] <= 0)
	{
		memset(numTicket, -1, sizeof(int)*4);
		while (numTicket[0] == -1)
		{
			cout << "Enter the number of adult tickets(0 - 6) :";
			numTicket[0] = inputAnInteger(0, 6);
		}

		while (numTicket[1] == -1)
		{
			cout << "Enter the number of concession tickets(0 - 6) : ";
			numTicket[1] = inputAnInteger(0, 6);
		}

		while (numTicket[2] == -1)
		{
			cout << "Enter the number of disability tickets(0 - 6) : ";
			numTicket[2] = inputAnInteger(0, 6);
		}

		while (numTicket[3] == -1)
		{
			cout << "Enter the number of elderly tickets(0 - 6) : ";
			numTicket[3] = inputAnInteger(0, 6);
		}

	}
	

	newBooking.setNumTickets(numTicket);

	newBooking.displayBooking(movieDatabase);

	selectSeats(newBooking);

	newBooking.setEmail(email);

	bookingDatabase.addBooking(newBooking);

	cin.ignore();

	cout << "Successful!!" << endl;	

}

void BuyTickets::selectSeats(Booking &newBooking)
{
	cout << "   A B C D E F G H I J K L" << endl;
	for (size_t i = 0; i < 8; i++)
	{
		cout << i << " ";
		for (size_t j = 0; j < 12; j++)
		{
			cout << setw(2)
				<< (movieDatabase.getMovie(newBooking.getMovieCode()).getOccupiedSeat(newBooking.getDateCode(), newBooking.getSessionTimeCode(), i, j) == true) ? "1" : "0";
		}
		cout << endl;
	}

	string seat[24];
	cout << "Select " << newBooking.getNumTickets() << " seats(e.g. 0A) : " << endl;
	for (size_t i = 0; i < newBooking.getNumTickets(); i++)
	{
		bool flag = false;
		do
		{
			cout << "? ";
			cin >> seat[i];
			if (!isdigit(seat[i][0]) || seat[i][1] > 'Z' || seat[i][1] < 'A')
			{
				cout << "Error input. Please try again.\n" << endl;
				flag = true;
				continue;
			}
			if (flag = movieDatabase.getMovie(newBooking.getMovieCode()).getOccupiedSeat(newBooking.getDateCode(), newBooking.getSessionTimeCode(), seat[i][0] - '0', seat[i][1] - 'A'))
				cout << "This seat bas been occupied.Please select another seat.\n" << endl;
			else
				movieDatabase.setMovieSeat(newBooking.getMovieCode(), newBooking.getDateCode(), newBooking.getSessionTimeCode(), seat[i][0] - '0', seat[i][1] - 'A');
		} while (flag);
	}
	newBooking.setSeletedSeats(seat, newBooking.getNumTickets());
}