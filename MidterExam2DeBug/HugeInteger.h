// HugeInteger class template definition
#ifndef HUGEINTEGER_H
#define HUGEINTEGER_H

#include <fstream>
using namespace std;
#include "Vector.h" // include definition of class template Vector 

template< typename T >
class HugeInteger : public Vector< T >
{
   template< typename U >
   friend ostream &operator<<( ostream &, HugeInteger< U > & );
public:
   HugeInteger( unsigned int size = 0 ); // default constructor
   HugeInteger( HugeInteger &integerToCopy ); // copy constructor
   ~HugeInteger(); // destructor

   void load( ifstream &inFile ); // load a HugeInteger from a text file
   const HugeInteger &operator=( const HugeInteger &right ); // assignment operator
   bool operator<( HugeInteger & ); // less than
   HugeInteger square(); // the square of HugeInteger
   HugeInteger squareRoot(); // the square root of HugeInteger
   HugeInteger operator++( int ); // postfix increment operator

private:
	bool isZero();
}; // end class HugeInteger

#endif