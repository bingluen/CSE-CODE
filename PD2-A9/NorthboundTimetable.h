// NorthboundTimetable.h
// NorthboundTimetable class definition. Represents the northbound timetable.
#ifndef NORTHBOUND_TIMETABLE_H
#define NORTHBOUND_TIMETABLE_H

#include <vector> // class uses vector to store NorthboundTimetable objects
#include "Train.h" // Train class definition

class NorthboundTimetable
{
public:
   NorthboundTimetable(); // call loadNorthboundTimetable()
   int getNumberOfTrains(); // returns the total number of northbound trains
   Train getTrain( int index ); // returns northboundTimetable[ index ]
private:
   vector< Train > northboundTimetable; // the northbound timetable

   void loadNorthboundTimetable(); // loads the northbound timetable from the file "Northbound timetable.dat"
}; // end class NorthboundTimetable
#endif // NORTHBOUND_TIMETABLE_H