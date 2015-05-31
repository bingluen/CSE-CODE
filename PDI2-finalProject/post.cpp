#include "post.h"
#include <iostream>


using namespace std;

void Post::postItem(User &user)
{
	Item newItem;
	string input;
	char name[PRODUCT_NAME_LENGTH + 1];
	newItem.setSeller(user.getId());
	newItem.setProductId(itemData.size() + 1);
	newItem.setBuyer("null");

	cout << "Please input the product name you want to sell: ";
	cin.ignore();
	cin.getline(name, PRODUCT_NAME_LENGTH, '\n');
	newItem.setProductName(name);
	
	bool errorInput;
	
	
	errorInput = false;
	do {
		cout << "Please input the price of the product: ";
		cin >> input;
		if (errorInput = !isNumber(input))
		{
			cout << "Please input number as price\n" << endl;
		}
	} while (errorInput);
	newItem.setPrice(atoi(input.c_str()));

	errorInput = false;
	do{
		cout << "Please input the quantity of the product: ";
		cin >> input;
		if (errorInput = !isNumber(input))
		{
			cout << "Please input number as quantity\n" << endl;
		}
	} while (errorInput);
	newItem.setQuantity(atoi(input.c_str()));

	itemData.Insert(newItem);
}