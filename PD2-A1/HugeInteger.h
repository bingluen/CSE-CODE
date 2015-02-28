// HugeInteger class definition.
#ifndef HUGEINTEGER_H
#define HUGEINTEGER_H
#include <fstream>
using namespace std;

class HugeInteger
{
public:
   HugeInteger(); // default constructor

   void load( ifstream &inFile ); // load a HugeInteger from a text file
   bool zero(); // is zero

   bool equal( HugeInteger ); // equal to
   bool notEqual( HugeInteger ); // not equal to
   bool less( HugeInteger ); // less than
   bool greater( HugeInteger ); // greater than
   bool lessEqual( HugeInteger ); // less than or equal
   bool greaterEqual( HugeInteger ); // greater than or equal to

   HugeInteger add( HugeInteger op2 ); // addition operator; HugeInteger + HugeInteger
   HugeInteger subtract( HugeInteger op2 ); // subtraction operator; HugeInteger - HugeInteger;
                                            // return 0 if first value is smaller
   HugeInteger multiply( HugeInteger op2 ); // multiplication operator; HugeInteger * HugeInteger
   HugeInteger divide( HugeInteger op2 ); // division operator; HugeInteger / HugeInteger
   HugeInteger modulus( HugeInteger op2 ); // modulus operator; HugeInteger % HugeInteger

   HugeInteger divideOrModulus(HugeInteger op2, bool getDivide);
   void output();

   void setSize(int);
   void setDigit(int, int);

private:
   int size;              // the number of digits of the integer
   short integer[ 1000 ]; // used to store a positive integer as large as 1000 digits

   HugeInteger( int ); // constructor
   void divideByTen();
}; // end class HugeInteger


class ProductTable
{
public:
	ProductTable(HugeInteger);
	short getScalarForDivision(HugeInteger);
	HugeInteger getProduct(short);
private:
	HugeInteger table[10];
};

#endif