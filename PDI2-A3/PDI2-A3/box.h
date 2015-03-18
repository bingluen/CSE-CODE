#ifndef BOX_H
#define BOX_H
class Box{
public:
	Box();
	Box(double len, double bre, double hei);
	double volume();
	int compareVolume(Box &otherBox);
	double getLength();
	double getBreadth();
	double getHeight();

private:
	double length, breadth, height;
	

};
#endif