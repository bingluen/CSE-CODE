// HugeInteger class definition.
#ifndef HUGEINTEGER_H
#define HUGEINTEGER_H

#include <fstream>
using namespace std;

#include "Vector.h" // include definition of class Vector 

template< typename T >
class HugeInteger : public Vector< T >
{
//   friend istream &operator>>( istream &, HugeInteger & );
   template< typename U >
   friend ostream &operator<<( ostream &, HugeInteger< U > & );

   template < typename V >
   friend class ProductTable;
public:
   HugeInteger(); // default constructor
   HugeInteger( T *first, T *last ); // constructor
   HugeInteger( HugeInteger &integerToCopy ); // copy constructor
   ~HugeInteger(); // destructor

   void load( ifstream &inFile ); // load a HugeInteger from a text file
   const HugeInteger &operator=( const HugeInteger &right ); // assignment operator
   bool operator<( const HugeInteger &); // less than
   bool operator>( const HugeInteger &); // greater than
   bool operator<=( const HugeInteger &); // less than or equal
   bool operator>=(const HugeInteger &); // greater than or equal to

   HugeInteger operator+( HugeInteger &op2 ); // addition operator; HugeInteger + HugeInteger
   HugeInteger operator-( HugeInteger &op2 ); // subtraction operator; HugeInteger - HugeInteger
   HugeInteger operator*( HugeInteger &op2 ); // multiplication operator; HugeInteger * HugeInteger
   HugeInteger operator/( HugeInteger &op2 ); // division operator; HugeInteger / HugeInteger
   HugeInteger operator%( HugeInteger &op2 ); // modulus operator; HugeInteger % HugeInteger
   HugeInteger &operator++(); // prefix increment operator
   HugeInteger operator++( int ); // postfix increment operator
   bool zero();                      // tests if a HugeInteger is zero
private:
   HugeInteger( unsigned int size ); // constructor
   void divideByTen();               // divides a HugeInteger by 10
   void helpIncrement();             // increments a HugeInteger by 1

   void shiftDigitLeft();
   HugeInteger doDivision(HugeInteger &op2, bool getQuotient);
}; // end class HugeInteger

#endif