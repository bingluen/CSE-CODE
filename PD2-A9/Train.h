// Train.h
// Train class definition. Represents a train.
#ifndef TRAIN_H
#define TRAIN_H

#include <string>
using namespace std;

class Train
{
public:
   Train( string = "", string * = NULL ); // constructor initializes data members
   string getTrainNumber();
   string * getDepartureTimes( string * ); // returns the departure times of a train for all stations
private:
   char trainNumber[ 8 ]; // used to identify a train
   char departureTimes[ 8 ][ 8 ]; // the departure time of a train for each station

   void setTrainNumber( string );
   void setDepartureTimes( string * );
};

#endif