#ifndef PRODUCT_TABLE_H
#define PRODUCT_TABLE_H
#include "HugeInteger.h"
class ProductTable
{
public:
	//default Constructor
	ProductTable(); 

	//Constructor with table base
	ProductTable(const HugeInteger &base);

	//set table base
	void setBase(const HugeInteger &base);

	//get max scalar of base which lessequal than remainder
	unsigned short getScalarForDivison(const HugeInteger &remainder) const;

	//get scalar * base by pass a scalar (0 <= scalar <= 9)
	HugeInteger getProduct(unsigned short scalar) const;

	//return availability
	bool isAvailable();
private:
	//save scalar table
	HugeInteger table[10];
	
	//before set base, the table can't use;
	bool available;
};
#endif