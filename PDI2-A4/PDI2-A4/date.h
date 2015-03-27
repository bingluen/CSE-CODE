#ifndef DATE_H
#define DATE_H
#include <iostream>
using namespace std;

class Date{
	friend ostream &operator<<(ostream &, const Date &);
public:
	Date(int m = 1, int d = 1, int y = 1900);
	void setDate(int, int, int);
	Date &operator++();
	Date operator++(int);
	const Date &operator+=(int);
	static bool leapyear(int);
	bool endofMonth(int) const;
private:
	int month;
	int day;
	int year;
	static const int days[];
	void helpIncrement();
};
#endif
