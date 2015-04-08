// Member-function definitions for class HugeInteger< T >.
#include "HugeInteger.h" // include definition of class HugeInteger< T > 
#include "Vector.cpp" // include definition of class Vector 
#include "Iterator.cpp" // include definition of class Iterator

// default constructor
template< typename T >
HugeInteger< T >::HugeInteger()
   : Vector()
{
}

// constructor
template< typename T >
HugeInteger< T >::HugeInteger( unsigned int size )
   : Vector( size, 0 )
{
}

// copy constructor
template< typename T >
HugeInteger< T >::HugeInteger( HugeInteger< T > &integerToCopy )
   : Vector( integerToCopy )
{
}

// destructor
template< typename T >
HugeInteger< T >::~HugeInteger()
{
}

// load a HugeInteger from a text file
template< typename T >
void HugeInteger< T >::load( ifstream &inFile )
{
   char digit;
   while( ( digit = inFile.get() ) != '\n' )
      push_back( digit - '0' );

   iterator it1( begin() );
   iterator it2( end() - 1 );
   T temp;
   for( ; it1 < it2; ++it1, --it2 )
   {
      temp = *it1;
      *it1 = *it2;
      *it2 = temp;
   }
}

// overloaded assignment operator;
// const return avoids: ( a1 = a2 ) = a3
template< typename T >
const HugeInteger< T > &HugeInteger< T >::operator=( const HugeInteger< T > &right )
{
   Vector< T >::operator=( right );

   return *this; // enables x = y = z, for example
}

// addition operator; HugeInteger< T > + HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator+( HugeInteger< T > op2 )
{
   unsigned int size = getSize();
   unsigned int op2Size = op2.getSize();
   unsigned int sumSize = ( size >= op2Size ) ? size + 1 : op2Size + 1;

   HugeInteger< T > sum( sumSize );

   for( iterator it1 = begin(), it3 = sum.begin(); it1 < end(); it1++, it3++ )
      *it3 = *it1;

   for( iterator it2 = op2.begin(), it3 = sum.begin(); it2 < op2.end(); it2++, it3++ )
      *it3 += *it2;

   for( iterator it3 = sum.begin(); it3 < sum.end() - 1; it3++ ) 
      if( *it3 > 9 ) 
      {
         *it3 -= 10;
         ( *( it3 + 1 ) )++;
      }

   if( *( sum.end() - 1 ) == 0 )
      sum.resize( sumSize - 1 );

   return sum;
} // end function operator+

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
template< typename T >
void HugeInteger< T >::divideByTen()
{
   for( iterator it = begin() + 1; it < end(); it++ )
      *( it - 1 ) = *it;
   resize( getSize() - 1 );
}

// function that tests if a HugeInteger is zero
template< typename T >
bool HugeInteger< T >::zero()
{
   for( iterator it = begin(); it < end(); it++ )
      if ( *it != 0 )
         return false;
         
   return true;
}

// overloaded output operator for class HugeInteger
template< typename T >
ostream &operator<<( ostream &output, HugeInteger< T > &hugeInteger )
{
   Vector< T >::iterator it;
   if( hugeInteger.getSize() == 0 )
      output << 0;
   else
   {
      for( it = hugeInteger.end() - 1; it > hugeInteger.begin(); it-- )
         output << *it;
      output << *it;
   }

   return output; // enables cout << x << y;
}

/* Assignment 7 - implement*/

template < typename T >
bool HugeInteger< T >::operator<(HugeInteger< T > &)
{
	// less than
}

template < typename T >
bool HugeIntegr< T >::operator>(HugeInteger< T > &)
{
	// greater than
}

template < typename T >
bool HugeInteger< T >::operator<=(HugeInteger< T > &)
{
	// less than or equal
}

template < typename T >
bool HugeInteger< T >::operator>=(HugeInteger< вт > &)
{
	// greater than or equal to
}

template < typename T >
HugeInteger< T > HugeInteger< T >::operator-(HugeInteger< T > &op2)
{
	// subtraction operator; HugeInteger - HugeInteger
}

template < typename T >
HugeInteger< T > HugeInteger< T >::operator*(HugeInteger< T > op2)
{
	// multiplication operator; HugeInteger * HugeInteger
}
template < typename T >
HugeInteger< T > HugeInteger< T >::operator/(HugeInteger< T > op2)
{
	// division operator; HugeInteger / HugeInteger
}

template < typename T >
HugeInteger< T > HugeInteger< T >::operator%(HugeInteger< T > op2)
{
	// modulus operator; HugeInteger % HugeInteger
}

template < typename T >
HugeInteger< T > &HugeInteger< T >::operator++()
{
	// prefix increment operator
}

template < typename T >
HugeInteger operator++(int)
{
	// postfix increment operator
}
