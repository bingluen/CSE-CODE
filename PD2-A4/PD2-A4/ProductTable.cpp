#include "ProductTable.h"
#include <iostream>
using namespace std;


ProductTable::ProductTable()
{
	available = false;
}

ProductTable::ProductTable(const HugeInteger &base)
{
	HugeInteger scalar(1);

	for (unsigned int i = 0; i < 10; i++)
	{
		table[i] = base * scalar;
		scalar.helpIncrement();
	}

	available = true;
}

void ProductTable::setBase(const HugeInteger &base)
{
	HugeInteger scalar(1);

	for (unsigned int i = 0; i < 10; i++)
	{
		table[i] = base * scalar;
		scalar.helpIncrement();
	}

	available = true;
}

unsigned short ProductTable::getScalarForDivison(const HugeInteger &remainder) const
{

	if (!available)
	{
		cerr << "table is not available." << endl;
		return -1;
	}

	size_t i;
	for (i = 0; i < 10 && table[i] <= remainder; i++);

	return i - 1;
}

HugeInteger ProductTable::getProduct(unsigned short scalar) const
{
	if (available && scalar >= 0 && scalar <= 9)
		return table[scalar];
	else
		cerr << "scalar out of bound (0 <= scalar <= 9) or table is not available." << endl;

	return table[0];
}

bool ProductTable::isAvailable()
{
	return available;
}