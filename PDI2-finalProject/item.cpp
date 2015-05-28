#include "item.h"

long long unsigned int Item::getProductId()
{
	return this->productId;
}
long long unsigned int Item::getPrice()
{
	return this->price;
}
long long unsigned int Item::getQuantity()
{
	return this->quantity;
}
string Item::getProductName()
{
	return string(this->productName);
}
string Item::getSeller()
{
	return string(this->seller);
}
string Item::getBuyer()
{
	return string(this->buyer);
}

void Item::setProductId(long long unsigned int id)
{
	this->productId = id;
}
void Item::setPrice(long long unsigned int p)
{
	this->price = p;
}
void Item::setQuantity(long long unsigned int q)
{
	this->quantity = q;
}
void Item::setProductName(string pn)
{
	if (pn.length() <= PRODUCT_NAME_LENGTH)
		strcpy(this->productName, pn.c_str());
	else
		strcpy(this->productName, pn.substr(0, PRODUCT_NAME_LENGTH).c_str());
}
void Item::setSeller(string s)
{
	if (s.length() <= SELLER_LENGTH)
		strcpy(this->seller, s.c_str());
	else
		strcpy(this->seller, s.substr(0, SELLER_LENGTH).c_str());
}
void Item::setBuyer(string b)
{
	if (b.length() <= BUYER_LENGTH)
		strcpy(this->buyer, b.c_str());
	else
		strcpy(this->buyer, b.substr(0, BUYER_LENGTH).c_str());
}