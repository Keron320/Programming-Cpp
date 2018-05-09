#include "cSquareBlock.h"



cSquareBlock::cSquareBlock()
{
}


cSquareBlock::~cSquareBlock()
{
}

void cSquareBlock::printSquare(int coordinateX, int coordinateY)
{
		HANDLE handleOut = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo(handleOut, &info);
		COORD coord; //block coordination
		COORD coord2; //block coordination
		COORD coord3; //block coordination
		COORD coord4; //block coordination
		COORD zeroCursor; //block coordination
		// ZeroCursor (is located at 0,0)
		zeroCursor.X = 0;
		zeroCursor.Y = 0;
		// Top left
		coord.X = coordinateX;
		coord.Y = coordinateY;
		// Top right
		coord2.X = coordinateX + 1;
		coord2.Y = coordinateY;
		// Bottom left
		coord3.X = coordinateX;
		coord3.Y = coordinateY + 1;
		// Bottom right
		coord4.X = coordinateX + 1;
		coord4.Y = coordinateY + 1;
		std::string pBlock = "x";  //-----
		DWORD d = 0;
		DWORD d2 = 0;
		DWORD d3 = 0;
		DWORD d4 = 0;

		
		WriteConsoleOutputCharacter(handleOut, pBlock.c_str(), pBlock.size(), coord, &d);
		WriteConsoleOutputCharacter(handleOut, pBlock.c_str(), pBlock.size(), coord2, &d2);
		WriteConsoleOutputCharacter(handleOut, pBlock.c_str(), pBlock.size(), coord3, &d3);
		WriteConsoleOutputCharacter(handleOut, pBlock.c_str(), pBlock.size(), coord4, &d4);
		SetConsoleCursorPosition(handleOut, zeroCursor);
}


void cSquareBlock::eraseSquare(int coordinateX, int coordinateY)
{
	HANDLE handleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handleOut, &info);
	COORD coord; //block coordination
	COORD coord2; //block coordination
	COORD coord3; //block coordination
	COORD coord4; //block coordination
	COORD zeroCursor; //block coordination
					  // ZeroCursor (is located at 0,0)
	zeroCursor.X = 0;
	zeroCursor.Y = 0;
	// Top left
	coord.X = coordinateX;
	coord.Y = coordinateY;
	// Top right
	coord2.X = coordinateX + 1;
	coord2.Y = coordinateY;
	// Bottom left
	coord3.X = coordinateX;
	coord3.Y = coordinateY + 1;
	// Bottom right
	coord4.X = coordinateX + 1;
	coord4.Y = coordinateY + 1;
	std::string pBlock = " ";  //-----
	DWORD d = 0;
	DWORD d2 = 0;
	DWORD d3 = 0;
	DWORD d4 = 0;


	WriteConsoleOutputCharacter(handleOut, pBlock.c_str(), pBlock.size(), coord, &d);
	WriteConsoleOutputCharacter(handleOut, pBlock.c_str(), pBlock.size(), coord2, &d2);
	WriteConsoleOutputCharacter(handleOut, pBlock.c_str(), pBlock.size(), coord3, &d3);
	WriteConsoleOutputCharacter(handleOut, pBlock.c_str(), pBlock.size(), coord4, &d4);
	SetConsoleCursorPosition(handleOut, zeroCursor);
}













void cSquareBlock::printBar(int coordinateX, int coordinateY)
{
	HANDLE handleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handleOut, &info);
	COORD coord;  //block coordination
	COORD coord2; //block coordination
	COORD coord3; //block coordination
	COORD coord4; //block coordination
	COORD zeroCursor; //block coordination
					  // ZeroCursor (is located at 0,0)
	zeroCursor.X = 0;
	zeroCursor.Y = 0;
	// Top left
	coord.X = coordinateX + 5;
	coord.Y = coordinateY + 5;
	// Top right
	coord2.X = coordinateX + 6;
	coord2.Y = coordinateY + 5;
	// Bottom left
	coord3.X = coordinateX + 5;
	coord3.Y = coordinateY + 6;
	// Bottom right
	coord4.X = coordinateX + 6;
	coord4.Y = coordinateY + 6;
	std::string pBlock = "Y";  //-----
	DWORD d = 0;
	DWORD d2 = 0;
	DWORD d3 = 0;
	DWORD d4 = 0;


	WriteConsoleOutputCharacter(handleOut, pBlock.c_str(), pBlock.size(), coord, &d);
	WriteConsoleOutputCharacter(handleOut, pBlock.c_str(), pBlock.size(), coord2, &d2);
	WriteConsoleOutputCharacter(handleOut, pBlock.c_str(), pBlock.size(), coord3, &d3);
	WriteConsoleOutputCharacter(handleOut, pBlock.c_str(), pBlock.size(), coord4, &d4);
	SetConsoleCursorPosition(handleOut, zeroCursor);
}
