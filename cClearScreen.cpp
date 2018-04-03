#include "cClearScreen.h"
#include "cMenu.h"



cClearScreen::cClearScreen()
{
}


cClearScreen::~cClearScreen()
{
}

// Reference: Keron_Sepp_DAC416_AE1_Project
void cClearScreen::wipeScreen()
{
		HANDLE handleOut;
		CONSOLE_SCREEN_BUFFER_INFO conbufferinfo;
		DWORD count;
		DWORD cellCount;
		COORD coords = { 0, 0 };
		handleOut = GetStdHandle(STD_OUTPUT_HANDLE);
		if (handleOut == INVALID_HANDLE_VALUE) return;
		if (!GetConsoleScreenBufferInfo(handleOut, &conbufferinfo)) return;
		cellCount = conbufferinfo.dwSize.X *conbufferinfo.dwSize.Y;
		if (!FillConsoleOutputCharacter(
			handleOut,
			(TCHAR) ' ',
			cellCount,
			coords,     //Starts filling from 0,0
			&count      //functions require a variable to store how many characters were written 
		)) return;
		//Moves cursor back to 0,0 every time
		SetConsoleCursorPosition(handleOut, coords);
		  //Clears entire screen

}
