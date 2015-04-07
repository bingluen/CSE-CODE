// Member-function definitions for class Vector.
#include "Vector.h" // include definition of class Vector 

// constructor
template< typename T >
Vector< T >::Vector( unsigned int n, const T val )
{
   size = n;
   capacity = n;
   ptr = new T[ n ];

   if( n > 0 )
      for ( unsigned int i = 0; i < n; i++ )
         ptr[ i ] = val;
} // end Vector constructor

// destructor
template< typename T >
Vector< T >::~Vector()
{
   delete [] ptr;
} // end destructor

template< typename T >
T* Vector< T >::begin() const
{
   return ptr;
}

template< typename T >
T* Vector< T >::end() const
{
   return ptr + size;
}

template< typename T >
unsigned int Vector< T >::getSize() const
{
   return size;
}



/* Assignment 6 - implement */
template< typename T >
Vector< T >::Vector(const Vector< T > &vectorToCopy)
{
	// Constructs a vector with a copy of each of the elements in vectorToCopy, in the same order.
	
	//copy size & capacity
	this->size = vectorToCopy.size;
	this->capacity = vectorToCopy.capacity;

	//allocate memory
	this->ptr = new T[this->capacity];

	//copy data
	memcpy(this->ptr, vectorToCopy.ptr, this->size * sizeof(T));
}


template< typename T >
const Vector< T > &Vector< T >::operator=(const Vector< T > &right)
{
	// assignment operator
	
	//check capacity
	if (right.size > this->capacity)
	{
		//if right.size > this->Capacity, call reserve to reallocate memory
		this->reserve(right.size);
	}

	//set size
	this->size = right.size;
	
	//copy data
	memcpy(this->ptr, right.ptr, this->size * sizeof(T));

	return *this;
}


template< typename T >
bool Vector< T >::operator==(const Vector< T > &right) const
{
	// equality operator
	//check size
	if (this->size != right.size)
		return false;

	//compare every digit
	for (T *p = this->begin(), *rP = right.begin()
		; p < this->end()
		; p++, rP++)
	{
		if (*p != *rP)
			return false;
	}

	return true;
}

template< typename T >
bool Vector< T >::operator!=(const Vector< T > &right) const
{
	// inequality operator; returns opposite of == operator

	return !(*(this) == right);
}


template< typename T >
T &Vector< T >::operator[](unsigned int pos)
{
	// subscript operator for non-const objects returns modifiable lvalue
	return ptr[pos];
}


template< typename T >
T Vector< T >::operator[](unsigned int pos) const
{
	// subscript operator for const objects returns rvalue
	return ptr[pos];
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

	//check capacity, if n > capacity call reserve to reallocate memory
	if (n > this->capacity)
	{
		this->reserve(n);
	}
	
	//init new element as 0
	memset(this->end(), 0, this->capacity - this->getSize());

	this->size = n;

}

template< typename T >
void Vector< T >::reserve(unsigned int n)
{
	// Requests that the vector capacity be enough to contain n elements.
	// If n is greater than the current vector capacity,   
	// the function causes the container to reallocate its storage increasing its capacity to n.   
	// In all other cases, the function call does not cause a reallocation and   
	// the vector capacity is not affected.

	if (n > this->capacity)
	{
		T* tempPtr = ptr;
		this->capacity = n;
		this->ptr = new T[this->capacity];

		//copy data
		memcpy(this->ptr, tempPtr, this->size * sizeof(T));

		delete[]tempPtr;
	}
}


template< typename T >
void Vector< T >::assign(T *first, T *last)
{
	// Assigns new contens to the vector, replacing its current contents,   
	// and modifying its size accordingly.   
	// The new contents are elements constructed from each of the elements   
	// in the range between first and last, in the same order.

	unsigned int length = last - first;

	//if length > this->capacity, reallocate memory
	if (length > this->capacity)
	{
		this->reserve(length);
	}

	//copy data
	memcpy(this->ptr, first, length * sizeof(T));

	//reset size
	this->size = length;
	
}


template< typename T >
void Vector< T >::push_back(const T val)
{
	// Adds a new element at the end of the vector, after its current last element.                                    
	// The content of val is copied to the new element.                                    
	// This effectively increases the vector size by one,                                    
	// which causes an automatic reallocation of the allocated storage space                                    
	// if -and only if- the new vector size surpasses the current vector capacity.

	//if cpapcity is not enought to add new element, reallocate memory
	if (this->size + 1 > this->capacity)
	{
		this->reserve(this->size + 1);
	}

	//push data
	*(this->end()) = val;

	//increment size
	this->size++;
}

template< typename T >
T* Vector< T >::insert(T *position, const T val)
{
	// The vector is extended by inserting a new element before the element at the specified position,   
	// effectively increasing the container size by one.   
	// This causes an automatic reallocation of the allocated storage space if -and only if-   
	// the new vector size surpasses the current vector capacity.   
	// Relocates all the elements that were after position to their new positions.

	//if cpapcity is not enought to add new element, reallocate memory
	if (this->size + 1 > this->capacity)
	{
		this->reserve(this->size + 1);
	}

	//To vacated position, do move data
	memmove(position + 1, position, this->end() - position);

	//insert data
	*position = val;

	//increment size
	this->size++;
}

template< typename T >
T* Vector< T >::erase(T *position)
{
	// Removes from the vector a single element.   
	// This effectively reduces the container size by one.   
	// Relocates all the elements after the element erased to their new positions.

	//move data to overwrite value which want to earse.
	memmove(position, position + 1, (this->end() - 1) - position);

	//decrease size
	this->size--;

}
