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