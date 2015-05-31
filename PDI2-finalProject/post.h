#ifndef POST_H
#define POST_H

#include "database.h"
#include "lib.h"

class Post : virtual public ItemMan{
public:
	void postItem(User&);
};

#endif