// MovieDatabase class definition
#ifndef MOVIE_DATABASE_H
#define MOVIE_DATABASE_H

#include "Vector.h"
#include "Movie.h" // Movie class definition

class MovieDatabase
{
public:
   MovieDatabase(); // calls loadMovies()

   ~MovieDatabase(); // calls saveMovies()

   int getNumMovies();

   Movie getMovie( int movieCode ); // return the movie object containing specified movieCode

   void setMovieSeat( int movieCode, int dateCode, int sessionTimeCode, int row, int col );

   void displaySessionTimes( char movieNames[][ 60 ], char availableDates[][ 12 ] );
private:
   Vector< Movie > movies; // vector of the movies

   void loadMovies(); // loads movies from the file Movies.dat
   void saveMovies(); // stores movies into the file Movies.dat
}; // end class MovieDatabase

#endif // MOVIE_DATABASE_H