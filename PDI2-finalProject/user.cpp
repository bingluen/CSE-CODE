#include "user.h"

User::User()
{
}

User::User(UserElement ue)
{
	this->setId(ue.id);
	this->setPassword(ue.password);
	this->setName(ue.name);
	this->setIdNumber(ue.idNumber);
	this->setAddress(ue.address);
	this->setEmail(ue.email);
	this->setPhone(ue.phone);
}

string User::getId()
{
	return this->id;
}
string User::getPassword()
{
	return this->password;
}
string User::getName()
{
	return this->name;
}
string User::getIdNumber()
{
	return this->idNumber;
}
string User::getEmail()
{
	return this->email;
}
string User::getPhone()
{
	return this->phone;
}
string User::getAddress()
{
	return this->address;
}

void User::setId(string id)
{
	if (id.length() <= ID_LENGTH)
		strcpy(this->id, id.c_str());
	else
		strcpy(this->id, id.substr(0, ID_LENGTH).c_str());
}
void User::setPassword(string pw)
{
	if (pw.length() <= PASSWORD_LENGTH)
		strcpy(this->password, pw.c_str());
	else
		strcpy(this->password, pw.substr(0, PASSWORD_LENGTH).c_str());
}
void User::setName(string name)
{
	if (name.length() <= NAME_LENGTH)
		strcpy(this->name, name.c_str());
	else
		strcpy(this->name, name.substr(0, NAME_LENGTH).c_str());
}
void User::setIdNumber(string idNum)
{
	if (idNum.length() <= ID_NUMBER_LENGTH)
		strcpy(this->idNumber, idNum.c_str());
	else
		strcpy(this->idNumber, idNum.substr(0, ID_NUMBER_LENGTH).c_str());
}
void User::setEmail(string email)
{
	if (email.length() <= EMAIL_LENGTH)
		strcpy(this->email, email.c_str());
	else
		strcpy(this->email, email.substr(0, EMAIL_LENGTH).c_str());
}
void User::setPhone(string phone)
{
	if (phone.length() <= PHONE_LENGTH)
		strcpy(this->phone, phone.c_str());
	else
		strcpy(this->phone, phone.substr(0, PHONE_LENGTH).c_str());
}
void User::setAddress(string address)
{
	if (address.length() <= ADDRESS_LENGTH)
		strcpy(this->address, address.c_str());
	else
		strcpy(this->address, address.substr(0, ADDRESS_LENGTH).c_str());
}