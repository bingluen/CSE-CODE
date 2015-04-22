#include "Point.h"
#include "Figure.h"


class Line : public Figure
{
public:
	Line();
	Line(int x1, int y1, int x2, int y2);
	~Line();
	void computeArea();
private:
	Point start, end;
};


Line::Line()
: start(0, 0), end(0, 0)
{
}


Line::Line(int x1, int y1, int x2, int y2)
: start(x1, y1), end(x2, y2)
{
	this->computeArea();
}


Line::~Line()
{
}


void Line::computeArea()
{
	this->setArea(0);
}