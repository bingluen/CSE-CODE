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