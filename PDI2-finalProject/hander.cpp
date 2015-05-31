#include "hander.h"
#include <iostream>
#include "exception.h"
using namespace std;

void Hander::login()
{
	execute();
}

void Hander::post()
{
	if (!isSingedIn())
		login();
	postItem(user);
	view();
}

void Hander::view()
{

	if (itemData.size() <= 0)
	{
		cout << "The Commodities is empty" << endl;
		return;
	}

	bool loopFalg = true;

	while (loopFalg)
	{
		showList();

		if (!isSingedIn())
			return;

		bool errorInput = false;
		string input;
		Item buyItem;

		do {
			cout << "Please chooese the Product Id you want buy (enter 0 to exit): ";
			cin >> input;

			if (errorInput = !isNumber(input))
			{
				cout << "Please input Product Id by number" << endl;
				cout << endl;
			}

		} while (errorInput);

		if (atoi(input.c_str()) == 0)
		{
			break;
		}

		try
		{
			buyItem = itemData.get(atoi(input.c_str()));
		}
		catch (const ItemError &e)
		{
			e.getMessages();
			continue;
		}

		if (buyItem.getQuantity() <= 0)
		{
			cout << "Product has been sold!!!" << endl;
			continue;
		}

		if (buyItem.getBuyer() == "null")
		{
			buyItem.setBuyer(user.getId());
		}
		else
		{
			buyItem.setBuyer(buyItem.getBuyer() + ", " +user.getId());
		}

		buyItem.setQuantity(buyItem.getQuantity() - 1);

		itemData.Update(buyItem.getProductId(), buyItem);
	}
}