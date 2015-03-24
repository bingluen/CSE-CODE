// SourceLine class definition
#ifndef SOURCE_LINE_H
#define SOURCE_LINE_H

#include "String.h" // String class definition

class SourceLine : public String
{
public:
   SourceLine( const char * = "" ); // default constructor
   void deleteComments(); // delete the comment beginning with "//" in a sourceLine
   void deleteStringConstants(); // deletes all string constants in a sourceLine
   void deleteCharacterConstants(); // deletes all character constants in a sourceLine
   bool findBeginEnd( unsigned int &beginPos, unsigned int &endPos );
   // find the begining and ending positions of the first identifier in a sourceLine
};

#endif