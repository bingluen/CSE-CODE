// HugeInteger class definition.
#ifndef HUGEINTEGER_H
#define HUGEINTEGER_H

#include <fstream>
#include "Vector.h" // include definition of class Vector 
#include "ProductTable.h"

using namespace std; //for ofstream and ifstream

class HugeInteger 
{
   friend ostream &operator<<( ostream &, const HugeInteger & );

   //let Product table can access private constructor and helpIncrements
   friend class ProductTable;
public:
   HugeInteger(); // default constructor
   HugeInteger( const HugeInteger &integerToCopy ); // copy constructor

   void load( ifstream &inFile ); // load a HugeInteger from a text file
   const HugeInteger &operator=( const HugeInteger &right ); // assignment operator

   bool operator==( const HugeInteger &right ) const; // equal to
   bool operator!=( const HugeInteger &right ) const; // not equal to
   bool operator<( const HugeInteger &right ) const;  // less than
   bool operator>( const HugeInteger &right ) const;  // greater than
   bool operator<=( const HugeInteger &right ) const; // less than or equal to
   bool operator>=( const HugeInteger &right ) const; // greater than or equal to

   // addition operator; HugeInteger + HugeInteger
   HugeInteger operator+( const HugeInteger op2 ) const;

   // subtraction operator; HugeInteger - HugeInteger; return 0 if first value is smaller
   HugeInteger operator-( const HugeInteger op2 ) const;

   // multiplication operator; HugeInteger * HugeInteger
   HugeInteger operator*( const  HugeInteger op2 ) const;

   // division operator; HugeInteger / HugeInteger
   HugeInteger operator/( const HugeInteger op2 ) const;

   // modulus operator; HugeInteger % HugeInteger
   HugeInteger operator%( const HugeInteger op2 ) const;

   // prefix increment operator
   HugeInteger &operator++();

   // postfix increment operator
   HugeInteger operator++( int );

   bool zero();                      // tests if a HugeInteger is zero
private:
   Vector integer;                   // stores a huge integer

   HugeInteger( unsigned int size ); // constructor
   void divideByTen();               // divides a HugeInteger by 10
   void helpIncrement();             // increments a HugeInteger by 1
}; // end class HugeInteger

#endif