#ifndef USER_H
#define USER_H
#include <string>
using namespace std;

const size_t ID_LENGTH = 20;
const size_t PASSWORD_LENGTH = 20;
const size_t NAME_LENGTH = 50;
const size_t ID_NUMBER_LENGTH = 10;
const size_t EMAIL_LENGTH = 50;
const size_t PHONE_LENGTH = 10;
const size_t ADDRESS_LENGTH = 200;

typedef struct {
	char id[ID_LENGTH + 1];
	char password[PASSWORD_LENGTH + 1];
	char name[NAME_LENGTH + 1];
	char idNumber[ID_NUMBER_LENGTH + 1];
	char email[EMAIL_LENGTH + 1];
	char phone[PHONE_LENGTH + 1];
	char address[ADDRESS_LENGTH + 1];
} UserElement;

class User {
public:
	User();
	User(UserElement);
	string getId();
	string getPassword();
	string getName();
	string getIdNumber();
	string getEmail();
	string getPhone();
	string getAddress();

	void setId(string);
	void setPassword(string);
	void setName(string);
	void setIdNumber(string);
	void setEmail(string);
	void setPhone(string);
	void setAddress(string);

private:
	char id[ID_LENGTH + 1];
	char password[PASSWORD_LENGTH + 1];
	char name[NAME_LENGTH + 1];
	char idNumber[ID_NUMBER_LENGTH + 1];
	char email[EMAIL_LENGTH + 1];
	char phone[PHONE_LENGTH + 1];
	char address[ADDRESS_LENGTH + 1];
};
#endif