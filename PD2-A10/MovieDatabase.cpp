// MovieDatabase.cpp
// Member-function definitions for class MovieDatabase
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace::std;
#include "MovieDatabase.h" // MovieDatabase class definition

extern char hours[ 17 ][ 8 ];

// MovieDatabase default constructor loads movies from the file Movies.dat
MovieDatabase::MovieDatabase()
{
   loadMovies();
}

// MovieDatabase destructor saves movies into the file Movies.dat
MovieDatabase::~MovieDatabase()
{
   saveMovies();
}

int MovieDatabase::getNumMovies()
{
   return movies.getSize();
}

Movie MovieDatabase::getMovie( int movieCode )
{
   return movies[ movieCode ];
}

void MovieDatabase::setMovieSeat( int movieCode, int dateCode, int sessionTimeCode, int row, int col )
{
   movies[ movieCode ].setOccupiedSeat( dateCode, sessionTimeCode, row, col );
}

void MovieDatabase::displaySessionTimes(char movieNames[][60], char availableDates[][12])
{
	for (size_t i = 0; i < movies.getSize(); i++)
	{
		cout << setw(2) << movies[i].getMovieCode() << setw(2) << ". " << "Movie: " << movieNames[i] << endl;
		cout << setw(4) << " " << "Date: ";
		for (size_t j = 0; j < 9; j++)
		{
			if (movies[i].getDate(j))
				cout << setw(2) << j << setw(2) << ". " << availableDates[j] << ", ";
		}
		cout << endl;
		cout << setw(4) << " " << "Session Time: ";
		for (size_t j = 0; j < 17; j++)
		{
			if (movies[i].getSessionTime(j))
				cout << setw(2) << j << setw(2) << ". " << hours[j] << ", ";
		}

		cout << endl;
	}
}

void MovieDatabase::loadMovies()
{
	// loads movies from the file Movies.dat
	ifstream loadFile("Movies.dat", ios::in | ios::binary);

	loadFile.seekg(0, ios::end);

	int conut = loadFile.tellg() / sizeof(movie);

	loadFile.seekg(0, ios::beg);

	for (size_t i = 0; i < conut ;i++)
	{
		movie data;
		loadFile.read(reinterpret_cast<char *>(&data), sizeof(movie));
		Movie newMovie;
		newMovie.setDates(data.dates);
		newMovie.setMovieCode(data.movieCode);
		newMovie.setOccupiedSeats(data.occupiedSeats);
		newMovie.setPrices(data.prices);
		newMovie.setSessionTimes(data.sessionTimes);

		this->movies.push_back(newMovie);
	}
	loadFile.close();
}

void MovieDatabase::saveMovies()
{
	// stores movies into the file Movies.dat

	ofstream saving("Movies.dat", ios::out | ios::binary);

	for (size_t i = 0; i < movies.getSize(); i++)
	{
		movie data;
		
		/* ¥]¦¨structure .. */
		
		//date
		for (size_t j = 0; j < 9; j++)
			data.dates[j] = movies[i].getDate(j);

		data.movieCode = movies[i].getMovieCode();

		//occupiedSeat
		for (size_t j = 0; j < 9; j++)
		{
			for (size_t k = 0; k < 17; k++)
			{
				for (size_t l = 0; l < 8; l++)
				{
					for (size_t m = 0; m < 12; m++)
					{
						data.occupiedSeats[j][k][l][m] = movies[i].getOccupiedSeat(j, k, l, m);
					}
				}
			}
		}

		for (size_t j = 0; j < 4; j++)
		{
			data.prices[j] = movies[i].getPrice(j);
		}

		for (size_t j = 0; j < 17; j++)
		{
			data.sessionTimes[j] = movies[i].getSessionTime(j);
		}

		saving.write(reinterpret_cast <char *> (&data), sizeof(movie));
	}

	saving.close();
}