#include "cFileManager.h"



cFileManager::cFileManager()
{
}


cFileManager::~cFileManager()
{
}

void cFileManager::fileReader()
{
	std::ifstream gameFile;
	srand(time(NULL));


	gameFile.open("test.txt", std::ifstream::in);
	std::string name, character,line;
	int row, column, colour;

	gameFile >> name >> row >> column >> colour >> character;
	
}
