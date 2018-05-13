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
#include <ctime>

// Author:Keron Sepp, Year:2017, Project:DAC416 Assessment 1, Viewed Date: 01.04.2018, Available from: github.com/Keron320/Programming-Cpp
#include "cClearScreen.h"


// Author:Dave Cobb, Year:2017, Project:DAC416 Assessment 2, Viewed Date: 01.04.2018, Available from: Solent University.
#include "cTimer.h"

using namespace std;

const std::string TestFileName{ "test.txt" };

int main()
{
	cTester tester;
	cFileManager reader;
	cClearScreen console;
	cGame gameplay;
	cMasterBlock block;
	cMasterBlock testBlock;
	cSquareBlock square;
	cMenu menu;
	srand((unsigned int)time(NULL));


	// TEST GAME STARTS HERE
	for (int loopInt = 1; loopInt < reader.lineCounter(); loopInt++) {

		// Returns the name of the line(BLOCK or BAR or so on)
		reader.getName(reader.lineCounter(), loopInt);


		// Returns the row of given line
		reader.getRow(reader.lineCounter(), loopInt);
		// Passes the returned value to return function
		testBlock.returnX(reader.getRow(reader.lineCounter(), loopInt));

		// Returns the column of given line
		reader.getColumn(reader.lineCounter(), loopInt);
		// Passes the returned value to return function
		testBlock.returnY(reader.getRow(reader.lineCounter(), loopInt));

		// Returns the colour of given line
		reader.getColour(reader.lineCounter(), loopInt);
		// Passes the returned value to return function
		testBlock.returnC(reader.getColour(reader.lineCounter(), loopInt));

		// Returns the character of given line
		reader.getCharacter(reader.lineCounter(), loopInt);
		// Passes the returned value to return function
		testBlock.returnCharacter(reader.getCharacter(reader.lineCounter(), loopInt));

		
		//Uncomment gameColours to test colors.
		//testBlock.gameColours = true;  
		if (reader.getName(reader.lineCounter(), loopInt) == "SQUARE") {
			square.printSquare(testBlock.coordinateX, testBlock.coordinateY, testBlock.colour, testBlock.blockName, testBlock.gameColours);
		}
		else if ((reader.getName(reader.lineCounter(), loopInt) == "SQUARE") && (reader.getCharacter(reader.lineCounter(), loopInt) == "1")) {
			loopInt += 1;
		}

		else if (reader.getName(reader.lineCounter(), loopInt) == "BAR") {
			square.printBar(testBlock.coordinateX, testBlock.coordinateY, testBlock.colour, testBlock.blockName, testBlock.gameColours);
		}
		else if (reader.getName(reader.lineCounter(), loopInt) == "T") {
			square.printT(testBlock.coordinateX, testBlock.coordinateY, testBlock.colour, testBlock.blockName, testBlock.gameColours);
		}

		if (reader.getName(reader.lineCounter(), loopInt) == "//") { // Custom Block
			loopInt++;
		}

		else if (reader.getName(reader.lineCounter(), loopInt) == "L") {
			square.printL(testBlock.coordinateX, testBlock.coordinateY, testBlock.colour, testBlock.blockName, testBlock.gameColours);
		}
		else if (reader.getName(reader.lineCounter(), loopInt) == "TEXT") {
			square.printTEXT(testBlock.coordinateX, testBlock.coordinateY, testBlock.colour, testBlock.blockName, testBlock.gameColours);
		}

		// Testing using the provided testing class ( Not pretty )
		for (int loopInt = 1; loopInt < reader.lineCounter(); loopInt++) {
			std::cout << "Testing completed if you see 1, then everything is all right!\n";
			if (loopInt = 1){
			bool test("SQUARE 20 10 49 s");
			std::cout << test;
			}
			if (loopInt = 2) {
				bool test("L 9 30 77 L");
				std::cout << test;
			}
			if (loopInt = 3) {
				bool test("T 15 22 42 ");
				std::cout << test;
			}
			if (loopInt = 4) {
				bool test("BAR 30 7 95 78");
				std::cout << test;
			}
			if (loopInt = 5) {
				bool test("TEXT 34 8 32 High Score");
				std::cout << test;
			}
			if (loopInt = 6) {
				bool test("L 20 20 07 @");
				std::cout << test;
			}
			if (loopInt = 7) {
				bool test("// overlapped SQUARE blocks");
				std::cout << test;
			}
			if (loopInt = 8) {
				bool test("SQUARE 30 12 26 1 skips this line");
				std::cout << test;
			}
			if (loopInt = 9) {
				bool test("SQUARE 30 10 63 2");
				std::cout << test;
			}
			if (loopInt = 10) {
				bool test("TEXT 34 8 32 This is the last line");
				std::cout << test;
			}
		}
		
		// remove comment from _getch() to test everyting with visuals!
		//_getch();
		// Clears the screen
		console.wipeScreen();
	}

	// Game starts
	menu.masterMenu();


	_getch();
	return 0;
	
}