#pragma once
#include "cMasterBlock.h"
#include "windows.h"
#include "wincon.h"
#include "conio.h"
class cSquareBlock : public cMasterBlock
{
public:
	cSquareBlock();
	~cSquareBlock();


	void printSquare(int coordinateX, int coordinateY, int colour, std::string character, bool gameColours);
	void printBar	(int coordinateX, int coordinateY, int colour, std::string character, bool gameColours);
	void printT		(int coordinateX, int coordinateY, int colour, std::string character, bool gameColours);
	void printL		(int coordinateX, int coordinateY, int colour, std::string character, bool gameColours);
	void printTEXT	(int coordinateX, int coordinateY, int colour, std::string character, bool gameColours);
};

