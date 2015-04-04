// Vector class definition.
#ifndef VECTOR_H
#define VECTOR_H

template< typename T >
class Vector
{
public:
   Vector( unsigned int n = 0, const T val = 0 );
   // Constructs a container with n elements. Each element is a copy of val.

   Vector( T *first, T *last );
   // Constructs a vector with as many elements as the range [first,last),
   // with each element emplace-constructed from its corresponding element in that range,
   // in the same order.

   Vector( const Vector< T > &vectorToCopy );
   // Constructs a vector with a copy of each of the elements in vectorToCopy, in the same order.

   ~Vector(); // Destroys the vector object.

   const Vector< T > &operator=( const Vector< T > &right ); // assignment operator

   bool operator==( const Vector< T > &right ) const; // equality operator

   bool operator!=( const Vector< T > &right ) const;
   // inequality operator; returns opposite of == operator
   
   T &operator[]( unsigned int );
   // subscript operator for non-const objects returns modifiable lvalue

   // subscript operator for const objects returns rvalue
   T operator[]( unsigned int ) const;

   T* begin() const; // Returns a pointer pointing to the first element in the vector.
                 // If the container is empty, the returned pointer shall not be dereferenced.
   T* end() const; // Returns an pointer referring to the past-the-end element in the vector container.
               // The past-the-end element is the theoretical element that would follow the last element in the vector.
               // It does not point to any element, and thus shall not be dereferenced.
               // If the container is empty, the returned pointer shall not be dereferenced. 

   unsigned int getSize() const; // Returns the number of elements in the vector.

   void resize( unsigned int n );
   // Resizes the container so that it contains n elements.
   // If n is smaller than the current container size,
   // the content is reduced to its first n elements, removing those beyond.
   // If n is greater than the current container size,
   // the content is expanded by inserting at the end as many elements as needed to reach a size of n.
   // The new elements are initialized as 0.
   // If n is also greater than the current container capacity,
   // an automatic reallocation of the allocated storage space takes place.

   void reserve( unsigned int n );
   // Requests that the vector capacity be enough to contain n elements.
   // If n is greater than the current vector capacity,   
   // the function causes the container to reallocate its storage increasing its capacity to n.   
   // In all other cases, the function call does not cause a reallocation and   
   // the vector capacity is not affected.

   void assign( T *first, T *last );
   // Assigns new contents to the vector, replacing its current contents,   
   // and modifying its size accordingly.   
   // The new contents are elements constructed from each of the elements   
   // in the range between first and last, in the same order.

   void push_back( const T val );
   // Adds a new element at the end of the vector, after its current last element.                                    
   // The content of val is copied to the new element.                                    
   // This effectively increases the vector size by one,                                    
   // which causes an automatic reallocation of the allocated storage space                                    
   // if -and only if- the new vector size surpasses the current vector capacity.

   T* insert( T *position, const T val );
   // The vector is extended by inserting a new element before the element at the specified position,   
   // effectively increasing the container size by one.   
   // This causes an automatic reallocation of the allocated storage space if -and only if-   
   // the new vector size surpasses the current vector capacity.   
   // Relocates all the elements that were after position to their new positions.

   T* erase( T *position );
   // Removes from the vector a single element.   
   // This effectively reduces the container size by one.   
   // Relocates all the elements after the element erased to their new positions.

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

#endif