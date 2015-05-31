#ifndef HANDER_H
#define HANDER_H

#include "post.h"
#include "logger.h"
#include "Viewer.h"
#include "lib.h"
class Hander : virtual public Post, virtual public Logger, virtual public Viewer {
public:
	void login();
	void post();
	void view();
};
#endif