#include "Point.h"
#include "Figure.h"

class Circle : public Figure
{
public:
	Circle();
	Circle(int x1, int y1, int x2, int y2);
	~Circle();
	void computeArea();
private:
	Point center;
	float radius;
	static const float PI;
};

const float Circle::PI = 3.1415926;

Circle::Circle()
:center()
{
	radius = 0;
}

Circle::Circle(int x1, int y1, int x2, int y2)
: center(x1, y1)
{
	float xOffset, yOffset;
	xOffset = abs(x1 - x2);
	yOffset = abs(y1 - y2);
	radius = sqrt(xOffset * xOffset + yOffset * yOffset); 
	this->computeArea();
}

Circle::~Circle()
{
}

void Circle::computeArea()
{
	this->setArea(radius * radius * PI);
}