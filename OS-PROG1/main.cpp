#include <iostream>
#include <fstream>

using namespace std;

void loadMap(char& , char &[2][20][20]);
void robot(char char &[2][20][20])

int main(int argc, char* argv[])
{
	if(argc <= 1)
	{
		cout << "Please assign a map." << endl;
		fgetc(stdin);
		exit(1);
	}

	char map [2][20][20]
	loadMap(argv[1], map);


}

void loadMap(char& filename, char &map[2][20][20])
{
	ifstream mapFile(filename, ios::in);

	if ( !inFile )
	{
		cout << "File could not be opened" << endl;
		fgetc(stdin);
		exit( 1 );
	}

	char input[20];
	unsigned int row = 0;
	while (mapFile.getline(input, 20))
	{
		if(strlen(input))
		{
			strcpy(map[0][row++], input);
			strcpy(map[1][row++], input);
		}
			
	}

	mapFile.close();
}

