// Vector test program.
#include <iostream>
#include <iomanip>
using namespace std;
#include "Vector.h" // include definition of class Vector

int enterChoice();

void testDefaultConstructor();
void testRangeConstructor( Vector vec );
void testCopyConstructor( Vector vectorToCopy );

void testResize( Vector vector );
void testReserve( Vector vector );
void testAssign( int intArray[] );
void testPush_back( Vector vector );
void testInsert( Vector vector );
void testErase( Vector vector );
void testSwap( Vector vector );

int main()
{
//   system("mode con:cols=60 lines=22");
   system( "color F0" );

   int intArray[ 20 ];
   for ( int i = 0; i < 20; i++ )
      intArray[ i ] = 10 + rand() % 90;

   Vector vector( intArray, intArray + 20 ); // call range constructor of class Vector

   int choice = enterChoice();

   switch ( choice )
   {
   case 1:
      testDefaultConstructor();
      break;
   case 2:
      testRangeConstructor( vector );
      break;
   case 3:
      testCopyConstructor( vector );
      break;
   case 4:
      testResize( vector );
      break;
   case 5:
      testReserve( vector );
      break;
   case 6:
      testAssign( intArray );
      break;
   case 7:
      testPush_back( vector );
      break;
   case 8:
      testInsert( vector );
      break;
   case 9:
      testErase( vector );
      break;
   case 10:
      testSwap( vector );
   } // end switch

   system( "pause" );
} // end main

int enterChoice()
{
   cout << "Enter your choice\n"
        << " 1 - test default constructor\n"
        << " 2 - test range constructor\n"
        << " 3 - test copy constructor\n"
        << " 4 - test resize\n"
        << " 5 - test reserve\n"
        << " 6 - test assign\n"
        << " 7 - test push_back\n"
        << " 8 - test insert\n"
        << " 9 - test erase\n"
        << "10 - test swap\n";

   int menuChoice;
   do {
      cout << "? ";
      cin >> menuChoice;
   } while ( ( menuChoice < 1 ) || ( menuChoice >= 11 ) );
   cout << endl;

   return menuChoice;
}

void testDefaultConstructor()
{
   int size;
   cout << "Enter the number of elements in the vector: ";
   cin >> size;

   int value;
   cout << "Enter a value: ";
   cin >> value;

   Vector vector( size, value ); // call default constructor of class Vector

   cout << "\nsize: " << vector.getSize() << ",  capacity: " << vector.getCapacity() << endl;
   vector.display();
}

void testRangeConstructor( Vector vec )
{
   cout << "size: " << vec.getSize() << ",  capacity: " << vec.getCapacity() << endl;
   vec.display();

   unsigned int first;
   cout << "Enter the initial position: ";
   cin >> first;

   unsigned int last;
   cout << "Enter the final position: ";
   cin >> last;

   Vector vector( vec.begin() + first, vec.begin() + last ); // call range constructor of class Vector

   cout << "\nsize: " << vector.getSize() << ",  capacity: " << vector.getCapacity() << endl;
   vector.display();
}

void testCopyConstructor( Vector vectorToCopy )
{
   cout << "vectorToCopy.size: " << vectorToCopy.getSize()
        << ",  vectorToCopy.capacity: " << vectorToCopy.getCapacity() << endl;
   vectorToCopy.display();

   Vector vector( vectorToCopy ); // call copy constructor of class Vector

   cout << "vector.size: " << vector.getSize() << ",  vector.capacity: " << vector.getCapacity() << endl;
   vector.display();
}

void testResize( Vector vector )
{
   cout << "Before resize: size = " << vector.getSize();
   cout << ",  capacity = " << vector.getCapacity() << endl;
   vector.display();

   unsigned int newSize;
   cout << "Enter a new size: ";
   cin >> newSize;

   vector.resize( newSize );

   cout << "\nAfter resize: size = " << vector.getSize();
   cout << ",  capacity = " << vector.getCapacity() << endl;
   vector.display();
}

void testReserve( Vector vector )
{
   cout << "Before reserve: size = " << vector.getSize();
   cout << ",  capacity = " << vector.getCapacity() << endl;
   vector.display();

   unsigned int newCapacity;
   cout << "Enter a new capacity: ";
   cin >> newCapacity;

   vector.reserve( newCapacity );

   cout << "\nAfter reserve: size = " << vector.getSize();
   cout << ",  capacity = " << vector.getCapacity() << endl;
   vector.display();
}

void testAssign( int intArray[] )
{
   cout << "intArray:" << endl;
   for ( int i = 0; i < 20; i++ )
      cout << setw(3) << intArray[ i ];
   cout << endl << endl;

   unsigned int first;
   cout << "Enter the initial position: ";
   cin >> first;

   unsigned int last;
   cout << "Enter the final position: ";
   cin >> last;

   Vector vector;
   vector.assign( intArray + first, intArray + last );

   cout << "\nvector.size: " << vector.getSize() << ",  vector.capacity: " << vector.getCapacity() << endl;
   vector.display();
}

void testPush_back( Vector vector )
{
   cout << "Before push_back: size = " << vector.getSize();
   cout << ",  capacity = " << vector.getCapacity() << endl;
   vector.display();

   int value;
   cout << "Enter a value: ";
   cin >> value;

   vector.push_back( value );

   cout << "\nAfter push_back: size = " << vector.getSize();
   cout << ",  capacity = " << vector.getCapacity() << endl;
   vector.display();
}

void testInsert( Vector vector )
{
   cout << "Before insert: size = " << vector.getSize();
   cout << ",  capacity = " << vector.getCapacity() << endl;
   vector.display();

   unsigned int position;
   cout << "Enter the position: ";
   cin >> position;
   int value = vector.back();
   cout << "Enter a value: ";
   cin >> value;

   vector.insert( vector.begin() + position, value );

   cout << "\nAfter insert: size = " << vector.getSize();
   cout << ",  capacity = " << vector.getCapacity() << endl;
   vector.display();
}

void testErase( Vector vector )
{
   cout << "Before erase: size = " << vector.getSize();
   cout << ",  capacity = " << vector.getCapacity() << endl;
   vector.display();

   unsigned int position;
   cout << "Enter the position: ";
   cin >> position;

   vector.erase( vector.begin() + position );

   cout << "\nAfter erase: size = " << vector.getSize();
   cout << ",  capacity = " << vector.getCapacity() << endl;
   vector.display();
}

void testSwap( Vector vector )
{
   int intArray[ 10 ];
   for ( int i = 0; i < 10; i++ )
      intArray[ i ] = rand() % 100;

   Vector vectorToSwap( intArray, intArray + 10 );

   cout << "Before swap: vector.size = " << vector.getSize();
   cout << ",  vector4.capacity = " << vector.getCapacity() << endl;
   vector.display();

   cout << "Before swap: vectorToSwap.size = " << vectorToSwap.getSize();
   cout << ",  vectorToSwap.capacity = " << vectorToSwap.getCapacity() << endl;
   vectorToSwap.display();

   vector.swap( vectorToSwap );

   cout << "After swap: vector.size = " << vector.getSize();
   cout << ",  vector.capacity = " << vector.getCapacity() << endl;
   vector.display();

   cout << "After swap: vectorToSwap.size = " << vectorToSwap.getSize();
   cout << ",  vectorToSwap.capacity = " << vectorToSwap.getCapacity() << endl;
   vectorToSwap.display();
}