#include "list.h"


Package::Package(Box *pNewBox)
{
	//make a duplicate of pNewBox and packaged
	pBox = new Box(pNewBox->getLength(), pNewBox->getBreadth(), pNewBox->getHeight());
	pNext = 0;
}

Box* Package::getBox() const
{
	return pBox;
}

Package* Package::getNext() const
{
	return pNext;
}

void Package::setNext(Package* pPackage)
{
	pNext = pPackage;
}

TruckLoad::TruckLoad(Box* pBox, unsigned int count)
{
	//init Object
	pHead = pCurrent = pTail = 0;

	
	if (pBox == 0)
		//case 1 declear a Object without pBox (box array)
		return;
	else
		//case 2 declear a Object with box array and length of array is count
	{
		for (size_t i = 0; i < count; i++)
			addBox(pBox+i);
	}
}

Box* TruckLoad::getFirstBox()
{
	return pHead == 0 ? 0 : pHead->getBox();
}

Box* TruckLoad::getNextBox()
{
	return (pCurrent = pCurrent->getNext()) == 0 ? 0 : pCurrent->getBox();
}

void TruckLoad::addBox(Box* pBox)
{
	if (pHead == 0)
	{
		pHead = pCurrent = pTail = new Package(pBox);
	}
	else
	{
		pTail->setNext(new Package(pBox));
		pTail = pTail->getNext();
	}
}