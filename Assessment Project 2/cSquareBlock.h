#pragma once
#include "cMasterBlock.h"
class cSquareBlock : public cMasterBlock
{
public:
	cSquareBlock();
	~cSquareBlock();


	void printSquare(int coordinateX, int coordinateY);
	void eraseSquare(int coordinateX, int coordinateY);
	void printBar	(int coordinateX, int coordinateY);
};

