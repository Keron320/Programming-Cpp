#include "SDL.h"
#undef main

#include "Game2.h"
#include "Level.h"
#include "input.h"
#include <conio.h>

int main()
{
	int R = 0, G = 0, B = 0;

	// false on start
	bool maxReached = false;
	Game2* game  = new Game2(); //Create a new game object
	Input* input = new Input();
	Level* level = new Level();

	//Default menu option
	int selectedOption = 2;

	if (game && input)
	{
		//declare and init variables used for colour of the background
		Uint8 r = 51, g = 171, b = 249, a = 255;
		game->SetDisplayColour(r, g, b, a); // set our colour
		game->CreateTimerEvent();
		//check keys pressed to update variable
		//Main menu loop
		bool exitGame = false;
		bool menu = true;

		while (exitGame != true)
		{
			input->Update();

			if (input->KeyIsPressed(KEY_RIGHT))
			{
				game->moveRight();
			}
			if (input->KeyIsPressed(KEY_LEFT))
			{
				game->moveLeft();
			}
			if (input->KeyIsPressed(KEY_DOWN))
			{
				game->moveDown();
				selectedOption = selectedOption + 1;
				if (selectedOption > 3)
				{
					selectedOption = 1;
				}
			}
			if (input->KeyIsPressed(KEY_UP))
			{
				game->moveUp();
				selectedOption = selectedOption - 1;
				if (selectedOption < 1)
				{
					selectedOption = 3;
				}
			}
			//go back to menu and highlight new game when escape is pressed
			if (input->KeyIsPressed(KEY_ESCAPE))
			{
				selectedOption = 1;
			}

			// Action depending what option player selects
			if (input->KeyIsPressed(KEY_RETURN))
			{
				switch (selectedOption)
				{
					case 1: {
						// Exit the loop to start the game loop
						menu = false;
						break;
					}
					case 2: {
						selectedOption = 4;
						break;
					}
					case 3: {
						SDL_Quit();
						return 0; 
						break;
					}
				}
			}
			//update the game			
			game->displayMainMenu(selectedOption);

			if (menu == false){
				game->SetDisplayColour(128, 128, b, a); // set our colour
				while (!input->KeyIsPressed(KEY_ESCAPE))
				{
					input->Update();
					if (input->KeyIsPressed(KEY_RIGHT))
					{
						game->moveRight();
					}
					if (input->KeyIsPressed(KEY_LEFT))
					{
						game->moveLeft();
					}
					if (input->KeyIsPressed(KEY_DOWN))
					{
						game->moveDown();
					}
					if (input->KeyIsPressed(KEY_UP))
					{
						game->moveUp();
					}

					//go back to menu and highlight new game when escape is pressed

					game->Update();
					// write some code here about the game
				}
			}
		}
	}


	return 0;						//Exit nicely
}