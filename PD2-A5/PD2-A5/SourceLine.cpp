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
	unsigned int pos;

	// find first '/'
	pos = this->find('/', 0); 

	//if can't find (pos ==  -1), break
	if (pos == -1)
		return;

	if (this->find('/', pos) - pos == 1)
	{
		// if find second '/' -> delete comment
		this->resize(pos - 1);
	}
}

void SourceLine::deleteStringConstants()
{
	// deletes all string constants in a sourceLine
	unsigned int pos;
	pos = this->find('\"', 0);
	if (pos != -1)
		this->erase(pos, this->find('\"', pos));

}

void SourceLine::deleteCharacterConstants()
{
	// deletes all character constants in a sourceLine
	unsigned int pos;
	pos = this->find('\"', 0);
	if (pos != -1)
		this->erase(pos, this->find('\'', pos));
}

bool SourceLine::findBeginEnd(unsigned int &beginPos, unsigned int &endPos)
{
	// find the begining and ending positions of the first identifier in a sourceLine
	char *ptr = strtok(this->begin(), " ,();*#:<>[]=+-*/{}!?&|\\%\'\"");

	//if it is number, search next
	while (ptr != NULL && isdigit(*ptr))
	{
		ptr = strtok(NULL, " ,();*#:<>[]=+-*/{}!?&|\\%\'\"");
	}

	if (ptr == NULL)
		return false;

	/*
		example
		int identifiers; // \\ ?!?@
		   ||		   |
		  \0|         \0
		    |<- len -> |
		beginPos      beginPos+strlen(beginPos)
	*/

	

	beginPos = ptr - this->begin();

	endPos = beginPos + strlen(ptr);

	return true;
}
