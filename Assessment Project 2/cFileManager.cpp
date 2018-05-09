#include "cFileManager.h"




cFileManager::cFileManager()
{
}


cFileManager::~cFileManager()
{
}

int cFileManager::lineCounter()
{
		std::string line;
		//Opens specific file.
		std::ifstream readFile("test.txt");
		//Reads the contents if found the file without error
		int totalLines { 0 };	// Default amount of totallines is 0
		if (readFile.is_open())
		{
			// Reads through lines until no lines left.
			while (getline(readFile, line))
			{
				//counts the total lines of the file
				totalLines++;
			}
			
			// Closes the file after finishing the loop
			return totalLines;
			readFile.close();
		}
		// Error message if something goes wrong and file does not open.
		else 
		{ 
			std::cout << "Unable to open file" << std::endl;
		// returns 0
		return totalLines;
		}

}

void cFileManager::readLine(int x)
{
	std::string line;
	//Opens specific file.
	std::ifstream readFile("test.txt");
	//Reads the contents if found the file without errore
	std::string name = "";
	std::string char1, char2, char3, char4, char5 = "";


	int row = 0, column = 0, colour = 0;
	if (readFile.is_open())
	{
		// Reads through lines until no lines left.
		for (int i = 1; i < x; i++)
		{
			
			getline(readFile, line);
			readFile >> name;// >> column >> colour; // >> character;
			if (name == "//") {
				//getline(readFile, line);
				std::cout << name << line;
					
			}
			else {
			readFile >> row >> column >> colour;
			std::cout << name << " " << row << " " << column << " " << colour; // << " " << character;
			}
			std::cout << "\n";

			
		}
		// Closes the file after finishing the loop
		readFile.close();
	}
	// Error message if something goes wrong and file does not open.
	else std::cout << "Unable to open file";
}

std::string cFileManager::getName(int x, int a)
{
	std::string line;
	//Opens specific file.
	std::ifstream readFile("test.txt");
	//Reads the contents if found the file without error
	std::string name = "";

	// line number basically...
	int intLine = 1; // a will always be atleast 1

	if (readFile.is_open())
	{
		// Loop through all lines
		while(getline(readFile, line))
		{
			if(intLine == a)
			{
				if (name == "//")
				{
				// Do nothing
				}
				else {
					// Read in the name and return it
					readFile >> name;
					return name;
				}
			}
			// if intline is not equal with a
			else { intLine ++; }
		}
		// Closes the file after finishing the loop
		readFile.close();
	}
	// Error message if something goes wrong and file does not open.
	else std::cout << "Unable to open file";
}

int cFileManager::getRow(int x, int i)
{
		std::string line;
		//Opens specific file.
		std::ifstream readFile("test.txt");
		//Reads the contents if found the file without error
		std::string name = "";
		int row = 0;
		if (readFile.is_open())
		{
			// Reads through lines until no lines left.
			for (i = 1; i < x; i++)
			{
				getline(readFile, line);
				readFile >> name >> row;
				if (name == "//") {
					// Do nothing
				}
				else {
					return row;
				}
			}
			// Closes the file after finishing the loop
			readFile.close();
		}
		// Error message if something goes wrong and file does not open.
		else std::cout << "Unable to open file";
}


int cFileManager::getColumn(int x, int i)
{
	std::string line;
	//Opens specific file.
	std::ifstream readFile("test.txt");
	//Reads the contents if found the file without error
	std::string name = "";
	int row = 0;
	int column = 0;
	if (readFile.is_open())
	{
		// Reads through lines until no lines left.
		for ( i = 1; i < x; i++)
		{
			getline(readFile, line);
			readFile >> name >> row >> column;
			if (name == "//") {
				// Do nothing
			}
			else {
				return column;
			}
		}
		// Closes the file after finishing the loop
		readFile.close();
	}
	// Error message if something goes wrong and file does not open.
	else std::cout << "Unable to open file";
}


