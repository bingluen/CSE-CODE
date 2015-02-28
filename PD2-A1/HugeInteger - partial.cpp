// Member-function definitions for class HugeInteger.
#include <iostream>
#include "HugeInteger.h" // include definition of class HugeInteger 

// default constructor
HugeInteger::HugeInteger()
{
   size = 0;
} // end HugeInteger default constructor

// constructor
HugeInteger::HugeInteger( int s )
{
   size = ( s > 0 && s <= 1000 ) ? s : 1000;
   for ( int i = 0; i < size; i++ )
      integer[ i ] = 0;
} // end HugeInteger constructor

// load a HugeInteger from a text file
void HugeInteger::load( ifstream &inFile )
{
   char numericString[ 1000 ];
   inFile >> numericString;

   size = strlen( numericString );
	for( int i = 0; i < size; i++ )
		integer[ i ] = numericString[ size - i - 1 ] - '0';
}

// function that tests if a HugeInteger is zero
bool HugeInteger::zero()
{
   for ( int i = 0; i < size; i++ )
      if ( integer[ i ] != 0 )
         return false;
         
   return true;
} // end function zero

// addition operator; HugeInteger + HugeInteger
HugeInteger HugeInteger::add( HugeInteger op2 )
{
   int sumSize = ( size >= op2.size ) ? size + 1 : op2.size + 1;
   HugeInteger sum( sumSize );

   for ( int i = 0; i < size; i++ )
      sum.integer[ i ] = integer[ i ];

   for ( int i = 0; i < op2.size; i++ )
      sum.integer[ i ] += op2.integer[ i ];

   for ( int i = 0; i < sum.size - 1; i++ ) 
      if ( sum.integer[ i ] > 9 ) // determine whether to carry a 1
      {
         sum.integer[ i ] -= 10; // reduce to 0-9
         sum.integer[ i + 1 ]++;
      }

   if( sum.integer[ sum.size - 1 ] == 0 )
      sum.size--;

   return sum;
} // end function add

// overloaded output operator
void HugeInteger::output()
{
   if( size == 0 )
      cout << 0;
   else
      for( int i = size - 1; i >= 0; i-- )
         cout << integer[ i ];
} // end function output

void HugeInteger::divideByTen()
{
   for( int i = 1; i < size; i++ )
      integer[ i - 1 ] = integer[ i ];
   integer[ size ] = 0;
   size--;
} // end function divideByTen

/*
*	Assignment 1
*/

bool HugeInteger::equal(HugeInteger op2)
{
	if (size != op2.size)
		return false;

	for (int i = 0; i < size; i++)
	{
		if (integer[i] != op2.integer[i])
			return false;
	}
	
	return true;

}

bool HugeInteger::notEqual(HugeInteger op2) 
{
	return !equal(op2);
}

bool HugeInteger::less(HugeInteger op2) 
{
	if (size > op2.size)
		return false;

	if (size < op2.size)
		return true;

	if (equal(op2))
		return false;

	for (int i = size -1; i >= 0; i--)
	{
		if (integer[i] < op2.integer[i])
			return true;
	}

	return false;
}

bool HugeInteger::greater(HugeInteger op2) 
{
	if (size > op2.size)
		return true;

	if (size < op2.size)
		return false;

	if (equal(op2))
		return false;

	for (int i = size - 1; i >= 0; i--)
	{
		if (integer[i] < op2.integer[i])
			return false;
	}

	return true;
}

bool HugeInteger::lessEqual(HugeInteger op2)
{
	return !greater(op2);
}

bool HugeInteger::greaterEqual(HugeInteger op2)
{
	return !less(op2);
}



HugeInteger HugeInteger::subtract(HugeInteger op2)
{
	if (less(op2))
		return *(new HugeInteger(1));

	HugeInteger result = HugeInteger(0);

	//do substract
	for (int i = 0; i < op2.size; i++)
	{
		result.integer[i] = result.integer[i] + integer[i] - op2.integer[i];

		// if number < 0, borrow ten
		while (result.integer[i] < 0)
		{
			result.integer[i] %= 10;
			result.integer[i + 1] -= 1;
		}
	}

	for (int i = op2.size; i < size; i++)
	{
		result.integer[i] = result.integer[i] + integer[i];
	}

	//check size
	for (result.size = 1000; result.integer[result.size - 1] == 0 && result.size > 0; result.size--);

	return result;

}// end of fnuction subtract

HugeInteger HugeInteger::multiply(HugeInteger op2)
{
	HugeInteger result = HugeInteger(0);

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < op2.size; j++)
		{
			result.integer[i + j] = result.integer[i + j] + integer[i] * op2.integer[j];
		}
	}

	//carry
	for (int i = 0; i < size + op2.size; i++)
	{
		if (result.integer[i] >= 10)
		{
			int temp = result.integer[i] / 10;
			result.integer[i] %= 10;
			result.integer[i + 1] += temp;
		}
	}

	//check size
	for (result.size = size + op2.size; result.integer[result.size - 1] == 0 && result.size > 0; result.size--);

	return result;
}// end of function multiply

HugeInteger HugeInteger::divide(HugeInteger op2)
{
	if (less(op2))
	{
		return *(new HugeInteger(1));
	}

	if (equal(op2))
	{
		HugeInteger result(1);
		result.integer[0] = 1;
		return result;
	}

	return divideOrModulus(op2, true);
}

HugeInteger HugeInteger::modulus(HugeInteger op2)
{
	if (less(op2))
	{
		return *this;
	}

	if (equal(op2))
	{
		return *(new HugeInteger(1));
	}

	return divideOrModulus(op2, false);
}

HugeInteger HugeInteger::divideOrModulus(HugeInteger op2, bool getDivide)
{
	HugeInteger remainder(1), quotiend(1), product(1);
	for (int i = size; i >= op2.size; i--)
	{
		HugeInteger tempProduct(1), tempQutiend(1);
		remainder.integer[size - i] = integer[i - 1];
		
		if (remainder.greaterEqual(op2))
		{
			//get Q_n
			while (remainder.greaterEqual(tempProduct))
			{
				quotiend.integer[0] = tempQutiend.integer[0];
				tempQutiend.integer[0] += 1;
				product = tempProduct;
				tempProduct = op2.multiply(tempQutiend);
			}

			//get remainder
			for (int j = quotiend.size - 1; j >= 0; j--)
				quotiend.integer[j + 1] = quotiend.integer[j];
			quotiend.size++;
			remainder = remainder.subtract(product);
		}
	}

	//check digit of remainder and qutiend
	for (quotiend.size = size; quotiend.integer[quotiend.size - 1] == 0; quotiend.size--);
	for (remainder.size = size; remainder.integer[remainder.size - 1] == 0; remainder.size--);

	if (getDivide)
		return quotiend;
	else
		return remainder;
}