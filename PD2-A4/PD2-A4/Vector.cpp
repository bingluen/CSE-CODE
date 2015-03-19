// Member-function definitions for class Vector.
#include <iostream>
using namespace std;
#include "Vector.h" // include definition of class Vector 

// default constructor
Vector::Vector( unsigned int n, const int val )
{
   size = n;
   capacity = n;
   ptr = new int[ n ];

   if( n > 0 )
      for ( unsigned int i = 0; i < n; i++ )
         ptr[ i ] = val;
} // end Vector constructor

// destructor
Vector::~Vector()
{
   delete [] ptr;
} // end destructor

unsigned int Vector::getSize() const
{
   return size;
}

Vector::Vector(const Vector &vectorToCopy)
{
	// Constructs a vector with a copy of each of the elements in vectorToCopy, in the same order.

	//get capacity & size
	capacity = vectorToCopy.capacity;
	size = vectorToCopy.size;

	//allocate memory
	ptr = new int[capacity];
	
	//copy data form source vector
	memcpy(ptr, vectorToCopy.ptr, size);
	
}


const Vector &Vector::operator=(const Vector &right)
{
	// assignment operator

	/*
	In order to optimize the effectiveness of Vector object,
	minimize the number of memory re-allocate.
	Therefore, only when right capacity greate then the current capacity of this,
	will re-allocate memory for vector.
	*/

	if (capacity < right.capacity)
	{
		capacity = right.capacity;
		delete[] ptr;
		ptr = new int[capacity];
	}

	//copy data & reset size
	size = right.size;
	memcpy(ptr, right.ptr, size);

	return *this;
}

bool Vector::operator==(const Vector &right) const
{
	// equality operator
	
	//if size not equal -> left will not equal right
	if (size != right.size)
		return false;

	//if size are eaqual -> check each bit
	for (size_t i = 0; i < size; i++)
	{
		//if there is one bit is not equal -> left will not equal right
		if (ptr[i] != right.ptr[i])
			return false;
	}

	return true;
}


bool Vector::operator!=(const Vector &right) const
{
	// inequality operator; returns opposite of == operator
	return !(*this == right);
}


int &Vector::operator[](unsigned int subscript)
{
	// subscript operator for non-const objects returns modifiable lvalue
	if (subscript >= size || subscript < 0)
	{
		cerr << "index out of bound " << endl;
		return;
	}
		
	return ptr[subscript];
}


int Vector::operator[](unsigned int subscript) const
{
	// subscript operator for const objects returns rvalue
	if (subscript >= size || subscript < 0)
	{
		cerr << "index out of bound " << endl;
		return;
	}
	return ptr[subscript];
}

void Vector::resize(unsigned int n)
{
	// Resizes the vector so that it contains n elements.                                  
	// If n is smaller than the current vector size,                                  
	// the content is reduced to its first n elements, removing those beyond.                                  
	// If n is greater than the current vector size,                                  
	// the content is expanded by inserting at the end as many elements as needed to reach a size of n.                                  
	// The new elements are initialized as 0.                                  
	// If n is also greater than the current vector capacity,                                  
	// an automatic reallocation of the allocated storage space takes place.

	if (n > capacity)
		reserve(n);

	for (size_t i = size; i < n; i++)
		ptr[i] = 0;

	size = n;
}


void Vector::reserve(unsigned int n)
{
	// Requests that the vector capacity be enough to contain n elements.                                   
	// If n is greater than the current vector capacity,                                   
	// the function causes the vector to reallocate its storage increasing its capacity to n.                                   
	// If n is less than or equal to the current vector capacity,                                   
	// the function call does not cause a reallocation and the vector capacity is not affected.                                   
	// This function has no effect on the vector size and cannot alter its elements.

	// if n <= capacity do nothing
	if (n <= capacity)
		return;

	int *tempPtr = ptr;
	ptr = new int[n];
	memcpy(tempPtr, ptr, capacity);
	capacity = n;
	delete[]tempPtr;
}


void Vector::push_back(const int val)
{
	// Adds a new element at the end of the vector, after its current last element.                                    
	// The content of val is copied to the new element.                                    
	// This effectively increases the vector size by one,                                    
	// which causes an automatic reallocation of the allocated storage space                                    
	// if -and only if- the new vector size surpasses the current vector capacity.

	if (size + 1 > capacity)
		reserve(size + 1);

	ptr[size + 1] = val;
	size++;

}
