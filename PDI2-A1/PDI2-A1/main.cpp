#include <iostream>
using namespace std;

class Box
{
public:
	Box()
	{
		cout << "Box Contructor called" << endl;
	}

	Box(float len, float bre, float hei)
	{
		length = len;
		breadth = bre;
		height = hei;
		cout << "Box Contructor called" << endl;
	}

	float volume()
	{
		return length*breadth*height;
	}

	bool compareVolume(Box secondBox)
	{
		if (volume() > secondBox.volume())
			return true;
		else
			return false;
	}

private:
	float length, breadth, height;
};


int main()
{
	Box firstBox(19.0, 11.0, 5.0);
	Box secondBox(17.9, 10.0, 8.0);

	cout << "Volume of first box = " << firstBox.volume() << endl;
	cout << "Volume of second box = " << secondBox.volume() << endl;

	if (firstBox.compareVolume(secondBox))
		cout << "The first box is greater than the second box" << endl;
	else
		cout << "The first box is not greater than the second box" << endl;
	system("pause");
	return 0;
}