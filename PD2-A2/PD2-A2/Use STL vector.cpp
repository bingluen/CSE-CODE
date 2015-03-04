// vector test program.
#include <iostream>
#include <iomanip>
using namespace std;
#include <vector> // include definition of class vector

int enterChoice();
void display( vector< int > integers );

void testDefaultConstructor();
void testRangeConstructor( vector< int > vec );
void testCopyConstructor( vector< int > integersToCopy );

void testAssign( int intArray[] );
void testResize( vector< int > integers );
void testReserve( vector< int > integers );
void testPush_back( vector< int > integers );
void testInsert( vector< int > integers );
void testErase( vector< int > integers );
void testSwap( vector< int > integers );

int main()
{
//   system("mode con:cols=60 lines=22");
   system( "color F0" );

   int intArray[ 20 ];
   for ( int i = 0; i < 20; i++ )
      intArray[ i ] = 10 + rand() % 90;

   vector< int > integers( intArray, intArray + 20 ); // call range constructor of class vector< int >

   int choice = enterChoice();

   switch ( choice )
   {
   case 1:
      testDefaultConstructor();
      break;
   case 2:
      testRangeConstructor( integers );
      break;
   case 3:
      testCopyConstructor( integers );
      break;
   case 4:
      testAssign( intArray );
      break;
   case 5:
      testResize( integers );
      break;
   case 6:
      testReserve( integers );
      break;
   case 7:
      testPush_back( integers );
      break;
   case 8:
      testInsert( integers );
      break;
   case 9:
      testErase( integers );
      break;
   case 10:
      testSwap( integers );
   } // end switch

   system( "pause" );
} // end main

int enterChoice()
{
   cout << "Enter your choice\n"
        << " 1 - test default constructor\n"
        << " 2 - test range constructor\n"
        << " 3 - test copy constructor\n"
        << " 4 - test assign\n"
        << " 5 - test resize\n"
        << " 6 - test reserve\n"
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

void display( vector< int > integers )
{
   for( unsigned int i = 0; i < integers.size(); i++ )
      cout << setw(3) << integers[ i ];
   cout << endl << endl;
}

void testDefaultConstructor()
{
   int size;
   cout << "Enter the number of elements in the integers: ";
   cin >> size;

   int value;
   cout << "Enter a value: ";
   cin >> value;

   vector< int > integers( size, value ); // call default constructor of class vector< int >

   cout << "\nsize: " << integers.size() << ",  capacity: " << integers.capacity() << endl;
   display( integers );
}

void testRangeConstructor( vector< int > vec )
{
   cout << "size: " << vec.size() << ",  capacity: " << vec.capacity() << endl;
   display( vec );

   unsigned int first;
   cout << "Enter the initial position: ";
   cin >> first;

   unsigned int last;
   cout << "Enter the final position: ";
   cin >> last;

   vector< int > integers( vec.begin() + first, vec.begin() + last ); // call range constructor of class vector< int >

   cout << "\nsize: " << integers.size() << ",  capacity: " << integers.capacity() << endl;
   display( integers );
}

void testCopyConstructor( vector< int > integersToCopy )
{
   cout << "integersToCopy.size: " << integersToCopy.size()
        << ",  integersToCopy.capacity: " << integersToCopy.capacity() << endl;
   display( integersToCopy );

   vector< int > integers( integersToCopy ); // call copy constructor of class vector< int >

   cout << "integers.size: " << integers.size() << ",  integers.capacity: " << integers.capacity() << endl;
   display( integers );
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

   vector< int > integers;
   integers.assign( intArray + first, intArray + last );

   cout << "\nintegers.size: " << integers.size() << ",  integers.capacity: " << integers.capacity() << endl;
   display( integers );
}

void testResize( vector< int > integers )
{
   cout << "Before resize: size = " << integers.size();
   cout << ",  capacity = " << integers.capacity() << endl;
   display( integers );

   unsigned int newSize;
   cout << "Enter a new size: ";
   cin >> newSize;
   integers.resize( newSize );

   cout << "\nAfter resize: size = " << integers.size();
   cout << ",  capacity = " << integers.capacity() << endl;
   display( integers );
}

void testReserve( vector< int > integers )
{
   cout << "Before reserve: size = " << integers.size();
   cout << ",  capacity = " << integers.capacity() << endl;
   display( integers );

   unsigned int newCapacity;
   cout << "Enter a new capacity: ";
   cin >> newCapacity;
   integers.reserve( newCapacity );

   cout << "\nAfter reserve: size = " << integers.size();
   cout << ",  capacity = " << integers.capacity() << endl;
   display( integers );
}

void testPush_back( vector< int > integers )
{
   cout << "Before push_back: size = " << integers.size();
   cout << ",  capacity = " << integers.capacity() << endl;
   display( integers );

   int value;
   cout << "Enter a value: ";
   cin >> value;
   integers.push_back( value );

   cout << "\nAfter push_back: size = " << integers.size();
   cout << ",  capacity = " << integers.capacity() << endl;
   display( integers );
}

void testInsert( vector< int > integers )
{
   cout << "Before insert: size = " << integers.size();
   cout << ",  capacity = " << integers.capacity() << endl;
   display( integers );

   unsigned int position;
   cout << "Enter the position: ";
   cin >> position;
   int value = integers.back();
   cout << "Enter a value: ";
   cin >> value;
   integers.insert( integers.begin() + position, value );

   cout << "\nAfter insert: size = " << integers.size();
   cout << ",  capacity = " << integers.capacity() << endl;
   display( integers );
}

void testErase( vector< int > integers )
{
   cout << "Before erase: size = " << integers.size();
   cout << ",  capacity = " << integers.capacity() << endl;
   display( integers );

   unsigned int position;
   cout << "Enter the position: ";
   cin >> position;
   integers.erase( integers.begin() + position );

   cout << "\nAfter erase: size = " << integers.size();
   cout << ",  capacity = " << integers.capacity() << endl;
   display( integers );
}

void testSwap( vector< int > integers )
{
   int intArray[ 10 ];
   for ( int i = 0; i < 10; i++ )
      intArray[ i ] = rand() % 100;

   vector< int > integersToSwap( intArray, intArray + 10 );

   cout << "Before swap: integers.size = " << integers.size();
   cout << ",  integers4.capacity = " << integers.capacity() << endl;
   display( integers );

   cout << "Before swap: integersToSwap.size = " << integersToSwap.size();
   cout << ",  integersToSwap.capacity = " << integersToSwap.capacity() << endl;
   display( integersToSwap );

   integers.swap( integersToSwap );

   cout << "After swap: integers.size = " << integers.size();
   cout << ",  integers.capacity = " << integers.capacity() << endl;
   display( integers );

   cout << "After swap: integersToSwap.size = " << integersToSwap.size();
   cout << ",  integersToSwap.capacity = " << integersToSwap.capacity() << endl;
   display( integersToSwap );
}