#include "cMasterBlock.h"



cMasterBlock::cMasterBlock()
{

}


cMasterBlock::~cMasterBlock()
{
}

// Pass value into coordinate
int cMasterBlock::returnX(int x)
{
	coordinateX = x;
	return coordinateX;
}

int cMasterBlock::returnY(int y)
{
	coordinateY = y;
	return coordinateY;
}

int cMasterBlock::returnC(int c)
{
	colour = c;
	return colour;
}

std::string cMasterBlock::returnCharacter(std::string character)
{
	blockName = character;
	return blockName;
}
