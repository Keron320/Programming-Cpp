#pragma once
#include <iostream>
#include <Windows.h>
#include <wincon.h>
#include <string>
#include "cFileManager.h"

class cMasterBlock
{
public:
	cMasterBlock();
	~cMasterBlock();

	// returned values are inserted into coordinateX and Y
	int returnX (int x);
	int returnY (int y);
	
	// default values
	unsigned int coordinateX = { 0 };	//Row
	unsigned int coordinateY = { 0 };	//Column
	unsigned int colour = { 0 };		//block colour
	std::string name;					//block name
	char text;							//text on block
};

