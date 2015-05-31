#ifndef DATABASE_H
#define DATABASE_H

#include "user.h"
#include "item.h"
#include <vector>
#include <iterator>

using namespace std;
class UserDatabase{
public:
	UserDatabase();
	~UserDatabase();
	bool Insert(User);
	bool Update(string id, User);
	bool Detlete(string id);
	bool idDuplicate(string id);
	User get(string id);
	size_t size();
private:
	vector< User > userData;
};

class ItemDatabase{
public:
	ItemDatabase();
	~ItemDatabase();
	vector< Item >::iterator begin();
	vector< Item >::iterator end();
	bool Insert(Item);
	bool Update(long long unsigned int  id, Item);
	bool Detlete(long long unsigned int  id);
	Item get(long long unsigned int  id);
	size_t size();
private:
	vector< Item > itemData;
};

class ItemMan{
protected:
	ItemDatabase itemData;
};
#endif