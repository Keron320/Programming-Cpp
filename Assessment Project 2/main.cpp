#include <iostream>
#include <string>
#include <fstream>
#include "cTester.h"
#include "cMenu.h"
#include "conio.h"
#include "cClearScreen.h"
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

	time.start();
	while(1){
	
		cout << time.getElapsed_sec() << endl;
	}

	//testing.test("SQUARE 20 10 49 s");
	

	mainMenu.masterMenu();


	//End message
	std::cout << "\nYou reached the end of the program, sorry...\nPress any key to exit";
	_getch();
	return 0;
}