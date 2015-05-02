#include <iostream>
#include "Box.h"
#include "ToughPack.h"
#include "Carton.h"
#include "Can.h"

using namespace std;

int main()
{
	Box box(40, 30, 20, "Box");
	Can can(10, 3, "Can");
	Carton carton(40, 30, 20, "Carton");
	ToughPack toughpack(40, 30, 20, "ToughPack");

	Vessel* pVessels[] = { &box, &can, &carton, &toughpack };

	for (int i = 0; i < sizeof pVessels / sizeof(pVessels[0]); i++)
		cout << "Volume of " << pVessels[i]->name() << " is " << pVessels[i]->volume() << endl;
	system("pause");
	return 0;
}
