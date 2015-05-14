// SouthboundTimetable.h
// SouthboundTimetable class definition. Represents the southbound timetable.
#ifndef SOUTHBOUND_TIMETABLE_H
#define SOUTHBOUND_TIMETABLE_H

#include <vector> // class uses vector to store SouthboundTimetable objects
#include "Train.h" // Train class definition

#include <fstream>
using namespace std;

class SouthboundTimetable
{
public:
   SouthboundTimetable(); // call loadSouthboundTimetable()
   int getNumberOfTrains(); // returns the total number of southbound trains
   Train getTrain( int index ); // returns southboundTimetable[ index ]
private:
   vector< Train > southboundTimetable; // the southbound timetable

   void loadSouthboundTimetable(); // loads the southbound timetable from the file "Southbound timetable.dat"
}; // end class SouthboundTimetable
#endif // SOUTHBOUND_TIMETABLE_H
