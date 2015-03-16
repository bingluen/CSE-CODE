#include "Box.h"

Box::Box()
{
	cout << "Box Contructor called" << endl;
}

Box::Box(double len, double bre, double hei, string name)
{
	length = len;
	breadth = bre;
	height = hei;
	_name = name;
	cout << "Box Contructor called" << endl;
}

double Box::volume()
{
	return length*breadth*height;
}

int Box::compareVolume(Box secondBox)
{
	if (volume() > secondBox.volume())
		return 1;
	else
		return -1;
}

string Box::name()
{
	return _name;
}