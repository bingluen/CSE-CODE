#ifndef EXCEPTION_H
#define EXCPETION_H
#include <string>
using namespace std;
class UserError {
public:
	virtual string getMessages() const = 0;
};

class UserNoFound : public UserError {
public:
	string getMessages() const
	{
		return "ID does not exist!!!";
	}
};

class ItemError {
public:
	virtual string getMessages() const = 0;
};

class ItemNoFound : public ItemError {
public:
	string getMessages() const
	{
		return "Product that you chooese does not exist!!";
	}
};
#endif