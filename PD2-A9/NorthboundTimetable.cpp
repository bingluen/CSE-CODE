#include "NorthboundTimetable.h"
#include <fstream>

using namespace std;


NorthboundTimetable::NorthboundTimetable() {
	// call loadNorthboundTimetable()
	loadNorthboundTimetable();
}

int NorthboundTimetable::getNumberOfTrains() {
	// returns the total number of northbound trains
	return northboundTimetable.size();
}

Train NorthboundTimetable::getTrain(int index) {
	// returns northboundTimetable[ index ]
	return northboundTimetable[index];
}

void NorthboundTimetable::loadNorthboundTimetable() {
	ifstream inputFile("Northbound timetable.dat", ios::in | ios::binary);
	while (!inputFile.eof()) {
		string number, departureTime[8];
		char numberChar[8];
		/* Ū�� train No. */
		inputFile.read(reinterpret_cast<char *> (&numberChar), sizeof(char)* 8);
		number = numberChar;
		
		/* �ɶ���v��Ū�� */
		for (size_t i = 0; i < 8; i++)
		{
			char departureTimeChar[8];
			inputFile.read(reinterpret_cast<char *> (&departureTimeChar), sizeof(char)* 8);

			/*�_�W�n�ϹL�ӡA�]���ɶ��|�O�q�n�䪺�����}�lŪ���A��]�w�����޶��Ǭۤ�*/
			departureTime[7-i] = departureTimeChar;
		}

		/* push��table(�]�˦�Train����^ */
		northboundTimetable.push_back(*(new Train(number, departureTime)));
	}

	/* �̫�@�ӷ|�]��eof�S�Q�ɰ_�ӭ��� */
	northboundTimetable.pop_back();
}