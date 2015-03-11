// String test program.
#include <iostream>
#include <iomanip>
using namespace std;
#include "String.h" // include definition of class String

int enterChoice();
void testDefaultConstructor( char charArray[] );
void testCopyConstructor( String stringToCopy );
void testResize( String string );
void testReserve( String string );
void testAssign( char charArray[] );
void testErase1( String string );
void testErase2( String string );
void testFind( String string );
void testSubstr( String string );

int main()
{
//   system("mode con:cols=60 lines=22");
   system( "color F0" );

   char *alphabet = "abcdefghijklmnopqrstuvwxyz";

   unsigned int length;
   cout << "Enter the number of characters: ";
   cin >> length;

   char *charArray = new char[ length ];
   for ( unsigned int i = 0; i < length - 1; i++ )
      charArray[ i ] = alphabet[ rand() % 26 ];
   charArray[ length - 1 ] = '\0';

   String string( charArray );
   
   int choice = enterChoice();

      switch ( choice ) 
      {
         case 1:
            testDefaultConstructor( charArray );
            break;
         case 2:
            testCopyConstructor( string );
            break;
         case 3:
            testResize( string );
            break;
         case 4:
            testReserve( string );
            break;
         case 5:
            testAssign( charArray );
            break;
         case 6:
            testErase1( string );
            break;
         case 7:
            testErase2( string );
            break;
         case 8:
            testFind( string );
            break;
         case 9:
            testSubstr( string );
      } // end switch

   system("pause");
} // end main

int enterChoice()
{
   cout << "\nEnter your choice\n"
        << "1 - test default constructor\n"
        << "2 - test copy constructor\n"
        << "3 - resize( unsigned int n )\n"
        << "4 - reserve( unsigned int n )\n"
        << "5 - assign( unsigned int n, char c )\n"
        << "6 - erase( unsigned int pos, unsigned int len )\n"
        << "7 - erase( char *first, char *last )\n"
        << "8 - find( char c, unsigned int pos )\n"
        << "9 - substr( unsigned int pos, unsigned int len )\n";

   int menuChoice;
   do {
      cout << "? ";
      cin >> menuChoice;
   } while ( ( menuChoice < 1 ) || ( menuChoice >= 10 ) );
   cout << endl;

   return menuChoice;
} // end function enterChoice

void testDefaultConstructor( char charArray[] )
{
   cout << "charArray:" << endl;
   cout << charArray << endl << endl;

   unsigned int position;
   cout << "Enter the position: ";
   cin >> position;

   int len;
   cout << "Enter the number of characters in the string: ";
   cin >> len;

   String string( charArray + position, len ); // call default constructor of class String

   cout << "\nsize: " << string.getSize() << ",  capacity: " << string.getCapacity() << endl;
   string.display();
}

void testCopyConstructor( String stringToCopy )
{
   cout << "vectorToCopy.size: " << stringToCopy.getSize()
        << ",  vectorToCopy.capacity: " << stringToCopy.getCapacity() << endl;
   stringToCopy.display();

   String string( stringToCopy ); // call copy constructor of class Vector

   cout << "vector.size: " << string.getSize() << ",  vector.capacity: " << string.getCapacity() << endl;
   string.display();
}

void testResize( String string )
{
   cout << "Before resize: size = " << string.getSize();
   cout << ",  capacity = " << string.getCapacity() << endl;
   string.display();

   unsigned int newSize;
   cout << "Enter a new size: ";
   cin >> newSize;
   string.resize( newSize );

   cout << "\nAfter resize: size = " << string.getSize();
   cout << ",  capacity = " << string.getCapacity() << endl;
   string.display();
}

void testReserve( String string )
{
   cout << "Before reserve: size = " << string.getSize();
   cout << ",  capacity = " << string.getCapacity() << endl;
   string.display();

   unsigned int newCapacity;
   cout << "Enter a new capacity: ";
   cin >> newCapacity;

   string.reserve( newCapacity );

   cout << "\nAfter reserve: size = " << string.getSize();
   cout << ",  capacity = " << string.getCapacity() << endl;
   string.display();
}

void testAssign( char charArray[] )
{
   cout << "charArray:" << endl;
   cout << charArray << endl << endl;

   unsigned int first;
   cout << "Enter the initial position: ";
   cin >> first;

   unsigned int last;
   cout << "Enter the final position: ";
   cin >> last;

   String string;
   string.assign( charArray + first, charArray + last );

   cout << "\nstring.size: " << string.getSize() << ",  string.capacity: " << string.getCapacity() << endl;
   string.display();
}

void testErase1( String string )
{
   cout << "Before erase: size = " << string.getSize();
   cout << ",  capacity = " << string.getCapacity() << endl;
   string.display();

   unsigned int position;
   cout << "Enter the position: ";
   cin >> position;

   int length;
   cout << "Enter the number of characters to erase: ";
   cin >> length;

   string.erase( position, length );

   cout << "\nAfter erase: size = " << string.getSize();
   cout << ",  capacity = " << string.getCapacity() << endl;
   string.display();
}

void testErase2( String string )
{
   cout << "Before erase: size = " << string.getSize();
   cout << ",  capacity = " << string.getCapacity() << endl;
   string.display();

   unsigned int first;
   cout << "Enter the initial position: ";
   cin >> first;

   unsigned int last;
   cout << "Enter the final position: ";
   cin >> last;

   string.erase( string.begin() + first, string.begin() + last );

   cout << "\nAfter erase: size = " << string.getSize();
   cout << ",  capacity = " << string.getCapacity() << endl;
   string.display();
}

void testFind( String string )
{
   cout << "size = " << string.getSize();
   cout << ",  capacity = " << string.getCapacity() << endl;
   string.display();

   char c;
   cout << "Enter a character: ";
   cin >> c;

   unsigned int position;
   cout << "Enter the starting position to be considered in the search: ";
   cin >> position;

   cout << "\nAThe position of the first character of the first match: "
        << string.find( c, position ) << endl << endl;
}

void testSubstr( String string )
{
   cout << "A string: size = " << string.getSize();
   cout << ",  capacity = " << string.getCapacity() << endl;
   string.display();

   unsigned int position;
   cout << "Enter the position: ";
   cin >> position;

   int length;
   cout << "Enter the number of characters in the string: ";
   cin >> length;

   String subString( string.substr( position, length ) );

   cout << "\nThe substring: size = " << subString.getSize();
   cout << ",  capacity = " << subString.getCapacity() << endl;
   subString.display();
}