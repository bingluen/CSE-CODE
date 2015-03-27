#include <iostream>
#include <fstream>
using namespace std;
#include "Identifier.h" // Identifier class definition
#include "SourceLine.h" // SourceLine class definition

// return true if and only if identifiers[ pos ] belongs to identifiers[ 0 .. pos-1 ]
bool duplicate( Identifier identifiers[], int pos );

int main()
{
   ifstream inFile( "test.cpp", ios::in );

   // exit program if ifstream could not open file
   if ( !inFile ) 
   {
      cerr << "File could not be opened" << endl;
      system( "pause" );
      exit( 1 );
   }

   char source[ 200 ];
   SourceLine sourceLine;
   Identifier identifiers[ 1000 ];
   int numIdentifiers = -1;
   unsigned int beginPos = 0; // the position of the first alphanumeric character in the first identifier
   unsigned int endPos = 0; // one position next to the last alphanumeric character in the first identifier

   while( inFile.getline( source, sizeof( source ), '\n' ) )
   {
      sourceLine.assign( source, source + strlen( source ) );
      sourceLine.deleteComments(); // deletes the comment beginning with "//" in "sourceLine"
      sourceLine.deleteStringConstants(); // deletes all string constants in sourceLine
      sourceLine.deleteCharacterConstants(); // deletes all character constants in sourceLine

      // find the begining and ending positions of the first identifier in a sourceLine
      while( sourceLine.findBeginEnd( beginPos, endPos ) )
      {
         identifiers[ ++numIdentifiers ] = sourceLine.substr( beginPos, endPos - beginPos );
         sourceLine.erase( 0, endPos );
      }
   }

   for( int i = 0; i < numIdentifiers; i++ )
      if( !identifiers[ i ].keyword() && !duplicate( identifiers, i ) )
         cout << identifiers[ i ] << endl;

   system( "pause" );
}

/* Assignment 5 - implement*/

bool duplicate(Identifier identifiers[], int pos)
{
	for (int i = 0; i < pos; i++)
	{
		if (!strcmp(identifiers[i].begin(), identifiers[pos].begin()))
			return true;
	}

	return false;
}