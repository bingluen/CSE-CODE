#ifndef ITEM_H
#define ITEM_H
#include <string>
using namespace std;

const size_t PRODUCT_NAME_LENGTH = 50;
const size_t SELLER_LENGTH = 20;
const size_t BUYER_LENGTH = 50;

typedef struct {
	long long unsigned int productId, price, quantity;
	char productName[PRODUCT_NAME_LENGTH + 1];
	char seller[SELLER_LENGTH + 1];
	char buyer[BUYER_LENGTH + 1];
} ItemElement;

class Item {
public:
	Item();
	Item(ItemElement);
	long long unsigned int getProductId();
	long long unsigned int getPrice();
	long long unsigned int getQuantity();
	string getProductName();
	string getSeller();
	string getBuyer();

	void setProductId(long long unsigned int);
	void setPrice(long long unsigned int);
	void setQuantity(long long unsigned int);
	void setProductName(string);
	void setSeller(string);
	void setBuyer(string);
private:
	long long unsigned int productId, price, quantity;
	char productName[PRODUCT_NAME_LENGTH + 1];
	char seller[SELLER_LENGTH + 1];
	char buyer[BUYER_LENGTH + 1];
};
#endif