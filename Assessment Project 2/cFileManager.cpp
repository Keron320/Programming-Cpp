#include "cFileManager.h"



cFileManager::cFileManager()
{
}


cFileManager::~cFileManager()
{
}

void cFileManager::fileReader()
{
	//int randomVal = 0;
	std::ifstream gameFile;

	srand(time(NULL));
	//randomVal = rand() % 4 + 1;

	gameFile.open("test.txt", std::ifstream::in);
	std::string name, character, line;
	int row, column, colour;
	gameFile >> name >> row >> column >> colour >> character;
	

	while (std::getline(gameFile, line))
	{
		
		std::cout << row << std::endl;
	
	}

}
