// Member-function definitions for class HugeInteger.
#include <iostream>
using namespace std;
#include "HugeInteger.h" // include definition of class HugeInteger 
#include "ProductTable.h" // include definitaion of calss ProductTable

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
	HugeInteger product(integer.getSize() + op2.integer.getSize());

	for (size_t i = 0; i < integer.getSize(); i++)
	{
		for (size_t j = 0; j < op2.integer.getSize(); j++)
		{
			product.integer[i + j] = integer[i] * op2.integer[j];
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
      for( int i = size - 1; i >= 0; i-- )
         output << hugeInteger.integer[ i ];

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
	for (size_t i = this->integer.getSize(); i >= 0; i--)
	{
		if (this->integer[i] > right.integer[i])
			return false;
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
	for (size_t i = this->integer.getSize(); i >= 0; i--)
	{
		if (this->integer[i] < right.integer[i])
			return false;
	}

	return true;
		
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
	HugeInteger temp(*this);
	this->helpIncrement();

	return temp;
}

// postfix increment operator
HugeInteger HugeInteger::operator++(int)
{
	this->helpIncrement();
	return *this;
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
	HugeInteger quotient, remainder;
	ProductTable table(right);

	//Form highest digit start
	for (size_t i = this->integer.getSize() - 1; i >= 0; i++)
	{
		//move digit (if this is first loop, skip)
		/*
		move digit form i to i+1
		*/
		if (i < this->integer.getSize() - 1)
		{
			remainder.integer.resize(remainder.integer.getSize() + 1);
			for (size_t j = remainder.integer.getSize(); j >= 0; j++)
				remainder.integer[j] = remainder.integer[j - 1];
		}

		//get next digit
		remainder.integer[0] = this->integer[i];

		//step 2 - 1 Correction size of remainder
		for (; remainder.integer[remainder.integer.getSize() - 1] <= 0 
			&& remainder.integer.getSize() > 0
			; remainder.integer.resize(remainder.integer.getSize() - 1));

		//step 3 平移 quotiend
		if (quotient.integer[quotient.integer.getSize() - 1] > 0)
		{
			quotient.integer.resize(quotient.integer.getSize() + 1);
			for (int j = quotient.integer.getSize(); j >= 0; j--)
				quotient.integer[j + 1] = quotient.integer[j];			
		}

		//step 4 compare remainder & right
		if (remainder >= right)
		{
			//step 4 - 1 if remainder >= right, try to get quotiend
			if (quotient.integer.getSize() == 0)
			{
				quotient.integer.resize(1);
			}
			quotient.integer[0] = table.getScalarForDivison(remainder);

			//step 4 - 2 do subtract
			remainder = remainder - table.getProduct(quotient.integer[0]);

		}

		//step 5 if remainder is divisible, 
		if (remainder.zero())
		{
			//compare digit of remaining of dividend & digit of op2
			if (right.integer.getSize() <= i + 1)
			{
				//digit of remaining of dividend > digit of op2 continue
				continue;
			}
			else
			{
				//Otherwise get remaining to remainder and break;
				//offset remainder
				for (int j = remainder.integer.getSize() - 1; j >= 0; j--)
				{
					remainder.integer[i + j] = remainder.integer[j];
				}
				for (int j = i - 1; j >= 0; j--)
				{
					remainder.integer.resize(remainder.integer.getSize() + 1);
					remainder.integer[j] = integer[j];
				}
				break;
			}
		}
	}

	if (getQuotient)
		return quotient;
	else
		return remainder;
}