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

	// Really ugly method
	std::string char1, char2, char3, char4, char5 = "";


	int row = 0, column = 0, colour = 0;
	std::string character = "";

	if (readFile.is_open())
	{
		// Reads through lines until no lines left.
		for (int i = 1; i < x; i++)
		{
			
			getline(readFile, line);
			readFile >> name;
			if (name == "T") {
				readFile >> row >> column >> colour;
				std::cout << name << " " << row << " " << column << " " << colour;
			}
			else if (name == "//") {
				readFile >> char1 >> char2 >> char3;
				std::cout << name << " " << char1 << " " << char2 << " " << char3;	
			}

			else if (name == "TEXT") {

				readFile >> row >> column >> colour >> char1;
				if (char1 == "High") {
					readFile >> char2;
					std::cout << name << " " << row << " " << column << " " << colour << " " << char1 << " " << char2;
				}
				else if (char1 == "This") {
					readFile >> char2 >> char3 >> char4 >> char5;
					std::cout << name << " " << row << " " << column << " " << colour << " " << char1 << " " << char2 << " " << char3 << " " << char4 << " " << char5;
				}
			}
			else {
			readFile >> row >> column >> colour >> character;
			std::cout << name << " " << row << " " << column << " " << colour << " " << character;
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
	return "";
}

int cFileManager::getRow(int x, int a)
{
	std::string line;
	//Opens specific file.
	std::ifstream readFile("test.txt");
	//Reads the contents if found the file without error
	std::string name = "";
	int row = 0;

	// line number basically...
	int intLine = 1; // a will always be atleast 1

	if (readFile.is_open())
	{
		// Loop through all lines
		while (getline(readFile, line))
		{
			if (intLine == a)
			{
				if (name == "//")
				{
					// Do nothing
				}
				else {
					// Read in the name and return it
					readFile >> name >> row;
					return row;
				}
			}
			// if intline is not equal with a
			else { intLine++; }
		}
		// Closes the file after finishing the loop
		readFile.close();
	}
	// Error message if something goes wrong and file does not open.
	else std::cout << "Unable to open file";
	return 0;
}

int cFileManager::getColumn(int x, int a)
{
	std::string line;
	//Opens specific file.
	std::ifstream readFile("test.txt");
	//Reads the contents if found the file without error
	std::string name = "";
	int row = 0;
	int column = 0;


	// line number basically...
	int intLine = 1; // a will always be atleast 1

	if (readFile.is_open())
	{
		// Loop through all lines
		while (getline(readFile, line))
		{
			if (intLine == a)
			{
				if (name == "//")
				{
					// Do nothing
				}
				else {
					// Read in the name and return it
					readFile >> name >> row >> column;
					return column;
				}
			}
			// if intline is not equal with a
			else { intLine++; }
		}
		// Closes the file after finishing the loop
		readFile.close();
	}
	// Error message if something goes wrong and file does not open.
	else std::cout << "Unable to open file";
	return 0;
}


int cFileManager::getColour(int x, int a)
{
	std::string line;
	//Opens specific file.
	std::ifstream readFile("test.txt");
	//Reads the contents if found the file without error
	std::string name = "";
	int row = 0;
	int column = 0;
	int colour = 0;

	// line number basically...
	int intLine = 1; // a will always be atleast 1

	if (readFile.is_open())
	{
		// Loop through all lines
		while (getline(readFile, line))
		{
			if (intLine == a)
			{
				if (name == "//")
				{
					// Do nothing
				}
				else {
					// Read in the name and return it
					readFile >> name >> row >> column >> colour;
					return colour;
				}
			}
			// if intline is not equal with a
			else { intLine++; }
		}
		// Closes the file after finishing the loop
		readFile.close();
	}
	// Error message if something goes wrong and file does not open.
	else std::cout << "Unable to open file";
	return 0;
}

std::string cFileManager::getCharacter(int x, int a)
{
	std::string line;
	//Opens specific file.
	std::ifstream readFile("test.txt");
	//Reads the contents if found the file without error
	std::string name = "";
	std::string character = "";
	int row = 0;
	int column = 0;
	int colour = 0;

	// line number basically...
	int intLine = 1; // a will always be atleast 1

	if (readFile.is_open())
	{
		// Loop through all lines
		while (getline(readFile, line))
		{
			
			if (name == "//")
			{
				intLine++;
			}

			if (intLine == a)
			{

				
				if (name == "T") {
					// Do nothing
				}
				readFile >> name >> row >> column >> colour >> character;
				// Returns custom made data based on whats on the text
				if (name == "TEXT") {
					readFile >> name >> row >> column >> colour >> character;
					if (character == "High") {
						character = "High Score ";
						return character;

					}
					else if (character == "This") {
						character = "This is the last line";
						return character;
					}
				}

				else {
					// Read in the name and return it
					return character;
				}
			}
			// if intline is not equal with a
			else { intLine++; }
		}
		// Closes the file after finishing the loop
		readFile.close();
	}
	// Error message if something goes wrong and file does not open.
	else std::cout << "Unable to open file";
	return 0; // Crashes the program when things are not going the way they should
}
