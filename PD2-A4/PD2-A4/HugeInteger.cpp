// Member-function definitions for class HugeInteger.
#include <iostream>
using namespace std;
#include "HugeInteger.h" // include definition of class HugeInteger 

// default constructor
HugeInteger::HugeInteger()
   : integer()
{
} // end HugeInteger default constructor

// constructor
HugeInteger::HugeInteger( unsigned int size )
   : integer( size, 0 )
{
} // end HugeInteger constructor

// copy constructor
HugeInteger::HugeInteger( const HugeInteger &integerToCopy )
   : integer( integerToCopy.integer )
{
} // end HugeInteger copy constructor

// load a HugeInteger from a text file
void HugeInteger::load( ifstream &inFile )
{
   char digit;
   while( ( digit = inFile.get() ) != '\n' )
      integer.push_back( digit - '0' );

   unsigned int size = integer.getSize();
   int temp;
   for( unsigned int i = 0; i <= ( size - 1 ) / 2; i++ )
   {
      temp = integer[ i ];
      integer[ i ] = integer[ size - i - 1 ];
      integer[ size - i - 1 ] = temp;
   }
}

// overloaded assignment operator;
// const return avoids: ( a1 = a2 ) = a3
const HugeInteger &HugeInteger::operator=( const HugeInteger &right )
{
   integer = right.integer;
   return *this; // enables x = y = z, for example
} // end function operator=

// function that tests if two HugeIntegers are equal
bool HugeInteger::operator==( const HugeInteger &right ) const
{
   return ( integer == right.integer );
} // end function operator==

// function that tests if two HugeIntegers are not equal
bool HugeInteger::operator!=( const HugeInteger &right ) const
{
   return ( integer != right.integer ); 
} // end function operator!=

// addition operator; HugeInteger + HugeInteger
HugeInteger HugeInteger::operator+( const HugeInteger op2 ) const
{
   unsigned int size = integer.getSize();
   unsigned int op2Size = op2.integer.getSize();
   unsigned int sumSize = ( size >= op2Size ) ? size + 1 : op2Size + 1;

   HugeInteger sum( sumSize );

   for( unsigned int i = 0; i < size; i++ )
      sum.integer[ i ] = integer[ i ];

   for( unsigned int i = 0; i < op2Size; i++ )
      sum.integer[ i ] += op2.integer[ i ];

   for( unsigned int i = 0; i < sumSize - 1; i++ )
      if( sum.integer[ i ] > 9 ) 
      {
         sum.integer[ i ] -= 10;
         sum.integer[ i + 1 ]++;
      }

   if( sum.integer[ sumSize - 1 ] == 0 )
      sum.integer.resize( sumSize - 1 );

   return sum;
} // end function operator+

// subtraction operator; HugeInteger - HugeInteger
HugeInteger HugeInteger::operator-( const HugeInteger op2 ) const
{
   HugeInteger zero( 1 );

   // return if first value is smaller; we are not handling negatives
   if( *this < op2 )
   {
      cout << "Error: Tried to subtract larger value from smaller value.\n";
      return zero;
   }

   if( *this == op2 )
      return zero;

   return difference;
} // end function operator-

// division operator; HugeInteger / HugeInteger
HugeInteger HugeInteger::operator/( const HugeInteger op2 ) const
{
   HugeInteger zero( 1 );
   if( *this < op2 )
      return zero;


   return quotient;
} // end function operator/

// modulus operator; HugeInteger % HugeInteger
HugeInteger HugeInteger::operator%( const HugeInteger op2 ) const
{
   if( *this < op2 )
      return *this;


   return remainder;
} // end function operator%

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
void HugeInteger::divideByTen()
{
   unsigned int size = integer.getSize();
   for( unsigned int i = 1; i < size; i++ )
      integer[ i - 1 ] = integer[ i ];
   integer.resize( size - 1 );
} // end function divideByTen

// function that tests if a HugeInteger is zero
bool HugeInteger::zero()
{
   for ( unsigned int i = 0; i < integer.getSize(); i++ )
      if ( integer[ i ] != 0 )
         return false;
         
   return true;
} // end function zero

// overloaded output operator for class Array 
ostream &operator<<( ostream &output, const HugeInteger &hugeInteger )
{
   unsigned int size = hugeInteger.integer.getSize();
   if( size == 0 )
      output << 0;
   else
      for( int i = size - 1; i >= 0; i-- )
         output << hugeInteger.integer[ i ];

   return output; // enables cout << x << y;
} // end function operator<<