// HugeInteger test program
#include <iostream>
#include "HugeInteger.cpp" // include member-function definitions for class template HugeInteger 

int enterChoice();

template< typename T >
void loadHugeInteger( HugeInteger< T > &hugeInteger );

template< typename T >
void testHugeIntegerOperators( HugeInteger< T > hugeInteger );

int main()
{
   HugeInteger< int > hugeInteger1;
   HugeInteger< unsigned int > hugeInteger2;
   HugeInteger< short int > hugeInteger3;
   HugeInteger< unsigned short int > hugeInteger4;

   int choice = enterChoice();

   switch( choice )
   {
   case 1:
      loadHugeInteger( hugeInteger1 );
      testHugeIntegerOperators( hugeInteger1 );
      break;
   case 2:
      loadHugeInteger( hugeInteger2 );
      testHugeIntegerOperators( hugeInteger2 );
      break;
   case 3:
      loadHugeInteger( hugeInteger3 );
      testHugeIntegerOperators( hugeInteger3 );
      break;
   case 4:
      loadHugeInteger( hugeInteger4 );
      testHugeIntegerOperators( hugeInteger4 );
   }

   system( "pause" );
} // end main

int enterChoice()
{
   cout << "Enter your choice\n"
      << " 1 - test int\n"
      << " 2 - test unsigned int\n"
      << " 3 - test short int\n"
      << " 4 - test unsigned short int\n";

   int menuChoice;
   do {
      cout << "? ";
      cin >> menuChoice;
   } while( ( menuChoice < 1 ) || ( menuChoice > 4 ) );
   cout << endl;

   return menuChoice;
} // end function enterChoice

template< typename T >
void loadHugeInteger( HugeInteger< T > &hugeInteger )
{
   // ifstream constructor opens the file
   ifstream inFile( "hugeIntegers.txt", ios::in );

   // exit program if ifstream could not open file
   if( !inFile )
   {
      cout << "File could not be opened" << endl;
      system( "pause" );
      exit( 1 );
   }

   hugeInteger.load( inFile );

   inFile.close();
}

template< typename T >
void testHugeIntegerOperators( HugeInteger< T > hugeInteger )
{
   HugeInteger< T > sqrt( hugeInteger.squareRoot() );
   cout << "The square root of\n" << hugeInteger << "\nis\n" << sqrt << endl << endl;

   cout << "The number " << hugeInteger << " must fall in between the following two numbers:\n\n";

   if( sqrt.square() < hugeInteger )
      cout << "The square of " << sqrt << ":\n" << sqrt.square() << endl << endl;

   sqrt++;
   if( hugeInteger < sqrt.square() )
      cout << "The square of " << sqrt << ":\n" << sqrt.square() << endl << endl;
}