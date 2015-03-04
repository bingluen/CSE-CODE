// Member-function definitions for class Vector.
#include <iostream>
#include <iomanip>
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

int* Vector::begin()
{
   return ptr;
}

int* Vector::end()
{
   return ptr + size;
}

unsigned int Vector::getSize() const
{
   return size;
}

unsigned int Vector::getCapacity() const
{
   return capacity;
}

bool Vector::empty() const
{
   return ( size == 0 );
}

int& Vector::front()
{
   return ptr[0];
}

int& Vector::back()
{
   return ptr[ size - 1 ];
}

void Vector::pop_back()
{
   size--;
}

void Vector::clear()
{
   size = 0;
}

void Vector::display()
{
   for( unsigned int i = 0; i < size; i++ )
      cout << setw(3) << ptr[ i ];
   cout << endl << endl;
}

Vector::Vector(int *first, int *last)
{
	size = (last - first);
	capacity = size;
	ptr = new int[size];
	for (unsigned int i = 0; ptr+i < end();i++)
	{
		*(ptr + i) = *(first + i);
	}
}

Vector::Vector(const Vector &vectorToCopy)
{
	size = vectorToCopy.size;
	capacity = vectorToCopy.capacity;
	ptr = new int[capacity];
	int* mPtr = vectorToCopy.ptr;
	for (unsigned int i = 0; i < size; i++)
	{
		*(ptr + i) = *(mPtr + i);
	}
}

void Vector::resize(unsigned int n)
{
	if (n > capacity)
	{
		reserve(n);
	}

	for (unsigned int i = size; i < n; i++)
	{
		*(ptr + i) = 0;
	}

	size = n;
}

void Vector::reserve(unsigned int n)
{
	if (n > capacity)
	{
		int *tempPtr = ptr;

		ptr = new int[(n%10 == 0)? n:((n / 10 + 1) * 10)];

		size = 0;
		for (unsigned int i = 0; i < capacity; i++)
		{
			ptr[i] = tempPtr[i];
			size++;
		}

		delete [] tempPtr;

		capacity = (n % 10 == 0) ? n : ((n / 10 + 1) * 10);
	}
}



void Vector::assign(int *first, int *last)
{
	for (int *mPtr = ptr; mPtr < end(); mPtr++)
	{
		if (mPtr < first || mPtr >= last)
		{
			delete mPtr;
			size--;
			capacity--;
		}

		ptr = first;
	}
}

void Vector::push_back(const int val)
{
	if (size + 1 > capacity)
	{
		resize(size + 1);
	}
	else 
	{
		size++;
	}

	*(ptr + size - 1) = val;
}

int* Vector::insert(int *position, const int val)
{
	unsigned int pos = position - begin();

	if (size + 1 > capacity)
	{
		resize(size + 1);
	}
	else 
	{
		size++;
	}

	for (unsigned int i = size - 1; i > pos; i--)
	{
		ptr[i] = ptr[i - 1];
	}

	ptr[pos] = val;

	return &(ptr[pos]);
}

int* Vector::erase(int *position)
{
	for (int* mPtr = position; mPtr < end(); mPtr++)
	{
		*mPtr = *(mPtr + 1);
	}
	size--;
	return position;
}

void Vector::swap(Vector &x)
{
	int* tempPtr;
	unsigned int tempCapacity;
	unsigned int tempSize;

	tempPtr = x.ptr;
	tempCapacity = x.capacity;
	tempSize = x.size;

	x.ptr = ptr;
	x.capacity = capacity;
	x.size = size;

	ptr = tempPtr;
	capacity = tempCapacity;
	size = tempSize;
}