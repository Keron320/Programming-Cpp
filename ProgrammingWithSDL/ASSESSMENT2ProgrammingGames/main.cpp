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

	if (game && input)
	{
		//declare and init variables used for colour of the background
		Uint8 r = 128, g = 128, b = 128, a = 255;
		game->SetDisplayColour(r, g, b, a); // set our colour
		game->CreateTimerEvent();
		//check keys pressed to update variable
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

			//update the game			
			game->Update();
		}
	}

	return 0;						//Exit nicely
}