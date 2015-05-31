#ifndef LOGGER_H
#define LOGGER_H
#include "database.h"
#include "lib.h"
class Logger{
public:
	Logger();
	void execute();
	bool isSingedIn();
protected:
	UserDatabase userData;
	User user;
private:
	bool doSignIn();
	void doRegister();
	bool userSignedIn;
};
#endif