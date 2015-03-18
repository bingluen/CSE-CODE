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