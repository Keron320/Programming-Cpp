#include "cGame.h"



cGame::cGame()
{
}


cGame::~cGame()
{
}

	cClearScreen screenClear;


void cGame::block() {

	cMasterBlock block;
	cSquareBlock square;
	cFileManager reader;


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


		if (reader.getName(reader.lineCounter(), loopInt) == "SQUARE") {
			square.printSquare(block.coordinateX, block.coordinateY);
		}

		else if (reader.getName(reader.lineCounter(), loopInt) == "BAR") {
			square.printBar(block.coordinateX, block.coordinateY);
		}

		// To do stuff
		keyPress();
	}
}


void cGame::keyPress()
{
	char keyPress = 0;
		// Press ESC to stop the loop
	//	while (keyPress != 27) {
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
					screenClear.wipeScreen();
				}
				// Display this message if no correct keys is pressed
				else if (keyPress == 13 && abuseBlocker == true)
				{
					keyPressed = false;
					abuseBlocker = true;
					lives -= 1;
				}
				else
				{
					std::cout << "you pressed an invalid key" << std::endl;
				}
			}
		//}
	}


void cGame::game()
{

	cTimer timer;
	cTimer timerSpawn;


	// Counts all the lines
	// getElapsed_ms
	while (lives != 0) 
	{
		// Starts the timer
		timer.start();
		int i = 1;
		// After 2 seconds of waiting executes this
		if (timer.getElapsed_sec() >= i)
		{
			timer.stop();
			timer.reset();		//Resets the timer back to 0;
			//new timer starts
			keyPressed = false;	 //resets keypress to false
			abuseBlocker = true; // prevents player from spamming the enter key or holding it down
			timerSpawn.start();	//
			
			// Display block
			while (timerSpawn.getElapsed_sec() <= i && keyPressed == false)
			{
				abuseBlocker = false;
				block();
				if (keyPressed == true) {
					keyPressed = true;

				}
				std::cout << timerSpawn.getElapsed_sec() << std::endl;
			}

			while (timerSpawn.getElapsed_sec() > i || keyPressed == true)
			{

					screenClear.wipeScreen();		// Clears the screen
					// If enter is not pressed but time runs out, lose a life
					if (timerSpawn.getElapsed_sec() > i)
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





}
