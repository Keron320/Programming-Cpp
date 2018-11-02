#include "SDL.h"
#undef main

#include "Game.h"

int main(int argc, char* argv[])
{
	Game* game = new Game(); //Create a new game object

	if (game)
	{
		game->SetDisplayColour();	//set and show our coloured display;
		delete game;				// Clean up
		game = nullptr;				
	}

	return 0;						//Exit nicely

}