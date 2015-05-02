#ifndef CARTON_H
#define CARTON_H
#include "Vessel.h"
class Carton : public Vessel
{
public:
	Carton();
	~Carton();
	string name();
	Carton(double, double, double, string);
private:
	double length, breadth, height;
	string Name;
};

Carton::Carton()
{
}

Carton::~Carton()
{
}

Carton::Carton(double len, double bre, double hei, string name)
:length(len), breadth(bre), height(hei), Name(name)
{
	this->setVolume((len - 0.5)*(hei - 0.5)*(bre - 0.5));
}

string Carton::name()
{
	return this->Name;
}
#endif