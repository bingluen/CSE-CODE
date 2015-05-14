#ifndef TIME_H
#define TIME_H
#include <string>
using namespace std;
class Time {
public:
	Time();
	Time(string);
	string toString();
	void setTime(string );
	Time& operator=(const Time);
	Time operator+(const Time);
	Time operator-(const Time);
	bool operator==(const Time);
	bool operator>=(const Time);
	bool operator<=(const Time);
	bool operator>(const Time);
	bool operator<(const Time);

private:
	int hh, mm;
	void sethour(int);
	void setMin(int);
};

Time::Time()
:hh(0), mm(0)
{
}

Time::Time(string timeString)
: hh(0), mm(0)
{
	int hh;
	hh = timeString.substr(0, 1).c_str()[0] - '0';
	hh *= 10;
	hh += timeString.substr(1, 1).c_str()[0] - '0';
	sethour(hh);

	int mm;
	mm = timeString.substr(3, 1).c_str()[0] - '0';
	mm *= 10;
	mm += timeString.substr(4, 1).c_str()[0] - '0';
	setMin(mm);
}

void Time::setTime(string timeString)
{
	int hh;
	hh = timeString.substr(0, 1).c_str()[0] - '0';
	hh *= 10;
	hh += timeString.substr(1, 0).c_str()[0] - '0';
	sethour(hh);

	int mm;
	mm = timeString.substr(3, 1).c_str()[0] - '0';
	mm *= 10;
	mm += timeString.substr(4, 1).c_str()[0] - '0';
	setMin(mm);
}

bool Time::operator==(const Time time)
{
	if (time.mm == mm && time.hh == hh)
		return true;
	return false;
}

bool Time::operator>=(const Time time)
{
	return !(*this < time);
}

bool Time::operator<=(const Time time)
{
	return !(*this > time);
}

bool Time::operator>(const Time time)
{
	if (time.hh < hh)
		return true;
	else if (time.hh == hh && time.mm < mm)
		return true;

	return false;
}

bool Time::operator<(const Time time)
{
	if (time.hh > hh)
		return true;
	else if (time.hh == hh && time.mm > mm)
		return true;

	return false;
}

Time Time::operator+(const Time time)
{
	Time result;
	result.hh = hh + time.hh;
	result.mm = mm + time.mm;

	return result;
}

Time Time::operator-(const Time time)
{
	Time result;
	result.hh = hh - time.hh;
	result.mm = mm - time.mm;

	return result;
}


void Time::sethour(int hh)
{
	if (hh >= 0 && hh <= 24)
		this->hh = hh;
}

void Time::setMin(int mm)
{
	if (mm >= 0 && mm <= 59)
		this->mm = mm;
}

#endif