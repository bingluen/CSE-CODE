#include <iostream>
#include "Point.h"
#include "Circle.h"
#include "Line.h"
#include "Rectangle.h"
#include "Triangle.h"

using namespace std;

int main()
{
	Line line(1, 1, 10, 10);//(x1,y1,x2,y2) 
	Rectangle rect(10, 10, 90, 50);//(topLeftX,topLeftY,bottomRightX,bottomRightY)
	Triangle triangle(2, 0, 0, 10, 4, 18);//(x1,y1,x2,y2,x3,y3)
	Circle circle(0, 0, 6, 8);//(x1,y1,x2,y2)

	cout << "Line area = " << line.area() << endl;
	cout << "Rectangle area = " << rect.area() << endl;
	cout << "Triangle area = " << triangle.area() << endl;
	cout << "Circle area = " << circle.area() << endl;

	system("pause");
	return 0;
}
