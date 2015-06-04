// Vector class definition and member-function definitions for class Vector
#ifndef VECTOR_H
#define VECTOR_H

#include "Iterator.h" // include definition of class Iterator

template< typename T >
class Vector
{
public:
   typedef Iterator< T > iterator;

   Vector( unsigned int n = 0, const T val = T() );
   // Constructs a container with n elements. Each element is a copy of val.

   Vector( const Vector &vectorToCopy );
   // Constructs a container with a copy of each of the elements in x, in the same order.

   ~Vector(); // Destroys the container object.

   const Vector &operator=( const Vector &right ); // assignment operator
   
   T &operator[]( unsigned int );
   // subscript operator for non-const objects returns modifiable lvalue

   // subscript operator for const objects returns rvalue
   T operator[]( unsigned int ) const;

   iterator begin(); // Returns a pointer pointing to the first element in the vector.
                 // If the container is empty, the returned pointer shall not be dereferenced.
   iterator end(); // Returns an pointer referring to the past-the-end element in the vector container.
               // The past-the-end element is the theoretical element that would follow the last element in the vector.
               // It does not point to any element, and thus shall not be dereferenced.
               // If the container is empty, the returned pointer shall not be dereferenced. 

   unsigned int getSize() const; // Returns the number of elements in the vector.

   void push_back( const T val );
   // Adds a new element at the end of the vector, after its current last element.                                    
   // The content of val is copied to the new element.                                    
   // This effectively increases the vector size by one,                                    
   // which causes an automatic reallocation of the allocated storage space                                    
   // if -and only if- the new vector size surpasses the current vector capacity.

private:
   unsigned int size;
   // the number of elements in the vector
   // This is the number of actual objects held in the vector,
   // which is not necessarily equal to its storage capacity.

   unsigned int capacity;
   // the size of the storage space currently allocated for the vector,
   // expressed in terms of elements.   
   // This capacity is not necessarily equal to the vector size. It can be equal or greater,   
   // with the extra space allowing to accommodate for growth
   // without the need to reallocate on each insertion.

   T *ptr;
   // points to a dynamically allocated array which is used to store the elements of the vector
}; // end class Vector

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

// copy constructor
template< typename T >
Vector< T >::Vector( const Vector< T > &vectorToCopy )
   : size( vectorToCopy.size ),
   capacity( vectorToCopy.capacity ),
   ptr( new T[ capacity ] )
{
   for( unsigned int i = 0; i < size; i++ )
      ptr[ i ] = vectorToCopy.ptr[ i ];
}

// destructor
template< typename T >
Vector< T >::~Vector()
{
   delete[] ptr;
}

// overloaded assignment operator;
// const return avoids: ( a1 = a2 ) = a3
template< typename T >
const Vector< T > &Vector< T >::operator=( const Vector< T > &right )
{
   if( &right != this ) // avoid self-assignment
   {
      // for Arrays of different sizes, deallocate original
      // left-side array, then allocate new left-side array
      if( size != right.size )
      {
         if( size > 0 )
            delete[] ptr; // release space
         size = right.size; // resize this object
         capacity = right.capacity;
         ptr = new T[ size ]; // create space for array copy
      } // end inner if

      for( unsigned int i = 0; i < size; i++ )
         ptr[ i ] = right.ptr[ i ]; // copy array into object
   } // end outer if

   return *this; // enables x = y = z, for example
} // end function operator=

// overloaded subscript operator for non-const Arrays;
// reference return creates a modifiable lvalue
template< typename T >
T &Vector< T >::operator[]( unsigned int subscript )
{
   // check for subscript out-of-range error
   if( subscript < 0 || subscript >= size )
   {
      cerr << "\nError: Subscript " << subscript << " out of range" << endl;
      exit( 1 ); // terminate program; subscript out of range
   } // end if

   return ptr[ subscript ]; // reference return
}

// overloaded subscript operator for const Arrays
// const reference return creates an rvalue
template< typename T >
T Vector< T >::operator[]( unsigned int subscript ) const
{
   // check for subscript out-of-range error
   if( subscript < 0 || subscript >= size )
   {
      cerr << "\nError: Subscript " << subscript << " out of range" << endl;
      system( "pause" );
      exit( 1 ); // terminate program; subscript out of range
   } // end if

   return ptr[ subscript ]; // returns copy of this element
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

#endif