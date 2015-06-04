// Iterator class definition and member-function definitions for class Iterator
#ifndef ITERATOR_H
#define ITERATOR_H

template< typename T >
class Iterator
{
public:
   Iterator( T *p = NULL );                         // default constructor
   Iterator( const Iterator< T > &iteratorToCopy ); // copy constructor

   T& operator*( ) const;  // dereference an iterator
   T* operator->( ) const; // class member access operator

   const Iterator< T > &operator=( const Iterator< T > &right ); // assignment operator

   Iterator< T >& operator++( );      // preincrement an iterator
   Iterator< T > operator++( int );  // postincrement an iterator

   bool operator==( const Iterator< T > &right ) const; // compare iterators for equality
   bool operator<( const Iterator< T > &right ) const;  // compare iterators for less
private:
   T *ptr; // keep a pointer to vector
}; // end class Iterator

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
T& Iterator< T >::operator*( ) const
{
   return *ptr;
}

template< typename T >
T* Iterator< T >::operator->( ) const
{
   return ptr;
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
Iterator< T >& Iterator< T >::operator++( )
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

// overloaded equality operator
template< typename T >
bool Iterator< T >::operator==( const Iterator< T > &right ) const
{
   return ptr == right.ptr;
}

// overloaded less operator
template< typename T >
bool Iterator< T >::operator<( const Iterator< T > &right ) const
{
   return ptr < right.ptr;
}

#endif