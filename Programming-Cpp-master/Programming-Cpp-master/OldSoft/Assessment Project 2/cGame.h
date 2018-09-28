#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "conio.h"
#include "cMasterBlock.h"
#include "cSquareBlock.h"
#include "cFileManager.h"
#include "cTimer.h"
#include "cClearScreen.h"
#include "cMenu.h"
#include <stdlib.h>
#include <time.h>



class cGame
{
public:
	cGame();
	~cGame();

	void block(int);
	int	randomNumber();

	void keyPress();
	bool keyPressed;
	bool abuseBlocker;


	void game();

	int loopInt = { 0 };

private:
	int score			= { 0 };
	int lives			= { 3 };
	int randomNum		= { 0 };
	double timeRestriction = { 1 }; // default value for timers
};

