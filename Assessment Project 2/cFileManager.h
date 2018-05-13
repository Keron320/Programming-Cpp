#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <sstream>

class cFileManager
{
public:
	cFileManager();
	~cFileManager();

	//counts the amount of lines on a textfile
	int lineCounter();

	//reads the values from a textfile
	void readLine(int);

	// reads through the line to return row value
	std::string getName(int x, int i);

	// reads through the line to return row value
	int getRow(int x, int i);
	int getColumn(int x, int i);
	int getColour(int x, int i);
	std::string getCharacter(int x, int i);

};

