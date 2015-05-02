#ifndef TOUGHPACK_H
#define TOUGHPACK_H
#include "Vessel.h"
class ToughPack : public Vessel
{
public:
	ToughPack();
	~ToughPack();
	string name();
	ToughPack(double, double, double, string);
private:
	double length, breadth, height;
	string Name;
};

ToughPack::ToughPack()
{
}

ToughPack::~ToughPack()
{
}

ToughPack::ToughPack(double len, double bre, double hei, string name)
:length(len), breadth(bre), height(hei), Name(name)
{
	this->setVolume(0.85*len*bre*hei);
}

string ToughPack::name()
{
	return this->Name;
}
#endif