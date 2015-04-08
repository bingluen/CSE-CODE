// Member-function definitions for class Vector.
#include "Vector.h" // include definition of class Vector 

// default constructor
template< typename T >
Vector< T >::Vector( unsigned int n, const T val )
   : size( n ),
     capacity( n ),
     ptr( new T[ n ] )
{
   if( n > 0 )
      for( unsigned int i = 0; i < n; i++ )
         ptr[ i ] = val;
}

// destructor
template< typename T >
Vector< T >::~Vector()
{
   delete [] ptr;
}

template< typename T >
Iterator< T > Vector< T >::begin()
{
   return Iterator< T >( ptr );
}

template< typename T >
Iterator< T > Vector< T >::end()
{
   return Iterator< T >( ptr + size );
}

template< typename T >
unsigned int Vector< T >::getSize() const
{
   return size;
}
template< typename T >
void Vector< T >::push_back( const T val )
{
   if( size == capacity )
   {
      capacity++;
      T *buf = new T[ capacity ];

      for( unsigned int i = 0; i < size; i++ )
         buf[ i ] = ptr[ i ];

      delete[] ptr;
      ptr = buf;
   }

   ptr[ size ] = val;
   size++;
}

/* Assignment 7 - implement */

template < typename T >
Vector< T >::Vector(const Vector< T > &vectorToCopy)
{
	// Constructs a container with a copy of each of the elements in x, in the same order.
	
	//copy size & capacity
	this->size = vectorToCopy.getSize();
	this->capacity = vectorToCopy.capacity;

	//allocate
	this->ptr = new T[this->capacity];

	//copy data
	for (iterator it = this->begin(), itR = vectorToCopy.begin();
		it < this->end();
		it++, itR++)
	{
		*it = *itr;
	}

	return *this;
}

template < typename T >
const Vector< T > &Vector< T >::operator=(const Vector< T > &right)
{
	// assignment operator
	//compare size, if this->size < vectorToCopy.size, resize this
	if (this->getSize() < vectorToCopy.getSize())
	{
		this->resize(vectorToCopy.getSize());
	}

	//copy data
	for (iterator it = this->begin(), itR = vectorToCopy.begin();
		it < this->end();
		it++, itR++)
	{
		*it = *itr;
	}

	return *this;
}

template < typename T >
bool Vector< T >::operator==(const Vector< T > &right) const
{
	// equality operator

	if (this->getSize() != right.getSize())
		return false;

	for (iterator it = this->begin(), itR = right.begin();
		it < this->end();
		it++, itR++)
	{
		if (*it != *itR)
			return false;
	}
	return true;
}

template < typename T >
bool Vector< T >::operator!=(const Vector< T > &right) const
{
	// inequality operator; returns opposite of == operator
	return !(*(this) == right);
}

template < typename T >
T &Vector< T >::operator[](unsigned int pos)
{
	// subscript operator for non-const objects returns modifiable lvalue
	return this->ptr[pos];
}


template < typename T >
T Vector< T >::operator[](unsigned int pos) const
{
	// subscript operator for const objects returns rvalue
	return this->ptr[pos];
}

template < typename T >
void Vector< T >::resize(unsigned int n)
{
	// Resizes the container so that it contains n elements.
	// If n is smaller than the current container size,
	// the content is reduced to its first n elements, removing those beyond.
	// If n is greater than the current container size,
	// the content is expanded by inserting at the end as many elements as needed to reach a size of n.
	// The new elements are initialized as 0.
	// If n is also greater than the current container capacity,
	// an automatic reallocation of the allocated storage space takes place.
	if (n > this->capacity)
	{
		this->reserve(n);
	}

	//init new element as 0
	iterator it = this->end();
	for (unsigned int i = 0; i < this->capacity - this->getSize(); i++)
	{
		*(it + i) = 0;
	}

	this->size = n;
}

template < typename T >
void Vector< T >::reserve(unsigned int n)
{
	// Requests that the vector capacity be enough to contain n elements.
	// If n is greater than the current vector capacity,   
	// the function causes the container to reallocate its storage increasing its capacity to n.   
	// In all other cases, the function call does not cause a reallocation and   
	// the vector capacity is not affected.

	if (n > this->capacity)
	{
		T* tempPtr = this->begin();
		this->capacity = n;
		this->ptr = new T[n];
		
		//copy data
		memcpy(this->ptr, tempPtr, this->size * sizeof(T));

		delete[]tempPtr;
	}
}