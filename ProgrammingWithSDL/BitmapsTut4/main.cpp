#include "SDL.h"
#undef main

#include "Game2.h"
#include "Level.h"
#include "input.h"

int main()
{
	bool onOff = true;
	int R = 0, G = 0, B = 0;

	// false on start
	bool maxReached = false;
	Game2* game = new Game2(); //Create a new game object
	Input* input = new Input();
	Level* level = new Level();

	//Default menu option
	int selectedOption = 1;


	if (game && input)
	{
		//declare and init variables used for colour of the background
		Uint8 r = 51, g = 171, b = 249, a = 255;
		game->SetDisplayColour(r, g, b, a); // set our colour
		game->CreateTimerEvent();
		//check keys pressed to update variable
		//Main menu loop
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
			

			if (selectedOption == 3)
				SDL_QUIT;
			//switch (selectedOption)
			//{
			//case 3:
			//	if (input->KeyIsPressed(KEY_RETURN))
			//		SDL_QUIT;
			//}

			//update the game			
			game->displayMainMenu(selectedOption);
		}

		game->SetDisplayColour(r, g, b, a); // set our colour
		while (!input->KeyIsPressed(KEY_ESCAPE))
		{
			// write some code here about the game
		}
	}


	return 0;						//Exit nicely
}