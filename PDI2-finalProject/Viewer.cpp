#include "Viewer.h"
#include <iostream>
#include <iomanip>


using namespace std;

void Viewer::showList()
{
	cout << setw(10) << left << "Product ID"
		<< setw(15) << left << "Product Name"
		<< setw(8) << left << "Price"
		<< setw(9) << left << "Quantity"
		<< setw(8) << left << "Seller"
		<< setw(8) << left << "Buyers"
		<< endl;
	
	
	for (vector<Item>::iterator it = itemData.begin(); it < itemData.end(); it++)
	{
		cout << setw(10) << left << it->getProductId()
			<< setw(15) << left << it->getProductName()
			<< setw(8) << left << it->getPrice()
			<< setw(9) << left << it->getQuantity()
			<< setw(8) << left << it->getSeller()
			<< setw(8) << left << it->getBuyer()
			<< endl;
	}

}