#include "ProductTable.h"
#include <iostream>
using namespace std;


ProductTable::ProductTable()
{
	//constructor without base
	//before set base set table is not available
	available = false;
}

ProductTable::ProductTable(const HugeInteger &base)
{
	//constructor with base
	HugeInteger scalar(1);

	//build table
	for (unsigned int i = 0; i < 10; i++)
	{
		table[i] = base * scalar;
		scalar.helpIncrement();
	}

	//after build table, set table is available
	available = true;
}

void ProductTable::setBase(const HugeInteger &base)
{
	HugeInteger scalar(1);

	//build base
	for (unsigned int i = 0; i < 10; i++)
	{
		table[i] = base * scalar;
		scalar.helpIncrement();
	}

	//after build table, set table is available
	available = true;
}

unsigned short ProductTable::getScalarForDivison(const HugeInteger &remainder) const
{

	// if table is not available (table has not been build)
	// return error
	if (!available)
	{
		cerr << "table is not available." << endl;
		return -1;
	}

	//Look-up table
	size_t i;
	for (i = 0; i < 10 && table[i] <= remainder; i++);

	return i - 1;
}

HugeInteger ProductTable::getProduct(unsigned short scalar) const
{
	// if table is available return product ( scalar * base )
	// or return error
	if (available && scalar >= 0 && scalar <= 9)
		return table[scalar];
	else
		cerr << "scalar out of bound (0 <= scalar <= 9) or table is not available." << endl;

	return table[0];
}

bool ProductTable::isAvailable()
{
	//return availability of table
	return available;
}