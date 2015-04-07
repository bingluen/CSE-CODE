#ifndef PRODUCT_TABLE_H
#define PRODUCT_TABLE_H
#include "HugeInteger.h"

template < typename T >
class ProductTable {
public:
	//default construct
	ProductTable();

	//construct with table
	ProductTable(HugeInteger< T > &base);

	//set table base
	void setBase( HugeInteger< T > &base);

	//get max scalar of base which less then or equal to remainder
	unsigned short getScalarForDivision(const HugeInteger< T > &remainder);

	//get scalar * base by pass scalar ( 0 <= scalar <= 9)
	HugeInteger< T > getProduct(unsigned short scalar);

	//return true if table has been build
	bool isAvailable();

private:
	HugeInteger< T > table[10];

	bool available;

};


template < typename T >
ProductTable< T >::ProductTable()
{
	this->available = false;
}

template < typename T >
ProductTable< T >::ProductTable(HugeInteger<T> &base)
{
	this->setBase(base);
}

template < typename T >
void ProductTable< T >::setBase(HugeInteger<T> &base)
{
	HugeInteger< T > *scalar = new HugeInteger<T>(1);
	for (unsigned short i = 0; i < 10; i++)
	{
		this->table[i] = (*scalar) * base;
		(*scalar)++;
		//cout << table[i] << endl;
	}


	this->available = true;
}

template < typename T >
unsigned short ProductTable< T >::getScalarForDivision(const HugeInteger< T > &remainder)
{
	unsigned short i;
	for (i = 0; i <= 10; i++)
	{
		if (table[i] > remainder)
			break;
	}

	return --i;
}

template < typename T >
HugeInteger< T > ProductTable< T >::getProduct(unsigned short scalar)
{
	if (this->available && scalar >= 0 && scalar <= 9)
		return table[scalar];
	else
		cerr << "scalar out of bound (0 <= scalar <= 9) or table is not available." << endl;
	return table[0];
}

template < typename T > 
bool ProductTable< T >::isAvailable()
{
	return this->available;
}
#endif