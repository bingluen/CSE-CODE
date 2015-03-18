#include "box.h"
Box::Box()
{

}

Box::Box(double len, double bre, double hei)
{
	length = len;
	breadth = bre;
	height = hei;
}
double Box::volume()
{
	return length * breadth * height;
}

int Box::compareVolume(Box &otherBox)
{
	if (volume() > otherBox.volume())
		return 1;
	else
		return 0;
}

double Box::getLength()
{
	return length;
}
double Box::getBreadth()
{
	return breadth;
}
double Box::getHeight()
{
	return height;
}