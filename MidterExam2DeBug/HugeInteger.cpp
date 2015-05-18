// Member-function definitions for class template HugeInteger
#include "HugeInteger.h" // include definition of class template HugeInteger
#include "Vector.cpp" // include member-function definitions for class template Vector 
#include "Iterator.cpp" // include member-function definitions for class template Iterator

// default constructor
template< typename T >
HugeInteger< T >::HugeInteger( unsigned int size )
   : Vector( size )
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
   for( ; it1 < it2; it1++, it2-- )
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


/* mid exam 2 implement */

template< typename T >
bool HugeInteger<T>::operator<(HugeInteger<T> &right)
{
	// less than
	if (this->getSize() < right.getSize())
		return true;
	if (this->getSize() > right.getSize())
		return false;

	for (Vector<T>::iterator it = this->end() - 1, rightIt = right.end() - 1;
		it >= this->begin();
		it--, rightIt--)
	{

		if (*it > *rightIt)
			return false;

		if (*it < *rightIt)
			return true;
	}
	return false;
}

template< typename T >
HugeInteger<T> HugeInteger<T>::square()
{

	if (this->isZero())
	{
		return *this;
	}

	// the square of HugeInteger
	HugeInteger<T> result(this->getSize() * 2);

	/* 做乘法 */
	for (Vector<T>::iterator thisIt = this->begin(); thisIt < this->end(); thisIt++)
	{
		for (Vector<T>::iterator op2 = this->begin(); op2 < this->end(); op2++)
		{
			*(result.begin() + (thisIt - this->begin()) + (op2 - this->begin())) = *(result.begin() + (thisIt - this->begin()) + (op2 - this->begin())) + (*op2) * (*thisIt);
		}
	}

	/* 處理carry */
	for (Vector<T>::iterator it = result.begin(); it < result.end(); it++)
	{
		if (*it > 9)
		{
			*(it + 1) += *it / 10;
			*it %= 10;
		}
	}

	/* 計算長度 */
	for (Vector<T>::iterator it = result.end() - 1; *it <= 0 && result.getSize() > 1; result.resize(result.getSize() - 1));

	return result;
}

template< typename T >
HugeInteger<T> HugeInteger<T>::squareRoot()
{
	// the square root of HugeInteger

	if (this->isZero())
	{
		return *this;
	}

	HugeInteger<T> result((this->getSize() % 2 == 0) ? this->getSize() / 2 : this->getSize() / 2 + 1);
	for (Vector<T>::iterator it = result.end() - 1; it >= result.begin(); it--)
	{
		while ((result.square() < *this) && (*it < 10))
		{
			(*it)++;
		}
		(*it)--;
	}

	/* 計算長度 */
	for (Vector<T>::iterator it = result.end() - 1; *it <= 0; result.resize(result.getSize() - 1));

	return result;
}

template< typename T >
HugeInteger<T> HugeInteger<T>::operator++(int)
{
	// postfix increment operator

	/*個位數+1*/
	Vector<T>::iterator number = this->begin();
	*number += 1;

	/*處理carray*/
	for (Vector<T>::iterator it = this->begin(); it < this->end() - 2; it++)
	{
		if (*it > 9)
		{
			*(it + 1) += (*it) / 10;
			*it %= 10;
		}
	}

	/* 處理最高位數的carry */
	if (*(this->end() - 1) > 9)
	{
		/* size ++*/
		this->resize(this->getSize() + 1);

		/* carry */
		*(this->end() - 2) += *(this->end() - 3) / 10;
		*(this->end() - 3) %= 10;
	}

	return *this;
}

template < typename T>
bool HugeInteger<T>::isZero()
{
	for (Vector<T>::iterator it = this->begin(); it < this->end(); it++)
	{
		if (*it != 0)
			return false;
	}
	return true;
}