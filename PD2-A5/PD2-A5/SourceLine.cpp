// SourceLine class member-function definitions.
#include <iostream>
using namespace std;
#include "SourceLine.h" // SourceLine class definition

// default/conversion constructor
SourceLine::SourceLine( const char *s ) : String( s )
{
}

/* Assigment 5 - implement SourceLine */

void deleteComments()
{
	// delete the comment beginning with "//" in a sourceLine
}

void deleteStringConstants()
{
	// deletes all string constants in a sourceLine
}

void deleteCharacterConstants()
{
	// deletes all character constants in a sourceLine
}

bool findBeginEnd(unsigned int &beginPos, unsigned int &endPos)
{
	// find the begining and ending positions of the first identifier in a sourceLine
}
