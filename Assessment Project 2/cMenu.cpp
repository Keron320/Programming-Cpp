#include "cMenu.h"
#include "cClearScreen.h"


cMenu::cMenu()
{
}


cMenu::~cMenu()
{
}

// class to wipe screen anywhere inside cMenu.cpp
cClearScreen screenWipe;

// Switch cases when "choice" changes.
void cMenu::menuSelection()
{
	enum userChoice { blank = 0, game, instructions, hiscore ,exit,};
	switch (choice) {
	// Default choice is set to 0 - no data will be proccessed.
	case blank:if(choice == 0)
		break;
	case game:if (choice == 1)
	{
		std::cout << "New game!" << std::endl;
	}
		break;
	case instructions:if (choice == 2)
	{
		// uses cClearScreen class to clear screen
		screenWipe.wipeScreen();
		// uses highScore() function to display score
		instructionMenu();
	}
		break;
	case hiscore:if (choice == 3)
	{
		// uses cClearScreen class to clear screen
		screenWipe.wipeScreen();
		// uses highScore() function to display score
		highScore();
	}
		break;
	case exit:if (choice == 4)
	{
		std::cout << "Press any key to exit the game" << std::endl;
	}
		break;
	// Default message if user inputs incorrect value
	default:
		std::cout << "Something went wrong... try some other buttons!" << std::endl;
	}
}

void cMenu::highScore()
{
	std::ifstream scoreFile("score.txt");
	std::string line;
	if (scoreFile.is_open())
	{
		while (getline(scoreFile, line))
		{
			std::cout << line << '\n';
		}
		scoreFile.close();
		//Function to return back to menu with a message
		anyKey();
	}
	else {
		std::cout << "\nNo scores" << std::endl;
	}
}

// Displays the main menu
void cMenu::printMenu()
{
	std::cout << "(1)New game" << std::endl;
	std::cout << "(2)Instructions" << std::endl;
	std::cout << "(3)High scores" << std::endl;
	std::cout << "(4)Exit game" << std::endl;
}

int cMenu::menuChoice()
{
	std::cin >> choice;
	return choice;
}

void cMenu::masterMenu()
{
	printMenu();
	while (choice != 4) {
		menuChoice();
		menuSelection();
	}	
}

void cMenu::anyKey()
{
	std::cout << "Press any key to return main-menu" << std::endl;
	//Get user response to return back to menu
	_getch();
	//Clear screen and print main-menu.
	screenWipe.wipeScreen();
	printMenu();
}

void cMenu::instructionMenu()
{
	std::ifstream scoreFile("instructions.txt");
	std::string line;
	if (scoreFile.is_open())
	{
		while (getline(scoreFile, line))
		{
			std::cout << line << '\n';
		}
		scoreFile.close();
		//Function to return back to menu with a message
		anyKey();
	}
	else {
		std::cout << "\nNo data" << std::endl;
	}
}

