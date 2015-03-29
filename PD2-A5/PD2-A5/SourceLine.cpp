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
	unsigned int pos = this->find('/');

	//if no find
	if (pos == -1)
		return;

	//if find '/', check next character
	//if next character is '/'
	//do delete comment
	if (*(this->begin()+pos+1) == '/')
	{
		this->erase(pos, this->getSize() - pos);
	}
}

void SourceLine::deleteStringConstants()
{
	// deletes all string constants in a sourceLine

	//try to find "
	unsigned int pos = this->find('\"');

	//if no found
	if (pos == -1)
		return;

	//if found ", delete character until next "
	
	this->erase(pos, this->find('\"', pos) - pos + 1);
}

void SourceLine::deleteCharacterConstants()
{
	// deletes all character constants in a sourceLine
	unsigned int pos = this->find('\'');

	//if not found
	if (pos == -1)
		return;

	//because length of character is 3 ( single quote * 2 + character)
	this->erase(pos, 3);
}

bool SourceLine::findBeginEnd(unsigned int &beginPos, unsigned int &endPos)
{

	beginPos = endPos = 0;

	while (beginPos < this->getSize() && !isalpha(*(this->begin() + beginPos)))
		beginPos++;

	if (beginPos > 0 && !isalpha(*(this->begin() + beginPos)))
	{
		return false;
	}

	endPos = beginPos;

	while (isalpha(*(this->begin() + endPos)) || isdigit(*(this->begin() + endPos)))
		endPos++;

	if (beginPos < endPos)
		return true;
	else
		return false;
}
