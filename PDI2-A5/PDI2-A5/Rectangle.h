#include "Point.h"
#include "Figure.h"


class Rectangle : public Figure
{
public:
	Rectangle();
	Rectangle(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY);
	~Rectangle();
	void computeArea();
private:
	Point topLeft, bottomRight;
};


Rectangle::Rectangle()
: topLeft(0, 0), bottomRight(0, 0)
{
	this->setArea(0);
}


Rectangle::Rectangle(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY)
: topLeft(topLeftX, topLeftY), bottomRight(bottomRightX, bottomRightY)
{
	this->computeArea();
}


Rectangle::~Rectangle()
{
}


void Rectangle::computeArea()
{
	this->setArea(abs(this->topLeft.getX() - this->bottomRight.getX()) * abs(this->topLeft.getY() - this->bottomRight.getY()));
}