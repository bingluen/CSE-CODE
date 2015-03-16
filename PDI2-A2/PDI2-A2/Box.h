#include <iostream>
#include <string>
#ifndef BOX_H
#define BOX_H

using namespace std;
class Box
{
public:
	Box();
	Box(double len, double bre, double hei, string name);
	double volume();
	int compareVolume(Box secondBox);
	string name();
private:
	double length, breadth, height;
	string _name;
};
#endif