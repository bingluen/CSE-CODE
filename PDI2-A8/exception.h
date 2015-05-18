#ifndef EXCEPTION_H
#define EXCEPTION_H

class NoTrouble
{
public:
	NoTrouble();
	~NoTrouble();

private:

};

NoTrouble::NoTrouble()
{
}

NoTrouble::~NoTrouble()
{
}

class Trouble : public NoTrouble
{
public:
	Trouble();
	~Trouble();

private:

};

Trouble::Trouble()
{
}

Trouble::~Trouble()
{
}


class BigTrouble : public NoTrouble
{
public:
	BigTrouble();
	~BigTrouble();

private:

};

BigTrouble::BigTrouble()
{
}

BigTrouble::~BigTrouble()
{
}
#endif