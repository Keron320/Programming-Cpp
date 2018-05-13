#include "cGame.h"



cGame::cGame()
{
}


cGame::~cGame()
{
}

	cClearScreen screenClear;
	cFileManager reader;
	cMenu menu;
	
	int cGame::randomNumber() 
	{
		
		//Random number from 1 to as many lines test.txt has
		randomNum = rand() % reader.lineCounter() + 1;
		// int loopInt = randomnumber means to only read the random line and get the data
		loopInt = randomNum;

		return loopInt;
	}

void cGame::block(int loopInt) {

	cMasterBlock block;
	cSquareBlock square;

	// Reads the line to test if it is working
	// reader.readLine(reader.lineCounter());
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

	// Returns the colour of given line
	reader.getColour(reader.lineCounter(), loopInt);
	// Passes the returned value to return function
	block.returnC(reader.getColour(reader.lineCounter(), loopInt));

	// Returns the column of given line
	reader.getCharacter(reader.lineCounter(), loopInt);
	// Passes the returned value to return function
	block.returnCharacter(reader.getCharacter(reader.lineCounter(), loopInt));


	// Did not use swtich because it seemed too complicated to get it to work... and the readabilty is fine because of the block names
	if (reader.getName(reader.lineCounter(), loopInt) == "SQUARE") {
		square.printSquare(block.coordinateX, block.coordinateY, block.colour, block.blockName, block.gameColours);
	}
	else if (reader.getName(reader.lineCounter(), loopInt) == "BAR") {
		square.printBar(block.coordinateX, block.coordinateY, block.colour, block.blockName, block.gameColours);
	}
	else if (reader.getName(reader.lineCounter(), loopInt) == "T") {
		square.printT(block.coordinateX, block.coordinateY, block.colour, "k", block.gameColours); // "k" is because the test file has no character and I failed to apply colours properly.
	}
	else if (reader.getName(reader.lineCounter(), loopInt) == "L") {
		square.printL(block.coordinateX, block.coordinateY, block.colour, block.blockName, block.gameColours);
	}
	else if (reader.getName(reader.lineCounter(), loopInt) == "//") { // Custom Block
		square.printSquare(38, 36, 14, "Q", block.gameColours);
	}
	else if (reader.getName(reader.lineCounter(), loopInt) == "TEXT") { // Custom Block
		square.printBar(24, 25, 42, "P", block.gameColours);
	}

	else {
		square.printL(4, 15, 12, "E", block.gameColours); // Custom block for else
	}


	keyPress();
	
	
}

void cGame::keyPress()
{
	char keyPress = 0;
	// Registers keyboard hit
	if (_kbhit())
	{
		// _getch() appoints _kbhit to keyPress variable
		keyPress = _getch();
		// If 'ENTER' is pressed
		if (keyPress == 13 && abuseBlocker == false)
		{	
			keyPressed = true;
			abuseBlocker = true;
			score += 100;
			timeRestriction -= 0.01; // Decrease all timers by 0.01 each time player gets it right to increase challenge
			screenClear.wipeScreen();
		}
		// Display this message if no correct keys is pressed
		else if (keyPress == 13 && abuseBlocker == true)
		{
			keyPressed = false;
			lives -= 1;
			abuseBlocker = true;

		}
		else
		{
			std::cout << "you pressed an invalid key                     " << std::endl;
		}
	}
}


void cGame::game()
{

	cTimer timer;
	cTimer timerSpawn;
	
	while (lives != 0) 
	{
		// Starts the timer
		timer.start();
		
		// After 2 seconds of waiting executes this
		if (timer.getElapsed_sec() >= timeRestriction)
		{	
			int rnumb = randomNumber();	
			timer.stop();
			timer.reset();			//Resets the timer back to 0;
			//new timer starts
			keyPressed = false;		//resets keypress to false
			abuseBlocker = true;	// prevents player from spamming the enter key or holding it down
			timerSpawn.start();
			// Display block
			std::cout <<"Score: " <<score <<"               "<< "Lives: "<< lives << std::endl;
			while (timerSpawn.getElapsed_sec() <= timeRestriction && keyPressed == false)
			{
				abuseBlocker = false;
				block(rnumb);				// Creates the block
				if (keyPressed == true) {
					keyPressed = true;
				}
			}
			while (timerSpawn.getElapsed_sec() > timeRestriction || keyPressed == true)
			{
					screenClear.wipeScreen();		// Clears the screen
					// If enter is not pressed but time runs out, lose a life
					if (timerSpawn.getElapsed_sec() > timeRestriction)
					{
						lives -= 1;					// lose a life every time you miss the block;
					}
					timerSpawn.reset();				// Resets the timer back to 0		
					keyPressed = false;				// Set keypress to false no matter what happens
			}		
			timerSpawn.reset();
		}
		else {
			timer.stop();
		}
		
	}
	std::cout << "out of lives" << std::endl;
	std::cout << "Congratulations your final score is : " << score << std::endl;
	std::cout << "Press any key 2 times to continue to main menu!";

	lives = 3;
	score = 0;
	timer.reset();
	timerSpawn.reset();
	_getch();
	_getch();
	screenClear.wipeScreen();
	menu.printMenu();

}
