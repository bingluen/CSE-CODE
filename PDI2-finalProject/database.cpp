#include "database.h"
#include <iostream>
#include <fstream>
#include "exception.h"

UserDatabase::UserDatabase()
{
	ifstream UserData("member.dat", ios::in | ios::binary);

	if (!UserData)
	{
		ofstream UserData("member.dat", ios::app | ios::binary);
		UserData.close();
		return;
	}
	else
	{
		while (!UserData.eof())
		{
			UserElement member;
			UserData.read(reinterpret_cast<char*> (&member), sizeof(UserElement));

			User memberObject(member);

			this->userData.push_back(memberObject);
		}
		/* pop 多餘的一個 */
		this->userData.pop_back();
	}
	UserData.close();
}
UserDatabase::~UserDatabase()
{
	ofstream saving("member.dat", ios::out | ios::binary);
	for (size_t i = 0; i < this->size(); i++)
	{
		UserElement member;
		strcpy(member.address, userData[i].getAddress().c_str());
		strcpy(member.email, userData[i].getEmail().c_str());
		strcpy(member.id, userData[i].getId().c_str());
		strcpy(member.idNumber, userData[i].getIdNumber().c_str());
		strcpy(member.name, userData[i].getName().c_str());
		strcpy(member.password, userData[i].getPassword().c_str());
		strcpy(member.phone, userData[i].getPhone().c_str());
		saving.write(reinterpret_cast<char *> (&member), sizeof(UserElement));
	}
	saving.close();
}
bool UserDatabase::Insert(User user)
{
	userData.push_back(user);
	ofstream saving("member.dat", ios::out | ios::binary);
	for (size_t i = 0; i < this->size(); i++)
	{
		UserElement member;
		strcpy(member.address, userData[i].getAddress().c_str());
		strcpy(member.email, userData[i].getEmail().c_str());
		strcpy(member.id, userData[i].getId().c_str());
		strcpy(member.idNumber, userData[i].getIdNumber().c_str());
		strcpy(member.name, userData[i].getName().c_str());
		strcpy(member.password, userData[i].getPassword().c_str());
		strcpy(member.phone, userData[i].getPhone().c_str());
		saving.write(reinterpret_cast<char *> (&member), sizeof(UserElement));
	}
	saving.close();
	return true;
}

bool UserDatabase::Update(string id, User user)
{
	for (size_t i = 0; i < userData.size(); i++)
	{
		if (userData[i].getId() == id)
		{
			userData[i].setAddress(user.getAddress());
			userData[i].setEmail(user.getEmail());
			userData[i].setId(user.getId());
			userData[i].setIdNumber(user.getIdNumber());
			userData[i].setName(user.getName());
			userData[i].setPassword(user.getPassword());
			userData[i].setPhone(user.getPhone());
			return true;
		}
	}

	ofstream saving("member.dat", ios::out | ios::binary);
	for (size_t i = 0; i < this->size(); i++)
	{
		UserElement member;
		strcpy(member.address, userData[i].getAddress().c_str());
		strcpy(member.email, userData[i].getEmail().c_str());
		strcpy(member.id, userData[i].getId().c_str());
		strcpy(member.idNumber, userData[i].getIdNumber().c_str());
		strcpy(member.name, userData[i].getName().c_str());
		strcpy(member.password, userData[i].getPassword().c_str());
		strcpy(member.phone, userData[i].getPhone().c_str());
		saving.write(reinterpret_cast<char *> (&member), sizeof(UserElement));
	}
	saving.close();
	return false;
}

bool UserDatabase::Detlete(string id)
{
	for (size_t i = 0; i < userData.size(); i++)
	{
		if (userData[i].getId() == id)
		{
			userData.erase(userData.begin() + i);
			return true;
		}
	}

	ofstream saving("member.dat", ios::out | ios::binary);
	for (size_t i = 0; i < this->size(); i++)
	{
		UserElement member;
		strcpy(member.address, userData[i].getAddress().c_str());
		strcpy(member.email, userData[i].getEmail().c_str());
		strcpy(member.id, userData[i].getId().c_str());
		strcpy(member.idNumber, userData[i].getIdNumber().c_str());
		strcpy(member.name, userData[i].getName().c_str());
		strcpy(member.password, userData[i].getPassword().c_str());
		strcpy(member.phone, userData[i].getPhone().c_str());
		saving.write(reinterpret_cast<char *> (&member), sizeof(UserElement));
	}
	saving.close();
	return false;
}

bool UserDatabase::idDuplicate(string id)
{
	try
	{
		get(id);
	}
	catch (UserNoFound)
	{
		return false;
	}
	return true;
}

User UserDatabase::get(string id)
{
	for (size_t i = 0; i < userData.size(); i++)
		if (userData[i].getId() == id)
			return userData[i];
	throw UserNoFound();
}
size_t UserDatabase::size()
{
	return userData.size();
}

ItemDatabase::ItemDatabase()
{
	ifstream ItemData("commodities.dat", ios::in | ios::binary);

	if (!ItemData)
	{
		ofstream ItemData("commodities.dat", ios::out | ios::binary);
		ItemData.close();
		return;
	}

	while (!ItemData.eof())
	{
		ItemElement item;
		ItemData.read(reinterpret_cast<char*> (&item), sizeof(ItemElement));

		Item ItemObject(item);

		this->itemData.push_back(ItemObject);
	}
	ItemData.close();
	/* pop 多餘的一個 */
	this->itemData.pop_back();
}
ItemDatabase::~ItemDatabase()
{
	ofstream saving("commodities.dat", ios::out | ios::binary);
	for (size_t i = 0; i < this->size(); i++)
	{
		ItemElement item;
		strcpy(item.buyer, itemData[i].getBuyer().c_str());
		item.price = itemData[i].getPrice();
		item.productId = itemData[i].getProductId();
		strcpy(item.productName, itemData[i].getProductName().c_str());
		item.quantity = itemData[i].getQuantity();
		strcpy(item.seller, itemData[i].getSeller().c_str());
		saving.write(reinterpret_cast<char *> (&item), sizeof(ItemElement));
	}
	saving.close();
}
bool ItemDatabase::Insert(Item item)
{
	this->itemData.push_back(item);
	ofstream saving("commodities.dat", ios::out | ios::binary);
	for (size_t i = 0; i < this->size(); i++)
	{
		ItemElement item;
		strcpy(item.buyer, itemData[i].getBuyer().c_str());
		item.price = itemData[i].getPrice();
		item.productId = itemData[i].getProductId();
		strcpy(item.productName, itemData[i].getProductName().c_str());
		item.quantity = itemData[i].getQuantity();
		strcpy(item.seller, itemData[i].getSeller().c_str());
		saving.write(reinterpret_cast<char *> (&item), sizeof(ItemElement));
	}
	saving.close();
	return true;
}
bool ItemDatabase::Update(long long unsigned int id, Item item)
{
	for (size_t i = 0; i < itemData.size(); i++)
	{
		if (itemData[i].getProductId() == id)
		{
			itemData[i].setBuyer(item.getBuyer());
			itemData[i].setPrice(item.getPrice());
			itemData[i].setProductName(item.getProductName());
			itemData[i].setQuantity(item.getQuantity());
			itemData[i].setSeller(item.getSeller());
			return true;
		}
	}

	ofstream saving("commodities.dat", ios::out | ios::binary);
	for (size_t i = 0; i < this->size(); i++)
	{
		ItemElement item;
		strcpy(item.buyer, itemData[i].getBuyer().c_str());
		item.price = itemData[i].getPrice();
		item.productId = itemData[i].getProductId();
		strcpy(item.productName, itemData[i].getProductName().c_str());
		item.quantity = itemData[i].getQuantity();
		strcpy(item.seller, itemData[i].getSeller().c_str());
		saving.write(reinterpret_cast<char *> (&item), sizeof(ItemElement));
	}
	saving.close();
	return false;
}
bool ItemDatabase::Detlete(long long unsigned int  id)
{
	for (size_t i = 0; i < itemData.size(); i++)
	{
		if (itemData[i].getProductId() == id)
		{
			itemData.erase(itemData.begin() + i);
			return true;
		}
	}

	ofstream saving("commodities.dat", ios::out | ios::binary);
	for (size_t i = 0; i < this->size(); i++)
	{
		ItemElement item;
		strcpy(item.buyer, itemData[i].getBuyer().c_str());
		item.price = itemData[i].getPrice();
		item.productId = itemData[i].getProductId();
		strcpy(item.productName, itemData[i].getProductName().c_str());
		item.quantity = itemData[i].getQuantity();
		strcpy(item.seller, itemData[i].getSeller().c_str());
		saving.write(reinterpret_cast<char *> (&item), sizeof(ItemElement));
	}
	saving.close();
	return false;
}
Item ItemDatabase::get(long long unsigned int  id)
{
	for (size_t i = 0; i < itemData.size(); i++)
	{
		if (itemData[i].getProductId() == id)
		{
			return itemData[i];
		}
	}

	throw ItemNoFound();
}
size_t ItemDatabase::size()
{
	return itemData.size();
}

vector< Item >::iterator ItemDatabase::begin()
{
	return itemData.begin();
}
vector< Item >::iterator ItemDatabase::end()
{
	return itemData.end();
}