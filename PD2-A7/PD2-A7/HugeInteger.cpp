// Member-function definitions for class HugeInteger< T >.
#include "HugeInteger.h" // include definition of class HugeInteger< T > 
#include "Vector.cpp" // include definition of class Vector 
#include "Iterator.cpp" // include definition of class Iterator

// default constructor
template< typename T >
HugeInteger< T >::HugeInteger()
   : Vector()
{
}

// constructor
template< typename T >
HugeInteger< T >::HugeInteger( unsigned int size )
   : Vector( size, 0 )
{
}

// copy constructor
template< typename T >
HugeInteger< T >::HugeInteger( HugeInteger< T > &integerToCopy )
   : Vector( integerToCopy )
{
}

// destructor
template< typename T >
HugeInteger< T >::~HugeInteger()
{
}

// load a HugeInteger from a text file
template< typename T >
void HugeInteger< T >::load( ifstream &inFile )
{
   char digit;
   while( ( digit = inFile.get() ) != '\n' )
      push_back( digit - '0' );

   iterator it1( begin() );
   iterator it2( end() - 1 );
   T temp;
   for( ; it1 < it2; ++it1, --it2 )
   {
      temp = *it1;
      *it1 = *it2;
      *it2 = temp;
   }
}

// overloaded assignment operator;
// const return avoids: ( a1 = a2 ) = a3
template< typename T >
const HugeInteger< T > &HugeInteger< T >::operator=( const HugeInteger< T > &right )
{
   Vector< T >::operator=( right );

   return *this; // enables x = y = z, for example
}

// addition operator; HugeInteger< T > + HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator+( HugeInteger< T > op2 )
{
   unsigned int size = getSize();
   unsigned int op2Size = op2.getSize();
   unsigned int sumSize = ( size >= op2Size ) ? size + 1 : op2Size + 1;

   HugeInteger< T > sum( sumSize );

   for( iterator it1 = begin(), it3 = sum.begin(); it1 < end(); it1++, it3++ )
      *it3 = *it1;

   for( iterator it2 = op2.begin(), it3 = sum.begin(); it2 < op2.end(); it2++, it3++ )
      *it3 += *it2;

   for( iterator it3 = sum.begin(); it3 < sum.end() - 1; it3++ ) 
      if( *it3 > 9 ) 
      {
         *it3 -= 10;
         ( *( it3 + 1 ) )++;
      }

   if( *( sum.end() - 1 ) == 0 )
      sum.resize( sumSize - 1 );

   return sum;
} // end function operator+

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
template< typename T >
void HugeInteger< T >::divideByTen()
{
   for( iterator it = begin() + 1; it < end(); it++ )
      *( it - 1 ) = *it;
   resize( getSize() - 1 );
}

// function that tests if a HugeInteger is zero
template< typename T >
bool HugeInteger< T >::zero()
{
   for( iterator it = begin(); it < end(); it++ )
      if ( *it != 0 )
         return false;
         
   return true;
}

// overloaded output operator for class HugeInteger
template< typename T >
ostream &operator<<( ostream &output, HugeInteger< T > &hugeInteger )
{
   Vector< T >::iterator it;
   if( hugeInteger.getSize() == 0 )
      output << 0;
   else
   {
      for( it = hugeInteger.end() - 1; it > hugeInteger.begin(); it-- )
         output << *it;
      output << *it;
   }

   return output; // enables cout << x << y;
}

/* Assignment 7 - implement*/

template < typename T >
bool HugeInteger< T >::operator<(HugeInteger< T > &right)
{
	// less than

	//compare size
	if (this->getSize() > right.getSize())
		return false;
	if (this->getSize() < right.getSize())
		return true;
	if (*this == right)
		return false;

	//compare every digit
	for (iterator it = this->end() - 1, itR = right.end() - 1;
		it >= this->begin();
		it--, itR--)
	{
		if (*it > *itR)
			return false;
		if (*it < *itR)
			return true;
	}
	return false;
}


template < typename T >
bool HugeInteger< T >::operator>(HugeInteger< T > &right)
{
	// greater than

	//compare size
	if (this->getSize() > right.getSize())
		return true;
	if (this->getSize() < right.getSize())
		return false;
	if (*this == right)
		return false;


	//compare every digit
	for (iterator it = this->end() - 1, itR = right.end() - 1;
		it >= this->begin();
		it--, itR--)
	{
		if (*it > *itR)
			return true;
		if (*it < *itR)
			return false;
	}

	return false;
}

template < typename T >
bool HugeInteger< T >::operator<=(HugeInteger< T > &right)
{
	// less than or equal
	return !(*this > right);
}

template < typename T >
bool HugeInteger< T >::operator>=(HugeInteger< T > &right)
{
	// greater than or equal to

	return !(this->operator< (right));
}

template < typename T >
HugeInteger< T > HugeInteger< T >::operator-(HugeInteger< T > &op2)
{
	// subtraction operator; HugeInteger - HugeInteger

	HugeInteger< T > zero(1);


	if (op2 > *this)
	{
		cout << "Error: Tried to subtract larger value from smaller value.\n";
		return zero;
	}

	if (op2 == *this)
	{
		return zero;
	}

	HugeInteger< T > difference(*this);

	bool doBorrow;

	for (iterator it = difference.begin(), itR = op2.begin();
		itR < op2.end();
		it++, itR++)
	{
		//compare digit
		if (*it < *itR)
			doBorrow = true;
		else
			doBorrow = false;

		//do borrow
		if (doBorrow)
		{
			//record source which is been borrowed
			int count = 1;

			//count where borrowed source from
			for (; *(it + count) == 0; count++);

			//borror 10
			*(it + count) -= 1;

			//for every digit which higher than current digit plus 9
			for (int i = count - 1; i > 0; i--)
				*(it + i) += 9;

			//the current digit plus 10
			*it += 10;
		}

		//do difference
		*it -= *itR;
	}


	//count size
	while (*(difference.end() - 1) == 0)
	{
		difference.resize(difference.getSize() - 1);
	}

	return difference;
}

template < typename T >
HugeInteger< T > HugeInteger< T >::operator*(HugeInteger< T > op2)
{
	// multiplication operator; HugeInteger * HugeInteger

	HugeInteger< T > zero(1);
	HugeInteger< T > product(this->getSize() + op2.getSize());


	//if one of them is zero, return zero
	if (op2.zero() || this->zero())
		return zero;

	for (iterator it = this->begin(); it < this->end(); it++)
	{
		if (*it == 0) continue;
		for (iterator itR = op2.begin(); itR < op2.end(); itR++)
		{
			if (*itR == 0) continue;
			*(product.begin() + (it - this->begin()) + (itR - op2.begin())) = *(product.begin() + (it - this->begin()) + (itR - op2.begin())) + (*it) * (*itR);
		}
	}

	//deal with carry
	for (iterator it = product.begin(); it < product.end(); it++)
	{
		if (*it > 9)
		{
			*(it + 1) += *it / 10;
			*it %= 10;
		}
	}

	//count size
	while (*(product.end() - 1) == 0)
	{
		product.resize(product.getSize() - 1);
	}

	return product;
}
template < typename T >
HugeInteger< T > HugeInteger< T >::operator/(HugeInteger< T > op2)
{
	// division operator; HugeInteger / HugeInteger
	HugeInteger< T > zero(1);
	HugeInteger< T > aidOp(op2);
	HugeInteger< T > remainder(*this), quotient(1);
	if (op2 > *this)
		return zero;

	while (*this >= aidOp)
		aidOp.tenfold();
	aidOp.divideByTen();

	while (remainder >= op2)
	{
		while (remainder >= aidOp)
		{
			remainder = remainder - aidOp;
			(*(quotient.begin()))++;
		}
		quotient.tenfold();
		aidOp.divideByTen();
	}

	quotient.divideByTen();

	return quotient;
}

template < typename T >
HugeInteger< T > HugeInteger< T >::operator%(HugeInteger< T > op2)
{
	// modulus operator; HugeInteger % HugeInteger
	HugeInteger< T > zero(1);
	HugeInteger< T > aidOp(op2);
	HugeInteger< T > remainder(*this), quotient(1);
	if (op2 > *this)
		return zero;

	while (*this >= aidOp)
		aidOp.tenfold();
	aidOp.divideByTen();

	while (remainder >= op2)
	{
		while (remainder >= aidOp)
		{
			remainder = remainder - aidOp;
			(*(quotient.begin()))++;
		}
		quotient.tenfold();
		aidOp.divideByTen();
	}

	quotient.divideByTen();

	return remainder;
}

template < typename T >
HugeInteger< T > &HugeInteger< T >::operator++()
{
	// prefix increment operator
	this->helpIncrement();

	return *this;

}

template < typename T >
HugeInteger<T> HugeInteger< T >::operator++(int)
{
	// postfix increment operator

	HugeInteger temp(*this);
	this->helpIncrement();

	return temp;
}

template < typename T >
void HugeInteger< T >::tenfold()
{
	// Enlarge tenfold
	this->resize(this->getSize() + 1);

	for (iterator it = this->end() - 2; it >= this->begin(); it--)
	{
		*(it + 1) = *it;
	}

	*(this->begin()) = 0;
}

template < typename T >
void HugeInteger< T >::helpIncrement()
{
	// increments a HugeInteger by 1

	(*(this->begin()))++;

	//carry
	for (iterator it = this->begin(); it < this->end() - 1; it++)
	{
		if (*it > 9)
		{
			*(it + 1) += *it / 10;
			*it %= 10;
		}
	}

	//check highest digit
	if (*(this->end() - 1) > 9)
	{
		this->resize(this->getSize() + 1);
		*(this->end() - 1) += *(this->end() - 2) / 10;
		*(this->end() - 2) %= 10;
	}
}