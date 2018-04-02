#pragma once
#include <iostream>
#include <Windows.h>
#include <wincon.h>
#include <string>

class cMasterBlock
{
public:
	cMasterBlock();
	~cMasterBlock();
	//Read coordinates from textfile.
	unsigned int coordinateX = 0;	//Row
	unsigned int coordinateY = 0;	//Column
	unsigned int colour = 0;
	std::string name;				//block name
	char text;						//text on block


	//Print the block based on location and data.
	void printBlock();
};

