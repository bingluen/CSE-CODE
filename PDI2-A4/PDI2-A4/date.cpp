#include "date.h"

const char Month[13][20] = { "", "January", "February", "March", "April", "May", "June", "July", "August",
"September", "October", "November", "December" };

const int daysOfMonth[2][13] = { { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
{ 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 } };

ostream &operator<<(ostream &out, const Date &date)
{
	out << Month[date.month] << " " << date.day << ", " << date.year;
	return out;
}

Date::Date(int m, int d, int y)
{
	if (m >= 1 && m <= 12)
		this->month = m;
	else
		this->month = 1;

	if (y >= 1900 && y < 2038)
		this->year = y;
	else
		this->year = 1900;

	if (Date::leapyear(this->year))
	{
		if (daysOfMonth[1][this->month] >= d)
			this->day = d;
		else
			this->day = 1;
	}
	else 
	{
		if (daysOfMonth[0][this->month] >= d)
			this->day = d;
		else
			this->day = 1;
	}
}

void Date::setDate(int m, int d, int y)
{
	if (m >= 1 && m <= 12)
		this->month = m;
	else
		this->month = 1;

	if (y >= 1900)
		this->year = y;
	else
		this->year = 1900;

	if (Date::leapyear(this->year))
	{
		if (daysOfMonth[1][this->day] >= d)
			this->day = d;
		else
			this->day = 1;
	}
	else
	{
		if (daysOfMonth[0][this->day] >= d)
			this->day = d;
		else
			this->day = 1;
	}
}

Date &Date::operator++()
{
	this->helpIncrement();
	return *this;
}

Date Date::operator++(int)
{
	Date temp(this->month, this->day, this->year);
	this->helpIncrement();
	return temp;
}

const Date &Date::operator+=(int day)
{
	for (int i = 0; i < day; i++)
		this->helpIncrement();

	return *this;
}

bool Date::leapyear(int year)
{
	/*
		leapyear rule
		if year % 4 == 0 => leapyear
		if year % 100 == 0 => not leapyear
		if year % 400 == 0 => leapyer
	*/

	if (year % 400 == 0)
		return true;

	if (year % 100 == 0)
		return false;

	if (year % 4 == 0)
		return true;

	return false;
}

bool Date::endofMonth(int day) const
{

	if (Date::leapyear(this->year))
		return (daysOfMonth[1][this->month] == day);
	else
		return (daysOfMonth[0][this->month] == day);
}

void Date::helpIncrement()
{
	if (this->endofMonth(this->day))
	{
		this->day = 1;
		this->month++;
	}
	else
	{
		this->day++;
	}

	if (this->month > 12)
	{
		this->month = 1;
		this->year++;
	}
}