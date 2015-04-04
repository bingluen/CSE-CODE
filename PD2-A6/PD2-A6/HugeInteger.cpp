// Member-function definitions for class HugeInteger< T >.
#include "HugeInteger.h" // include definition of class HugeInteger< T > 


// default constructor
template< typename T >
HugeInteger< T >::HugeInteger()
   : Vector()
{
} // end HugeInteger< T > default constructor

// constructor
template< typename T >
HugeInteger< T >::HugeInteger( unsigned int size )
   : Vector( size, 0 )
{
} // end HugeInteger< T > constructor

// constructor
template< typename T >
HugeInteger< T >::HugeInteger( T *first, T *last )
   : Vector( first, last )
{
}

// copy constructor
template< typename T >
HugeInteger< T >::HugeInteger( HugeInteger< T > &integerToCopy )
   : Vector( integerToCopy )
{
} // end HugeInteger< T > copy constructor

// destructor
template< typename T >
HugeInteger< T >::~HugeInteger()
{
} // end HugeInteger< T > destructor

// load a HugeInteger from a text file
template< typename T >
void HugeInteger< T >::load( ifstream &inFile )
{
   char digit;
   while ( ( digit = inFile.get() ) != '\n' )
      push_back( digit - '0' );

   unsigned int size = getSize();
   T temp;
   for ( unsigned int i = 0; i <= ( size - 1 ) / 2; i++ )
   {
      temp = (*this)[ i ];
      ( *this )[ i ] = ( *this )[ size - i - 1 ];
      ( *this )[ size - i - 1 ] = temp;
   }
}

// overloaded assignment operator;
// const return avoids: ( a1 = a2 ) = a3
template< typename T >
const HugeInteger< T > &HugeInteger< T >::operator=( const HugeInteger< T > &right )
{
   Vector< T >::operator=( right );

   return *this; // enables x = y = z, for example
} // end function operator=

// addition operator; HugeInteger< T > + HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator+( HugeInteger< T > &op2 )
{
   unsigned int size = getSize();
   unsigned int op2Size = op2.getSize();
   unsigned int sumSize = ( size >= op2Size ) ? size + 1 : op2Size + 1;

   HugeInteger< T > sum( sumSize );

   for( T *p1 = begin(), *p3 = sum.begin(); p1 < end(); p1++, p3++ )
      *p3 = *p1;

   for( T *p2 = op2.begin(), *p3 = sum.begin(); p2 < op2.end(); p2++, p3++ )
      *p3 += *p2;

   for( T *p3 = sum.begin(); p3 < sum.end() - 1; p3++ ) 
      if( *p3 > 9 ) 
      {
         *p3 -= 10;
         ( *( p3 + 1 ) )++;
      }

   if( *( sum.end() - 1 ) == 0 )
      sum.resize( sumSize - 1 );

   return sum;
} // end function operator+



// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
template< typename T >
void HugeInteger< T >::divideByTen()
{
   for( T *p = begin() + 1; p < end(); p++ )
      *( p - 1 ) = *p;
   resize( getSize() - 1 );
} // end function divideByTen

// function that tests if a HugeInteger is zero
template< typename T >
bool HugeInteger< T >::zero()
{
   for( T *p = begin(); p < end(); p++ )
      if ( *p != 0 )
         return false;
         
   return true;
} // end function zero

// overloaded output operator for class HugeInteger
template< typename T >
ostream &operator<<( ostream &output, HugeInteger< T > &hugeInteger )
{
   if( hugeInteger.getSize() == 0 )
      output << 0;
   else
      for( T *p = hugeInteger.end() - 1; p >= hugeInteger.begin(); p-- )
           output << *p;

   return output; // enables cout << x << y;
} // end function operator<<


/* Assigment 6 - implement */
template< typename T >
bool HugeInteger< T >::operator<(const HugeInteger &right)
{
	// less than
	if (*(this) == right)
		return false;
	if (this->getSize() > right.getSize())
		return false;
	if (this->getSize() < right.getSize())
		return true;


	//compare every digit
	for (T *pLeft = this->end() - 1, *pRight = right.end() - 1;
		pLeft >= this->begin();
		pLeft--, pRight--)
	{
		if (*pLeft > *pRight)
			return false;
		if (*pLeft < *pRight)
			return true;
	}

	return false;
}

template< typename T >
bool HugeInteger< T >::operator>(const HugeInteger &right)
{
	// greater than

	if (*(this) == right)
		return false;
	if (this->getSize() < right.getSize())
		return false;
	if (this->getSize() > right.getSize())
		return true;


	//compare every digit
	for (T *pLeft = this->end() - 1, *pRight = right.end() - 1;
		pLeft >= this->begin();
		pLeft--, pRight--)
	{
		if (*pLeft < *pRight)
			return false;
		if (*pLeft > *pRight)
			return true;
	}

	return false;
}

template< typename T >
bool HugeInteger< T >::operator<=(const HugeInteger &right)
{
	// less than or equal
	return !(this->operator>(right));
}

template< typename T >
bool HugeInteger< T >::operator>=(const HugeInteger &right)
{
	// greater than or equal to
	return !(this->operator<(right));
}


// subtraction operator; HugeInteger< T > - HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator-(HugeInteger< T > &op2)
{
	HugeInteger< T > zero(1);

	// return if first value is smaller; we are not handling negatives
	if (*this < op2)
	{
		cout << "Error: Tried to subtract larger value from smaller value.\n";
		return zero;
	}

	if (*this == op2)
		return zero;

	HugeInteger< T > difference(*this);

	for (T* pRight = op2.begin(), *pDiff = difference.begin();
		pRight < op2.end();
		pRight++, pDiff++)
	{
			//do difference
			*pDiff -= *pRight;
			// if number < 0, borrow ten
			while (*pDiff < 0)
			{
				*pDiff += 10;
				*(pDiff + 1) -= 1;
			}

	}

	//count size
	for (T* ptr = difference.end(); *ptr == 0; difference.resize(difference.getSize() - 1));


	return difference;
} // end function operator-

// multiplication operator; HugeInteger * HugeInteger
template< typename T >
HugeInteger< T > HugeInteger< T >:: operator*(HugeInteger &op2)
{
	//declare product
	HugeInteger< T > product(this->getSize() + op2.getSize());


	//do product
	for (T* pLeft = this->begin(); pLeft < this->end(); pLeft++)
	{
		for (T* pRight = op2.begin(); pRight < op2.end(); pRight++)
		{
			*(product.begin() + (pLeft - this->begin()) + (pRight - op2.begin())) = *pLeft * *pRight;
		}
	}

	//process carry
	for (T* ptr = product.begin(); ptr < product.end(); ptr++)
	{
		if (*ptr > 10)
		{
			*(ptr + 1) += *ptr / 10;
			*ptr %= 10;
		}
	}

	//check size
	for (T* ptr = product.end() - 1;
		product.getSize() > 0 && !(*ptr);
		product.resize(product.getSize() - 1));

	return product;
}

template < typename T >
HugeInteger< T > HugeInteger< T >:: operator*(const HugeInteger &op2)
{
	//declare product
	HugeInteger< T > product(this->getSize() + op2.getSize());


	//do product
	for (T* pLeft = this->begin(); pLeft < this->end(); pLeft++)
	{
		for (T* pRight = op2.begin(); pRight < op2.end(); pRight++)
		{
			*(product.begin() + (pLeft - this->begin()) + (pRight - op2.begin())) = *pLeft * *pRight;
		}
	}

	//process carry
	for (T* ptr = product.begin(); ptr < product.end(); ptr++)
	{
		if (*ptr > 10)
		{
			*(ptr + 1) += *ptr / 10;
			*ptr %= 10;
		}
	}

	//check size
	for (T* ptr = product.end() - 1;
		product.getSize() > 0 && !(*ptr);
		product.resize(product.getSize() - 1));

	return product;
}

// division operator; HugeInteger< T > / HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator/(HugeInteger< T > &op2)
{
	HugeInteger< T > zero(1);
	if (*this < op2)
		return zero;

	return this->doDivision(op2, true);
} // end function operator/

// modulus operator; HugeInteger< T > % HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator%(HugeInteger< T > &op2)
{
	HugeInteger< T > zero(1);
	if (*this < op2)
		return zero;

	return this->doDivision(op2, false);
} // end function operator%

// prefix increment operator
template< typename T >
HugeInteger< T > &HugeInteger< T >::operator++()
{
	

	this->helpIncrement();

	return *this;
}

// postfix increment operator
template< typename T >
HugeInteger< T > HugeInteger< T >::operator++(int)
{
	HugeInteger< T > temp(*this);

	this->helpIncrement();

	return temp;
}

// increments a HugeInteger by 1
template< typename T >
void HugeInteger< T >::helpIncrement()
{
	//increment the lower bit
	(*(this->begin()))++;

	//check carry
	for (T* ptr = this->begin(); ptr < this->end(); ptr++)
	{
		if (*(ptr) > 9)
		{
			*(ptr + 1) += *ptr / 10;
			*ptr %= 10;
		}
	}

	//check hightest bit
	if (*(this->end() - 1) > 9)
	{
		this->reserve(this->getSize() + 1);
		*(this->end() - 1) = *(this->end() - 2) / 10;
		*(this->end() - 2) %= 10;
	}
}

/* addition - Helper function */
template < typename T >
void HugeInteger< T >::shiftDigitLeft()
{
	//first resize
	this->resize(this->getSize() + 1);

	//shift data left
	memmove(this->end() - 1, this->end() - 2, this->getSize() - 1);
}

template < typename T >
HugeInteger< T > HugeInteger< T >::doDivision(const HugeInteger< T > &right, bool getQuotient)
{
	HugeInteger< T > quotient(1), remainder(1);
	ProductTable< T > table(right);

	//start from height digit
	for (T* ptr = this->end() - 1; ptr >= this->begin(); ptr--)
	{
		/*
		Left shift bit before put next bit
		the first time or remainder is zero did not need
		*/
		if (ptr == this->end() - 1 && !remainder.zero())
		{
			remainder.shiftDigitLeft();
		}

		//get Next bit
		*(remainder.begin()) = *ptr;

		//offset quotient, if quotient is not zero
		if (!quotient.zero())
			quotient.shiftDigitLeft();

		//do subtraction & get scalar
		*(quotient.begin()) = table.getScalarForDivision(remainder);
		remainder = remainder - table.getProduct(*(quotient.begin()));
	}

	if (getQuotient)
		return quotient;
	else
		return remainder;
}