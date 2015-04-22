#ifndef FIGURE_H
#define FIGURE_H
class Figure
{
public:
	Figure();
	~Figure();
	float area();
	virtual void computeArea() = 0;
	void setArea(float area);
	void setArea(int area);
private:
	float areaValue;
};


Figure::Figure()
: areaValue(0)
{
}


Figure::~Figure()
{
}

float Figure::area()
{
	return areaValue;
}


void Figure::setArea(float area)
{
	this->areaValue = area;
}

void Figure::setArea(int area)
{
	this->areaValue = area;
}
#endif