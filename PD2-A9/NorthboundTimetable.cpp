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
		/* 讀取 train No. */
		inputFile.read(reinterpret_cast<char *> (&numberChar), sizeof(char)* 8);
		number = numberChar;
		
		/* 時間表逐站讀取 */
		for (size_t i = 0; i < 8; i++)
		{
			char departureTimeChar[8];
			inputFile.read(reinterpret_cast<char *> (&departureTimeChar), sizeof(char)* 8);

			/*北上要反過來，因為時間會是從南邊的車站開始讀取，跟設定的索引順序相反*/
			departureTime[7-i] = departureTimeChar;
		}

		/* push到table(包裝成Train物件） */
		northboundTimetable.push_back(*(new Train(number, departureTime)));
	}

	/* 最後一個會因為eof沒被升起而重複 */
	northboundTimetable.pop_back();
}