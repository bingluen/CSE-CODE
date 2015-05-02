#ifndef VESSEL_H
#define VESSEL_H
#include <string>
using namespace std;
class Vessel
{
public:
	Vessel();
	~Vessel();
	virtual string name() = 0;
	void setVolume(double);
	double volume();
private:
	double Volume;
};

Vessel::Vessel()
:Volume(0)
{
}

Vessel::~Vessel()
{
}

void Vessel::setVolume(double v)
{
	this->Volume = v;
}

double Vessel::volume()
{
	return this->Volume;
}
#endif