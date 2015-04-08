// Member-function definitions for class Iterator.
#include "Iterator.h" // include definition of class Iterator

// default constructor
template< typename T >
Iterator< T >::Iterator( T *p )
   : ptr( p )
{
}

// copy constructor
template< typename T >
Iterator< T >::Iterator( const Iterator< T > &iteratorToCopy )
{
   ptr = iteratorToCopy.ptr;
}

// overloaded dereference operator
template< typename T >
T& Iterator< T >::operator*() const
{
   return *ptr;
}

// overloaded assignment operator
template< typename T >
const Iterator< T >& Iterator< T >::operator=( const Iterator< T > &right )
{
   if( &right != this ) // avoid self-assignment
      ptr = right.ptr;
   return *this;
}

// overloaded prefix increment operator
template< typename T >
Iterator< T >& Iterator< T >::operator++()
{
   ++ptr;
   return *this;
}

// overloaded postfix increment operator
template< typename T >
Iterator< T > Iterator< T >::operator++( int )
{
   Iterator temp( *this );
   ptr++;
   return temp;
}

// overloaded prefix increment operator
template< typename T >
Iterator< T >& Iterator< T >::operator--()
{
   --ptr;
   return *this;
}

// overloaded postfix increment operator
template< typename T >
Iterator< T > Iterator< T >::operator--( int )
{
   Iterator temp( *this );
   ptr--;
   return temp;
}

template< typename T >
Iterator< T > Iterator< T >::operator+( int i )
{
   return Iterator< T >( ptr + i );
}

template< typename T >
Iterator< T > Iterator< T >::operator-( int i )
{
   return Iterator< T >( ptr - i );
}

template< typename T >
unsigned int Iterator< T >::operator-( Iterator< T > &right ) const
{
   return ptr - right.ptr;
}

// overloaded equality operator
template< typename T >
bool Iterator< T >::operator==( const Iterator< T > &right ) const
{
   return ptr == right.ptr;
}

// overloaded inequality operator
template< typename T >
bool Iterator< T >::operator!=( const Iterator< T > &right ) const
{
   return ptr != right.ptr;
}

// overloaded less operator
template< typename T >
bool Iterator< T >::operator<( const Iterator< T > &right ) const
{
   return ptr < right.ptr;
}

// overloaded less or equal operator
template< typename T >
bool Iterator< T >::operator<=( const Iterator< T > &right ) const
{
   return ptr <= right.ptr;
}

// overloaded greater operator
template< typename T >
bool Iterator< T >::operator>( const Iterator< T > &right ) const
{
   return ptr > right.ptr;
}

// overloaded greater or equal operator
template< typename T >
bool Iterator< T >::operator>=( const Iterator< T > &right ) const
{
   return ptr >= right.ptr;
}