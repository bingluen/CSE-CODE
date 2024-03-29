// Member-function definitions for class HugeInteger.
#include <iostream>
using namespace std;
#include "HugeInteger.h" // include definition of class HugeInteger 
#include "ProductTable.h"

// default constructor
HugeInteger::HugeInteger()
   : integer()
{
} // end HugeInteger default constructor

// constructor
HugeInteger::HugeInteger( unsigned int size )
   : integer( size, 0 )
{
} // end HugeInteger constructor

// copy constructor
HugeInteger::HugeInteger( const HugeInteger &integerToCopy )
   : integer( integerToCopy.integer )
{
} // end HugeInteger copy constructor

// load a HugeInteger from a text file
void HugeInteger::load( ifstream &inFile )
{
   char digit;
   while( ( digit = inFile.get() ) != '\n' )
      integer.push_back( digit - '0' );

   unsigned int size = integer.getSize();
   int temp;
   for( unsigned int i = 0; i <= ( size - 1 ) / 2; i++ )
   {
      temp = integer[ i ];
      integer[ i ] = integer[ size - i - 1 ];
      integer[ size - i - 1 ] = temp;
   }
}

// overloaded assignment operator;
// const return avoids: ( a1 = a2 ) = a3
const HugeInteger &HugeInteger::operator=( const HugeInteger &right )
{
   integer = right.integer;
   return *this; // enables x = y = z, for example
} // end function operator=

// function that tests if two HugeIntegers are equal
bool HugeInteger::operator==( const HugeInteger &right ) const
{
   return ( integer == right.integer );
} // end function operator==

// function that tests if two HugeIntegers are not equal
bool HugeInteger::operator!=( const HugeInteger &right ) const
{
   return ( integer != right.integer ); 
} // end function operator!=

// addition operator; HugeInteger + HugeInteger
HugeInteger HugeInteger::operator+( const HugeInteger op2 ) const
{
   unsigned int size = integer.getSize();
   unsigned int op2Size = op2.integer.getSize();
   unsigned int sumSize = ( size >= op2Size ) ? size + 1 : op2Size + 1;

   HugeInteger sum( sumSize );

   for( unsigned int i = 0; i < size; i++ )
      sum.integer[ i ] = integer[ i ];

   for( unsigned int i = 0; i < op2Size; i++ )
      sum.integer[ i ] += op2.integer[ i ];

   for( unsigned int i = 0; i < sumSize - 1; i++ )
      if( sum.integer[ i ] > 9 ) 
      {
         sum.integer[ i ] -= 10;
         sum.integer[ i + 1 ]++;
      }

   if( sum.integer[ sumSize - 1 ] == 0 )
      sum.integer.resize( sumSize - 1 );

   return sum;
} // end function operator+

// subtraction operator; HugeInteger - HugeInteger
HugeInteger HugeInteger::operator-( const HugeInteger op2 ) const
{
   HugeInteger zero( 1 );

   // return if first value is smaller; we are not handling negatives
   if( *this < op2 )
   {
      cout << "Error: Tried to subtract larger value from smaller value.\n";
      return zero;
   }

   if( *this == op2 )
      return zero;

   HugeInteger difference(integer.getSize());

   for (size_t i = 0; i < op2.integer.getSize(); i++)
   {
	   difference.integer[i] = difference.integer[i] + integer[i] - op2.integer[i];
	   // if number < 0, borrow ten
	   while (difference.integer[i] < 0)
	   {
		   difference.integer[i + 1] -= 1;
		   difference.integer[i] += 10;
	   }
   }

   //將沒有被處理到的digit直接拉下來
   for (size_t i = op2.integer.getSize(); i < integer.getSize(); i++)
   {
	   difference.integer[i] = difference.integer[i] + integer[i];
   }

   //check size
   while (difference.integer.getSize() > 0 
	   && !difference.integer[difference.integer.getSize() - 1])
	   difference.integer.resize(difference.integer.getSize() - 1);


   return difference;
} // end function operator-

// multiplication operator; HugeInteger * HugeInteger
HugeInteger HugeInteger::operator*(const  HugeInteger op2) const
{

	HugeInteger zero(1);

	if (op2 == zero || *this == zero)
		return zero;

	HugeInteger product(integer.getSize() + op2.integer.getSize());

	for (size_t i = 0; i < integer.getSize(); i++)
	{
		for (size_t j = 0; j < op2.integer.getSize(); j++)
		{
			product.integer[i + j] = product.integer[i + j] + integer[i] * op2.integer[j];
		}
	}

	//carry
	for (size_t i = 0; i < product.integer.getSize(); i++)
	{
		if (product.integer[i] >= 10)
		{
			product.integer[i + 1] += product.integer[i] / 10;
			product.integer[i] %= 10;
		}
	}

	//check size
	while (product.integer.getSize() > 0
		&& !product.integer[product.integer.getSize() - 1])
		product.integer.resize(product.integer.getSize() - 1);

	return product;
}// end function operator*

// division operator; HugeInteger / HugeInteger
HugeInteger HugeInteger::operator/( const HugeInteger op2 ) const
{
   HugeInteger zero( 1 );
   if( *this < op2 )
      return zero;
   // if this equal to op2 return 1
   if (*this == op2)
   {
	   zero.helpIncrement();
	   return zero;
   }

   HugeInteger quotient(this->doDivision(op2, true));

   return quotient;
} // end function operator/

// modulus operator; HugeInteger % HugeInteger
HugeInteger HugeInteger::operator%( const HugeInteger op2 ) const
{
   if( *this < op2 )
      return *this;

   HugeInteger zero(1);
   // if this equal to op2 return 0
   if (*this == op2)
   {
	   return zero;
   }

   HugeInteger remainder(this->doDivision(op2, false));

   return remainder;
} // end function operator%

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
void HugeInteger::divideByTen()
{
   unsigned int size = integer.getSize();
   for( unsigned int i = 1; i < size; i++ )
      integer[ i - 1 ] = integer[ i ];
   integer.resize( size - 1 );
} // end function divideByTen

// function that tests if a HugeInteger is zero
bool HugeInteger::zero()
{
   for ( unsigned int i = 0; i < integer.getSize(); i++ )
      if ( integer[ i ] != 0 )
         return false;
         
   return true;
} // end function zero

// overloaded output operator for class Array 
ostream &operator<<( ostream &output, const HugeInteger &hugeInteger )
{
   unsigned int size = hugeInteger.integer.getSize();
   if( size == 0 )
      output << 0;
   else
	   for (int i = size - 1; i >= 0; i--)
		   output << hugeInteger.integer[i];
         

	  

   return output; // enables cout << x << y;
} // end function operator<<


bool HugeInteger::operator<(const HugeInteger &right) const  // less than
{
	
	if (this->integer == right.integer)
		return false;
	//check size
	else if (this->integer.getSize() < right.integer.getSize())
		return true;
	else if (this->integer.getSize() > right.integer.getSize())
		return false;

	//if size is equal, compare every bit
	for (size_t i = this->integer.getSize() - 1; i >= 0; i--)
	{
		if (this->integer[i] > right.integer[i])
			return false;
		if (this->integer[i] < right.integer[i])
			return true;
	}

	return true;
}

bool HugeInteger::operator>(const HugeInteger &right) const  // greater than
{
	if (this->integer == right.integer)
		return false;
	//check size
	else if (this->integer.getSize() > right.integer.getSize())
		return true;
	else if (this->integer.getSize() < right.integer.getSize())
		return false;

	//if size is equal, compare every bit
	for (size_t i = this->integer.getSize() - 1; i >= 0; i--)
	{
		if (this->integer[i] > right.integer[i])
			return true;
		if (this->integer[i] < right.integer[i])
			return false;
	}		
}

bool HugeInteger::operator<=(const HugeInteger &right) const // less than or equal to
{
	return !(*this > right);
}

bool HugeInteger::operator>=(const HugeInteger &right) const // greater than or equal to
{
	return !(*this < right);
}

// prefix increment operator
HugeInteger& HugeInteger::operator++()
{
	this->helpIncrement();
	return *this;
}

// postfix increment operator
HugeInteger HugeInteger::operator++(int)
{
	HugeInteger temp(*this);
	this->helpIncrement();

	return *(new HugeInteger(temp));
}

void HugeInteger::helpIncrement()
{
	// increments a HugeInteger by 1
	
	//first increment Lower digit
	this->integer[0]++;

	//check carry
	for (size_t i = 0; i < this->integer.getSize() - 1; i++)
	{
		if (this->integer[i] > 9)
		{
			this->integer[i + 1] += this->integer[i] / 10;
			this->integer[i] %= 10;
		}
	}

	//check highest bit is small than 10
	if (this->integer[this->integer.getSize() - 1] > 9)
	{
		this->integer.resize(this->integer.getSize() + 1);
		this->integer[this->integer.getSize() - 1] = this->integer[this->integer.getSize() - 2] / 10;
		this->integer[this->integer.getSize() - 2] %= 10;
	}
}

HugeInteger& HugeInteger::doDivision(const HugeInteger &right, bool getQuotient) const
{
	HugeInteger quotient(1), remainder(1);
	ProductTable table(right);

	//Form highest digit start
	for (int i = this->integer.getSize() - 1; i >= 0; i--)
	{
		//Left shift bit before put next bit
		//the first time or remainder is zero did not need
		if (i < this->integer.getSize() - 1 && !remainder.zero())
		{
			remainder.shiftDigitLeft();
		}
		

		//get Next bit
		remainder.integer[0] = this->integer[i];


		//offset quotient
		if (!quotient.zero())
			quotient.shiftDigitLeft();

		//compare remainder and right
		quotient.integer[0] = table.getScalarForDivison(remainder);
		remainder = remainder - table.getProduct(quotient.integer[0]);
	}

	if (getQuotient)
		return *(new HugeInteger(quotient));
	else
		return *(new HugeInteger(remainder));
}

void HugeInteger::shiftDigitLeft()
{
	//first, resize
	this->integer.resize(this->integer.getSize() + 1);
	
	//second, shift
	for (short i = this->integer.getSize() - 2; i >= 0; i--)
	{
		this->integer[i + 1] = this->integer[i];
	}
}