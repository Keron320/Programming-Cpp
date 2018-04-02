#include <iostream>
#include <string>
#include <fstream>
#include "conio.h"
#include "cTester.h"
#include "cMenu.h"
#include "cMasterBlock.h"

// Author:Keron Sepp, Year:2017, Project:DAC416 Assessment 1, Viewed Date: 01.04.2018, Available from: github.com/Keron320/Programming-Cpp
#include "cClearScreen.h"


// Author:Dave Cobb, Year:2017, Project:DAC416 Assessment 2, Viewed Date: 01.04.2018, Available from: Solent University.
#include "cTimer.h"

using namespace std;



/*
// function for keyboard inputs
void keyboardInput(char keyPress = 0) {
	// Press ESC to stop the loop
	while (keyPress != 27) {
		// Registers keyboard hit
		if (_kbhit())
		{
			// _getch() appoints _kbhit to keyPress variable
			keyPress = _getch();
			// If 'ENTER' is pressed
			if (keyPress == 13)
			{
				std::cout << "Hello friend";
			}
			// Display this message if no correct keys is pressed
			else
			{
				cout << "you pressed an invalid key" << endl;
			}
		}
	}
}
*/

int main()
{
	cTester testing;
	cClearScreen clearScreen;
	cMenu mainMenu;
	cTimer time;
	cMasterBlock masterBlock;
	
	masterBlock.printBlock();



	//testing.test("SQUARE 20 10 49 s");
	//mainMenu.masterMenu();


	//End message
	//std::cout << "\nYou reached the end of the program, sorry...\nPress any key to exit";
	_getch();
	return 0;
}