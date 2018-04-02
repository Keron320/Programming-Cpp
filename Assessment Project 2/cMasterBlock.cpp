#include "cMasterBlock.h"



cMasterBlock::cMasterBlock()
{

}


cMasterBlock::~cMasterBlock()
{
}

void cMasterBlock::printBlock()
{
		HANDLE handleOut = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo(handleOut, &info);
		COORD coord; //block coordination
		coord.X = coordinateX;
		coord.Y = coordinateY;
		std::string pBlock = "x";  //-----
		DWORD d = 0;
		WriteConsoleOutputCharacter(handleOut, pBlock.c_str(), pBlock.size(), coord, &d);
		SetConsoleCursorPosition(handleOut, coord);
}


