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


class cGame
{
public:
	cGame();
	~cGame();

	void block();
	void keyPress();
	bool keyPressed;
	bool abuseBlocker;

	void game();
private:
	int score { 0 };
	int lives { 3 };
};

