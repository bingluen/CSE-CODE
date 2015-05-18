// Iterator class template definition
#ifndef ITERATOR_H
#define ITERATOR_H

template< typename T >
class Iterator 
{
public:
   Iterator( T *p = 0 ); // default constructor
   Iterator( const Iterator &iteratorToCopy ); // copy constructor
   T& operator*() const; // dereference an iterator
   const Iterator &operator=( const Iterator &right ); // assignment operator
   Iterator operator++( int ); // postincrement an iterator
   Iterator operator--( int ); // postdecrement an iterator
   Iterator operator+( int i ); // increment an iterator by i positions
   Iterator operator-( int i ); // decrement an iterator by i positions
   int operator-(Iterator it);
   bool operator<( const Iterator &right ) const; // compare iterators for less
   bool operator>=( const Iterator &right ) const; // compare iterators for greater or equal
   bool operator>( const Iterator &right ) const; // compare iterators for greater
private:
   T *ptr; // keep a pointer to vector
}; // end class Iterator

#endif