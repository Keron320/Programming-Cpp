#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#include "cGame.h"


class cMenu
{
public:
	cMenu();
	~cMenu();

	//Prints the first menu
	void printMenu();
	//Selects part of menu based on menuChoice
	void menuSelection();
	//Prints high-score
	void highScore();
	//Allows player to chance "choice" value to access different parts of menu	
	int	 menuChoice();
	//MasterMenu connects all parts together.
	void masterMenu();
	//Default message to press any key, returns back to menu
	void anyKey();
	//Instructions part of the game
	void instructionMenu();
	std::string playerName();
private:
	//default menu selection set to 0
	int choice = { 0 };
};

