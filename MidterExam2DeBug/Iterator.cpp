// Member-function definitions for class template Iterator
#include "Iterator.h" // include definition of class template Iterator

// default constructor
template< typename T >
Iterator< T >::Iterator( T *p )
   : ptr( p )
{
}

// copy constructor
template< typename T >
Iterator< T >::Iterator( const Iterator< T > &iteratorToCopy )
   : ptr( iteratorToCopy.ptr )
{
}

// overloaded dereference operator
template< typename T >
T& Iterator< T >::operator*() const
{
   return *ptr;
}


/* midter exam 2 implement */
template< typename T >
const Iterator<T> &Iterator< T >::operator=(const Iterator<T> &right)
{
	// assignment operator
	this->ptr = right.ptr;
	return *this;
}

template< typename T >
Iterator<T> Iterator< T >::operator++(int)
{
	// postincrement an iterator
	Iterator<T> temp(this->ptr);
	this->ptr++;
	return temp;
}

template< typename T >
Iterator<T> Iterator< T >::operator--(int)
{
	// postdecrement an iterator
	Iterator<T> temp(this->ptr);
	this->ptr--;
	return temp;
}

template< typename T >
Iterator<T> Iterator< T >::operator+(int i)
{
	// increment an iterator by i positions
	return *(new Iterator(this->ptr + i));
}

template< typename T >
Iterator<T> Iterator< T >::operator-(int i)
{
	// decrement an iterator by i positions
	return *(new Iterator(this->ptr - i));
}

template< typename T >
bool Iterator< T >::operator<(const Iterator<T> &right) const
{
	// compare iterators for less
	if (this->ptr < right.ptr)
		return true;
	else
		return false;
}

template< typename T >
bool Iterator< T >::operator>=(const Iterator<T> &right) const
{
	// compare iterators for greater or equal
	return !(this->operator<(right));
}

template< typename T >
bool Iterator< T >::operator>(const Iterator<T> &right) const
{
	// compare iterators for greater
	if (this->ptr > right.ptr)
		return true;
	else
		return false;
}

template< typename T >
int Iterator< T >::operator-(Iterator<T> it)
{
	return this->ptr - it.ptr;
}