#include "cSquareBlock.h"



cSquareBlock::cSquareBlock()
{
}


cSquareBlock::~cSquareBlock()
{
}

void cSquareBlock::printSquare(int coordinateX, int coordinateY, int colour, std::string character, bool gameColours)
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
		std::string pBlock = character;
		DWORD d = 0;

		SetConsoleCursorPosition(handleOut, coord);
		SetConsoleCursorPosition(handleOut, coord2);
		SetConsoleCursorPosition(handleOut, coord3);
		SetConsoleCursorPosition(handleOut, coord4);
	

		// For coloured blocks and game
		int txtColour = colour;
		if (txtColour > 0 && gameColours == true)
		{
			WORD attribute;

			attribute = SetConsoleTextAttribute(handleOut, FOREGROUND_GREEN | FOREGROUND_BLUE);

			WriteConsoleOutputAttribute(handleOut, &attribute, 1, coord, &d);
			WriteConsoleOutputAttribute(handleOut, &attribute, 1, coord2, &d);
			WriteConsoleOutputAttribute(handleOut, &attribute, 1, coord3, &d);
			WriteConsoleOutputAttribute(handleOut, &attribute, 1, coord4, &d);
		}
		// Writes characters on set locations
		WriteConsoleOutputCharacter(handleOut, pBlock.c_str(), pBlock.size(), coord, &d);
		WriteConsoleOutputCharacter(handleOut, pBlock.c_str(), pBlock.size(), coord2, &d);
		WriteConsoleOutputCharacter(handleOut, pBlock.c_str(), pBlock.size(), coord3, &d);
		WriteConsoleOutputCharacter(handleOut, pBlock.c_str(), pBlock.size(), coord4, &d);



		SetConsoleCursorPosition(handleOut, zeroCursor);


}

void cSquareBlock::printBar(int coordinateX, int coordinateY, int colour, std::string character, bool gameColours)
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
	coord3.X = coordinateX + 2;
	coord3.Y = coordinateY;
	// Bottom right
	coord4.X = coordinateX + 3;
	coord4.Y = coordinateY;
	std::string pBlock = character;
	DWORD d = 0;

	SetConsoleCursorPosition(handleOut, coord);
	SetConsoleCursorPosition(handleOut, coord2);
	SetConsoleCursorPosition(handleOut, coord3);
	SetConsoleCursorPosition(handleOut, coord4);


	// For coloured blocks and game
	int txtColour = colour;
	if (txtColour > 0 && gameColours == true)
	{
		WORD attribute;

		if (txtColour = 1) { attribute = FOREGROUND_INTENSITY | FOREGROUND_RED; };
		if (txtColour = 2) { attribute = FOREGROUND_INTENSITY | FOREGROUND_BLUE; };
		if (txtColour = 49) { attribute = FOREGROUND_INTENSITY | FOREGROUND_GREEN; };

		WriteConsoleOutputAttribute(handleOut, &attribute, 1, coord, &d);
		WriteConsoleOutputAttribute(handleOut, &attribute, 1, coord2, &d);
		WriteConsoleOutputAttribute(handleOut, &attribute, 1, coord3, &d);
		WriteConsoleOutputAttribute(handleOut, &attribute, 1, coord4, &d);
	}
	// Writes characters on set locations
	WriteConsoleOutputCharacter(handleOut, pBlock.c_str(), pBlock.size(), coord, &d);
	WriteConsoleOutputCharacter(handleOut, pBlock.c_str(), pBlock.size(), coord2, &d);
	WriteConsoleOutputCharacter(handleOut, pBlock.c_str(), pBlock.size(), coord3, &d);
	WriteConsoleOutputCharacter(handleOut, pBlock.c_str(), pBlock.size(), coord4, &d);



	SetConsoleCursorPosition(handleOut, zeroCursor);


}


void cSquareBlock::printT(int coordinateX, int coordinateY, int colour, std::string character, bool gameColours)
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
	
	coord.X = coordinateX + 1;
	coord.Y = coordinateY;
	
	coord2.X = coordinateX + 1;
	coord2.Y = coordinateY;
	
	coord3.X = coordinateX + -1;
	coord3.Y = coordinateY;
	
	coord4.X = coordinateX;
	coord4.Y = coordinateY - 1;
	std::string pBlock = character;
	DWORD d = 0;

	SetConsoleCursorPosition(handleOut, coord);
	SetConsoleCursorPosition(handleOut, coord2);
	SetConsoleCursorPosition(handleOut, coord3);
	SetConsoleCursorPosition(handleOut, coord4);


	// For coloured blocks and game
	int txtColour = colour;
	if (txtColour > 0 && gameColours == true)
	{
		WORD attribute;

		attribute = FOREGROUND_RED | FOREGROUND_BLUE;

		WriteConsoleOutputAttribute(handleOut, &attribute, 1, coord, &d);
		WriteConsoleOutputAttribute(handleOut, &attribute, 1, coord2, &d);
		WriteConsoleOutputAttribute(handleOut, &attribute, 1, coord3, &d);
		WriteConsoleOutputAttribute(handleOut, &attribute, 1, coord4, &d);
	}
	// Writes characters on set locations
	WriteConsoleOutputCharacter(handleOut, pBlock.c_str(), pBlock.size(), coord, &d);
	WriteConsoleOutputCharacter(handleOut, pBlock.c_str(), pBlock.size(), coord2, &d);
	WriteConsoleOutputCharacter(handleOut, pBlock.c_str(), pBlock.size(), coord3, &d);
	WriteConsoleOutputCharacter(handleOut, pBlock.c_str(), pBlock.size(), coord4, &d);



	SetConsoleCursorPosition(handleOut, zeroCursor);


}


void cSquareBlock::printL(int coordinateX, int coordinateY, int colour, std::string character, bool gameColours)
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

	coord.X = coordinateX;
	coord.Y = coordinateY;

	coord2.X = coordinateX + 1;
	coord2.Y = coordinateY;

	coord3.X = coordinateX;
	coord3.Y = coordinateY + 1;

	coord4.X = coordinateX;
	coord4.Y = coordinateY + 2;
	std::string pBlock = character;
	DWORD d = 0;

	SetConsoleCursorPosition(handleOut, coord);
	SetConsoleCursorPosition(handleOut, coord2);
	SetConsoleCursorPosition(handleOut, coord3);
	SetConsoleCursorPosition(handleOut, coord4);


	// For coloured blocks and game
	int txtColour = colour;
	if (txtColour > 0 && gameColours == true)
	{
		WORD attribute;

		attribute = FOREGROUND_GREEN | FOREGROUND_BLUE;

		WriteConsoleOutputAttribute(handleOut, &attribute, 1, coord, &d);
		WriteConsoleOutputAttribute(handleOut, &attribute, 1, coord2, &d);
		WriteConsoleOutputAttribute(handleOut, &attribute, 1, coord3, &d);
		WriteConsoleOutputAttribute(handleOut, &attribute, 1, coord4, &d);
	}
	// Writes characters on set locations
	WriteConsoleOutputCharacter(handleOut, pBlock.c_str(), pBlock.size(), coord, &d);
	WriteConsoleOutputCharacter(handleOut, pBlock.c_str(), pBlock.size(), coord2, &d);
	WriteConsoleOutputCharacter(handleOut, pBlock.c_str(), pBlock.size(), coord3, &d);
	WriteConsoleOutputCharacter(handleOut, pBlock.c_str(), pBlock.size(), coord4, &d);



	SetConsoleCursorPosition(handleOut, zeroCursor);


}

void cSquareBlock::printTEXT(int coordinateX, int coordinateY, int colour, std::string character, bool gameColours)
{
	HANDLE handleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handleOut, &info);
	COORD coord; //block coordination
	COORD zeroCursor; //block coordination
					  // ZeroCursor (is located at 0,0)
	zeroCursor.X = 0;
	zeroCursor.Y = 0;

	coord.X = coordinateX;
	coord.Y = coordinateY;

	std::string pBlock = character;
	DWORD d = 0;

	SetConsoleCursorPosition(handleOut, coord);

	// For coloured blocks and game
	int txtColour = colour;
	if (txtColour > 0 && gameColours == true)
	{
		WORD attribute;

		attribute = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,

		WriteConsoleOutputAttribute(handleOut, &attribute, 1 , coord, &d);
	}
	// Writes characters on set locations
	WriteConsoleOutputCharacter(handleOut, pBlock.c_str(), pBlock.size(), coord, &d);
	


	SetConsoleCursorPosition(handleOut, zeroCursor);


}

