#include <iostream>
#include "date.h"

using namespace std;

int  main()
{
	Date d1;
	Date d2(12, 27, 1992);
	Date d3(0, 99, 8045);

	cout << "d1 is " << d1 << endl
		<< "d2 is " << d2 << endl
		<< "d3 is " << d3 << endl << endl;

	cout << "d2 += 7 is " << (d2 += 7) << endl << endl;

	d3.setDate(2, 28, 1992);
	cout << "d3 is " << d3 << endl;
	cout << "++d3 is " << ++d3 << endl << endl;

	Date d4(7, 13, 2002);

	cout << "  d4 is " << d4 << endl;
	cout << "++d4 is " << ++d4 << endl;
	cout << "  d4 is " << d4 << endl << endl;
	cout << "  d4 is " << d4 << endl;
	cout << "d4++ is " << d4++ << endl;
	cout << "  d4 is " << d4 << endl;

	system("pause");
	return 0;
}
