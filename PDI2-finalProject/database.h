#ifndef DATABASE_H
#define DATABASE_H

#include "user.h"
#include "item.h"
#include <vector>

using namespace std;
class UserDatabase{
public:
	UserDatabase();
	bool Insert(Item);
	bool Update(string id, Item);
	bool Detlete(string id);
	Item get(string id);
	size_t size();
private:
	vector< User > userData;
};

class ItemDatabase{
public:
	ItemDatabase();
	bool Insert(Item);
	bool Update(string id, Item);
	bool Detlete(string id);
	Item get(string id);
	size_t size();
private:
	vector< Item > itemData;
};
#endif