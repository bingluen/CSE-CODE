// SourceLine class member-function definitions.
#include <iostream>
using namespace std;
#include "SourceLine.h" // SourceLine class definition

// default/conversion constructor
SourceLine::SourceLine( const char *s ) : String( s )
{
}

/* Assigment 5 - implement SourceLine */

void SourceLine::deleteComments()
{
	// delete the comment beginning with "//" in a sourceLine

}

void SourceLine::deleteStringConstants()
{
	// deletes all string constants in a sourceLine

}

void SourceLine::deleteCharacterConstants()
{
	// deletes all character constants in a sourceLine
}

bool SourceLine::findBeginEnd(unsigned int &beginPos, unsigned int &endPos)
{
	// find the begining and ending positions of the first identifier in a sourceLine
}
