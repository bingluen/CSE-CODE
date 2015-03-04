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
	//count size
	size = (last - first);
	capacity = size;

	//allocate new memory
	ptr = new int[size];
	for (unsigned int i = 0; ptr+i < end();i++)
	{
		//copy element
		*(ptr + i) = *(first + i);
	}
}

Vector::Vector(const Vector &vectorToCopy)
{
	//copy size & capacity 
	size = vectorToCopy.size;
	capacity = vectorToCopy.capacity;
	//allocate new memoery
	ptr = new int[capacity];

	//get ptr of copy source
	int* mPtr = vectorToCopy.ptr;

	//copy data
	for (unsigned int i = 0; i < size; i++)
	{
		*(ptr + i) = *(mPtr + i);
	}
}

void Vector::resize(unsigned int n)
{
	//check size, if n bigger than capacity reserver vector
	if (n > capacity)
	{
		reserve(n);
	}

	//initialize new element
	for (unsigned int i = size; i < n; i++)
	{
		*(ptr + i) = 0;
	}

	//adjust size
	size = n;
}

void Vector::reserve(unsigned int n)
{
	//check capacity
	if (n > capacity)
	{
		//if capacity is smaller than n, re-allocate memory

		//save original ptr
		int *tempPtr = ptr;

		//allocate new memory (base in 10)
		ptr = new int[(n%10 == 0)? n:((n / 10 + 1) * 10)];

		//init size
		size = 0;
		for (unsigned int i = 0; i < capacity; i++)
		{
			//transfer data to memory which be allocate
			ptr[i] = tempPtr[i];
			size++;
		}

		//release origrinal memory
		delete [] tempPtr;

		//adjust capacity base in 10
		capacity = (n % 10 == 0) ? n : ((n / 10 + 1) * 10);
	}
}



void Vector::assign(int *first, int *last)
{
	for (int *mPtr = ptr; mPtr < end(); mPtr++)
	{
		//delete memory if isn't in range
		if (mPtr < first || mPtr >= last)
		{
			delete mPtr;
			size--;
			capacity--;
		}

		// asjust ptr to point first position
		ptr = first;
	}
}

void Vector::push_back(const int val)
{
	//check capcity & adjust size and capacity
	if (size + 1 > capacity)
	{
		resize(size + 1);
	}
	else 
	{
		size++;
	}

	//insert data to back
	*(ptr + size - 1) = val;
}

int* Vector::insert(int *position, const int val)
{
	unsigned int pos = position - begin();

	//check capcity & adjust size and capacity
	if (size + 1 > capacity)
	{
		resize(size + 1);
	}
	else 
	{
		size++;
	}

	//move data to make room for insert data
	for (unsigned int i = size - 1; i > pos; i--)
	{
		ptr[i] = ptr[i - 1];
	}

	//insert data
	ptr[pos] = val;

	//return point of insert data
	return &(ptr[pos]);
}

int* Vector::erase(int *position)
{
	//move next data to current position from input position (Overwrite data which want to earse)
	for (int* mPtr = position; mPtr < end(); mPtr++)
	{
		*mPtr = *(mPtr + 1);
	}
	size--;
	return position;
}

void Vector::swap(Vector &x)
{
	//To echange size, cpapcity and ptr

	int* tempPtr;
	unsigned int tempCapacity;
	unsigned int tempSize;
	
	//save data of x
	tempPtr = x.ptr;
	tempCapacity = x.capacity;
	tempSize = x.size;

	//assignment data of this to x
	x.ptr = ptr;
	x.capacity = capacity;
	x.size = size;

	//assignment data of x to this
	ptr = tempPtr;
	capacity = tempCapacity;
	size = tempSize;
}