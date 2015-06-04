// Movie class definition
#ifndef MOVIE_H
#define MOVIE_H

class Movie
{
public:
   Movie();
   void setMovieCode( int theMovieCode );
   int getMovieCode();
   void setPrices( int thePrices[] );
   int getPrice( int ticketType );
   void setDates( bool theDates[] );
   bool getDate( int dateCode );
   void setSessionTimes( bool theSessionTimes[] );
   bool getSessionTime( int sessionTimeCode );
   void setOccupiedSeats( bool theOccupiedSeats[][ 17 ][ 8 ][ 12 ] );
   void setOccupiedSeat( int dateCode, int sessionTimeCode, int row, int col );
   bool getOccupiedSeat( int dateCode, int sessionTimeCode, int row, int col );

private:
   int movieCode;
   int prices[ 4 ]; // prices[0]:adult, prices[1]:concession, prices[2]:disability, prices[3]:elderly
   bool dates[ 9 ]; // dates[i] is true if and only if the movie is offered on i-th date
   bool sessionTimes[ 17 ];
   bool occupiedSeats[ 9 ][ 17 ][ 8 ][ 12 ]; // occupiedSeats[i][j] is the occupied Seats for all accounts
};                                           // at j-th session time on i-th date

#endif