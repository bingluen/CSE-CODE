#include "Point.h"
#include "Figure.h"

class Triangle : public Figure
{
public:
	Triangle();
	Triangle(int x1, int y1, int x2, int y2, int x3, int y3);
	~Triangle();
	void computeArea();
private:
	Point p1, p2, p3;
};

Triangle::Triangle()
{
}

Triangle::Triangle(int x1, int y1, int x2, int y2, int x3, int y3)
:p1(x1, y1), p2(x2, y2), p3(x3, y3)
{
	this->computeArea();
}

Triangle::~Triangle()
{
}

void Triangle::computeArea()
{
	/* 
	 * 給三點求 面積 (ノ｀Д´)ノ彡┻━┻
	 * 還好小弟高中數學還不錯(๑╹ڡ╹๑)
	 */
	
	/* 向量公式
	 * AB = (x1 - x2, y1 - y2) = (X1, Y1)
	 * AC = (x1 - x3, y1 - y3) = (X2, Y2)
	 * 1  ｜ X1 Y1 ｜    1
	 * — |｜       ｜| = — |(X1Y2 - Y1X2)| = 1/2 * |{ [(x1-x2)(y1-y3)] - [(x1-x3)(y1-y2)] }|
	 * 2  ｜ X2 Y2 ｜    2
	 */
	this->setArea((float)1 / 2 * abs( ((p1.getX() - p2.getX()) * (p1.getY() - p3.getY()) - (p1.getX() - p3.getX()) * (p1.getY() - p2.getY())) ));

	/* 還有海龍公式喔^口^
	 * a = sqrt( abs(x1-x2) * abs(x1-x2) + abs(y1-y2) * abs(y1-y2) ) 
	 * b = sqrt( abs(x1-x3) * abs(x1-x3) + abs(y1-y3) * abs(y1-y3) )
	 * c = sqrt( abs(x2-x3) * abs(x2-x3) + abs(y2-y3) * abs(y2-y3) )
	 * s = (float) (a + b + c) / 2
	 * area = sqrt( s * (s-a) * (s-b) * (s-c) )
	 */
}