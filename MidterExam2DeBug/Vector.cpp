// Member-function definitions for class template Vector
#include "Vector.h" // include definition of class template Vector 

// default constructor
template< typename T >
Vector< T >::Vector( unsigned int n )
   : size( n ),
     capacity( n ),
     ptr( new T[ n ] )
{
   if( n > 0 )
      for( unsigned int i = 0; i < n; i++ )
         ptr[ i ] = 0;
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


/* midter exam 2 implement */
template< typename T >
Vector< T >::Vector(const Vector< T > &vectorToCopy)
{
	// Constructs a container with a copy of each of the elements in x, in the same order.
	this->size = vectorToCopy.size;
	this->capacity = vectorToCopy.capacity;
	this->ptr = new T[this->capacity];

	/* copy data */
	memcpy(this->ptr, vectorToCopy.ptr, this->size*sizeof(T));

}


template< typename T >
const Vector< T > &Vector< T >::operator=(const Vector< T > &right)
{
	// assignment operator

	delete[] this->ptr;
	
	this->size = vectorToCopy.size;
	this->capacity = vectorToCopy.capacity;
	this->ptr = new T[this->capacity];

	/* copy data */
	memcpy(this->ptr, vectorToCopy.ptr, this->size*sizoef(T));
}


template< typename T >
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

	if (this->capacity < n)
	{
		/* backup address */
		Vector<T>::iterator temp = this->begin(), endTemp = this->end();

		/* reallocate memoery */
		this->ptr = new T[n + 10];

		/* copy data*/
		/* memcpy(this->ptr, temp, sizeof(T)*this->size); */
		for (Vector<T>::iterator it = this->begin(), tempIt = temp;
			tempIt < endTemp;
			it++, tempIt++)
		{
			*it = *tempIt;
		}

		this->capacity = n + 10;
	}

	/* set new element to zero */
	/*
	for (size_t i = this->size; i < n; i++)
		this->ptr[i] = 0;
	*/
	for (Vector<T>::iterator it = this->end(); it < this->end() + (n - this->size); it++)
		*it = 0;

	/* set size and cpacity */
	this->size = n;
}

template< typename T >
void Vector< T >::push_back(const T val)
{
	// Adds a new element at the end of the vector, after its current last element.
	// The content of val is copied to the new element.
	// This effectively increases the vector size by one,
	// which causes an automatic reallocation of the allocated storage space
	// if -and only if- the new vector size surpasses the current vector capacity.

	if (this->getSize() + 1 > this->capacity)
	{
		this->resize(getSize() + 1);
	}
	else
	{
		this->size++;
	}

	this->ptr[this->size - 1] = val;
}
