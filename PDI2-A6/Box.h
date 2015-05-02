#ifndef BOX_H
#define BOX_H
#include "Vessel.h"
class Box : public Vessel
{
public:
	Box();
	~Box();
	string name();
	Box(double, double, double, string);
private:
	double length, breadth, height;
	string Name;
};

Box::Box()
:length(0), breadth(0), height(0), Name(NULL)
{
}

Box::~Box()
{
}

Box::Box(double len, double bre, double hei, string name)
:length(len), breadth(bre), height(hei), Name(name)
{
	this->setVolume(len*bre*hei);
}

string Box::name()
{
	return this->Name;
}

#endif