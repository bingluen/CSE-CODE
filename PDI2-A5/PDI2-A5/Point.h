#ifndef POINT_H
#define POINT_H

class Point
{
public:
	Point();
	Point(int, int);
	~Point();
	int getX();
	int getY();
private:
	int x, y;
};

Point::Point()
:x(0), y(0)
{
}

Point::Point(int x, int y)
: x(x), y(y)
{

}

Point::~Point()
{
}

int Point::getX()
{
	return x;
}

int Point::getY()
{
	return y;
}
#endif