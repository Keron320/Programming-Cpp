#include <iostream>
#include <string>
#include <fstream>
#include "conio.h"
#include "cTester.h"
#include "cMenu.h"
#include "cMasterBlock.h"
#include "cSquareBlock.h"
#include "cFileManager.h"
#include "cGame.h"

// Author:Keron Sepp, Year:2017, Project:DAC416 Assessment 1, Viewed Date: 01.04.2018, Available from: github.com/Keron320/Programming-Cpp
#include "cClearScreen.h"


// Author:Dave Cobb, Year:2017, Project:DAC416 Assessment 2, Viewed Date: 01.04.2018, Available from: Solent University.
#include "cTimer.h"

using namespace std;




//// function for keyboard inputs
//void keyboardInput(char keyPress = 0) {
//	// Press ESC to stop the loop
//	while (keyPress != 27) {
//		// Registers keyboard hit
//		if (_kbhit())
//		{
//			// _getch() appoints _kbhit to keyPress variable
//			keyPress = _getch();
//			// If 'ENTER' is pressed
//			if (keyPress == 13)
//			{
//				std::cout << "Hello friend";
//			}
//			// Display this message if no correct keys is pressed
//			else
//			{
//				cout << "you pressed an invalid key" << endl;
//			}
//		}
//	}
//}


const std::string TestFileName{ "test.txt" };

int main()
{
	cTester tester;
	cFileManager reader;
	cClearScreen console;
	cGame gameplay;
	cMasterBlock block;
	cSquareBlock square;
	cMenu menu;


	//while (reader.fileReader())
	//{
	//	// construct a shape from a file
	//	cMasterBlock shape { reader.getNextLine() };
	//	//clear the screen
	//	console.wipeScreen();
	//	//display shape just created
	//	shape.printBlock();
	//	//test the shape
	//	//bool success = tester.test(shape.getRawText());
	//}
	//// std::cout << std::boolalpha << success;
	////_getch();


	// menu.masterMenu();

	// TEST GAME STARTS HERE

/* TESTING FOR READING ALL THE LINES

	for (int loopInt = 1; loopInt < reader.lineCounter(); loopInt++) {

		// Reads the line to test if it is working
		//	reader.readLine(reader.lineCounter());
		// Returns the name of the line(BLOCK or BAR or so on)
		reader.getName(reader.lineCounter(), loopInt);

		// Returns the row of given line
		reader.getRow(reader.lineCounter(), loopInt);
		// Passes the returned value to return function
		block.returnX(reader.getRow(reader.lineCounter(), loopInt));

		// Returns the column of given line
		reader.getColumn(reader.lineCounter(), loopInt);
		// Passes the returned value to return function
		block.returnY(reader.getRow(reader.lineCounter(), loopInt));


		//if (reader.getName(reader.lineCounter(), loopInt) == "SQUARE") {
		//	square.printSquare(block.coordinateX, block.coordinateY);
		//}


		std::cout << reader.getName(reader.lineCounter(), loopInt) << std::endl;


		//else if (reader.getName(reader.lineCounter(), loopInt) == "BAR") {
		//	square.printBar(block.coordinateX, block.coordinateY);
		//}
	}

*/

//	// Reading random lines
//#include <stdlib.h>
//#include <time.h>
//
//	int randomNumber = 0;
//	srand(time(NULL));
//	//Random number from 1 to as many lines test.txt has
//	randomNumber = rand() % reader.lineCounter() + 1;
//	// int loopInt = randomnumber means to only read the random line and get the data
//	int loopInt = randomNumber;
//
//		// Reads the line to test if it is working
//		//	reader.readLine(reader.lineCounter());
//		// Returns the name of the line(BLOCK or BAR or so on)
//		reader.getName(reader.lineCounter(), loopInt);
//
//		// Returns the row of given line
//		reader.getRow(reader.lineCounter(), loopInt);
//		// Passes the returned value to return function
//		block.returnX(reader.getRow(reader.lineCounter(), loopInt));
//
//		// Returns the column of given line
//		reader.getColumn(reader.lineCounter(), loopInt);
//		// Passes the returned value to return function
//		block.returnY(reader.getRow(reader.lineCounter(), loopInt));
//
//
//		if (reader.getName(reader.lineCounter(), loopInt) == "SQUARE") {
//			square.printSquare(block.coordinateX, block.coordinateY);
//		}
//
//
//		std::cout << reader.getName(reader.lineCounter(), loopInt) << std::endl;
//
//
		//else if (reader.getName(reader.lineCounter(), loopInt) == "BAR") {
		//	square.printBar(block.coordinateX, block.coordinateY);
		//}


		// To prevent the for loop being an endless loop

	menu.masterMenu();


	_getch();
	return 0;
	
}

//for (int loopInt = 1; loopInt < reader.lineCounter(); loopInt++) {
//
//	 Reads the line to test if it is working
//	 reader.readLine(reader.lineCounter());
//	 Returns the name of the line (BLOCK or BAR or so on)
//	reader.getName(reader.lineCounter(), loopInt);
//
//	// Returns the row of given line
//	reader.getRow(reader.lineCounter(), loopInt);
//	// Passes the returned value to return function
//	block.returnX(reader.getRow(reader.lineCounter(), loopInt));
//
//	// Returns the column of given line
//	reader.getColumn(reader.lineCounter(), loopInt);
//	// Passes the returned value to return function
//	block.returnY(reader.getRow(reader.lineCounter(), loopInt));
//
//
//	if (reader.getName(reader.lineCounter(), loopInt) == "SQUARE") {
//		square.printSquare(block.coordinateX, block.coordinateY);
//	}
//
//	else if (reader.getName(reader.lineCounter(), loopInt) == "BAR") {
//		square.printBar(block.coordinateX, block.coordinateY);
//	}
//
//
//}
//
//
//
//}