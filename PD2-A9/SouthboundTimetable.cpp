#include "SouthboundTimetable.h"


SouthboundTimetable::SouthboundTimetable() {
	// call loadSouthboundTimetable()
	loadSouthboundTimetable();
}

int SouthboundTimetable::getNumberOfTrains() {
	// returns the total number of southbound trains
	return southboundTimetable.size();
}

Train SouthboundTimetable::getTrain(int index) {
	// returns southboundTimetable[ index ]
	return southboundTimetable[index];
}

void SouthboundTimetable::loadSouthboundTimetable() {
	ifstream inputFile("Southbound timetable.dat", ios::in | ios::binary);

	if (!inputFile)
	{
		exit(1);
	}

	while (!inputFile.eof()) {
		string number, departureTime[8];
		char numberChar[8];
		/* Ū�XTrain No. */
		inputFile.read(reinterpret_cast<char *> (&numberChar), sizeof(char)* 8);

		number = numberChar;

		/* Ū���쯸�ɶ� */
		for (size_t i = 0; i < 8; i++)
		{	
			char departureTimeChar[8];
			inputFile.read(reinterpret_cast<char *> (&departureTimeChar), sizeof(char)* 8);
			departureTime[i] = departureTimeChar;
		}

		/* push��table(�]�˦�Train����^ */
		southboundTimetable.push_back(*(new Train(number, departureTime)));
	}

	/* �̫�@�ӷ|�]��eof�S�Q�ɰ_�ӭ��� */
	southboundTimetable.pop_back();
}