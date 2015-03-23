// Vector class definition.
#ifndef VECTOR_H
#define VECTOR_H

class Vector
{
public:
   Vector( unsigned int n = 0, const int val = 0 );
   // Constructs a vector with n elements. Each element is a copy of val.

   Vector( const Vector &vectorToCopy );
   // Constructs a vector with a copy of each of the elements in vectorToCopy, in the same order.

   ~Vector(); // Destroys the vector object.

   const Vector &operator=( const Vector &right ); // assignment operator

   bool operator==( const Vector &right ) const; // equality operator

   // inequality operator; returns opposite of == operator
   bool operator!=( const Vector &right ) const;
   
   // subscript operator for non-const objects returns modifiable lvalue
   int &operator[]( unsigned int subscript );

   // subscript operator for const objects returns rvalue
   int operator[]( unsigned int subscript ) const;

   unsigned int getSize() const; // Returns the number of elements in the vector.

   void resize( unsigned int n );
   // Resizes the vector so that it contains n elements.                                  
   // If n is smaller than the current vector size,                                  
   // the content is reduced to its first n elements, removing those beyond.                                  
   // If n is greater than the current vector size,                                  
   // the content is expanded by inserting at the end as many elements as needed to reach a size of n.                                  
   // The new elements are initialized as 0.                                  
   // If n is also greater than the current vector capacity,                                  
   // an automatic reallocation of the allocated storage space takes place.

   void reserve( unsigned int n );
   // Requests that the vector capacity be enough to contain n elements.                                   
   // If n is greater than the current vector capacity,                                   
   // the function causes the vector to reallocate its storage increasing its capacity to n.                                   
   // If n is less than or equal to the current vector capacity,                                   
   // the function call does not cause a reallocation and the vector capacity is not affected.                                   
   // This function has no effect on the vector size and cannot alter its elements.

   void push_back( const int val );
   // Adds a new element at the end of the vector, after its current last element.                                    
   // The content of val is copied to the new element.                                    
   // This effectively increases the vector size by one,                                    
   // which causes an automatic reallocation of the allocated storage space                                    
   // if -and only if- the new vector size surpasses the current vector capacity.

private:
   unsigned int size; // the number of elements in the vector
                      // This is the number of actual objects held in the vector,
                      // which is not necessarily equal to its storage capacity.

   unsigned int capacity;
   // the size of the storage space currently allocated for the vector,
   // expressed in terms of elements.                          
   // This capacity is not necessarily equal to the vector size.
   // It can be equal or greater, with the extra space allowing to accommodate
   // for growth without the need to reallocate on each insertion.

   int *ptr;
   // points to a dynamically allocated array which is used to store the elements of the vector
}; // end class Vector

#endif