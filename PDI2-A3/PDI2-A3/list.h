#ifndef LIST_H
#define LIST_H
#include "box.h"

class Package {
public:
	Package(Box *pNewBox);
	Box* getBox() const;
	Package* getNext() const;
	void setNext(Package* pPackage);
private:
	Box* pBox;
	Package* pNext;
};

class TruckLoad
{
public:
	TruckLoad(Box* pBox = 0, unsigned int count = 0);
	Box* getFirstBox();
	Box* getNextBox();
	void addBox(Box* pBox);

private:
	Package* pHead;
	Package* pTail;
	Package* pCurrent;
};
#endif