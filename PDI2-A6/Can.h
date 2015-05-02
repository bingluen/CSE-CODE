#ifndef CAN_H
#define CAN_H
#include "Vessel.h"
class Can : public Vessel
{
public:
	Can();
	~Can();
	Can(double, double, string);
	string name();
private:
	double diameter, height;
	string Name;
	static const double pi;
};

const double Can::pi = 3.14159265;

Can::Can()
{
}

Can::~Can()
{
}

Can::Can(double diameter, double height, string Name)
:diameter(diameter), height(height), Name(Name)
{
	this->setVolume(diameter * diameter / 4.0 *pi*height);
}

string Can::name()
{
	return this->Name;
}
#endif