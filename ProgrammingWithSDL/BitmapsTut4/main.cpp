#include "SDL.h"
#undef main

#include "Game2.h"
#include "input.h"

int main()
{
	bool onOff = true;
	int R = 0, G = 0, B = 0;

	// false on start
	bool maxReached = false;
	Game2* game = new Game2(); //Create a new game object
	Input* input = new Input();

	if (game && input)
	{
		//declare and init variables used for colour of the background
		Uint8 r = 0, g = 0, b = 0, a = 255;

		//check keys pressed to update variable
		while (!input->KeyIsPressed(KEY_ESCAPE))
		{
			//Update when getting input
			input->Update();
			
			//incrase r
			if (input->KeyIsPressed(KEY_R))
			{
				if (++r > 255) r = 0;
				
			}

			//incrase g
			if (input->KeyIsPressed(KEY_G))
			{
				if (++g > 255) g = 0;
			}

			//incrase b
			if (input->KeyIsPressed(KEY_B))
			{
				if (++b > 255) b = 0;
			}

			game->SetDisplayColour(r, g, b, a); // set our colour
			game->Update();

		}

	}



	//if (game)
	//{
	//	while(onOff == true)
	//	{
	//		if (R != 255 && maxReached == false || G != 255 && maxReached == false || B != 255 && maxReached == false) {
	//		R = R + 1;
	//		G = G + 2;
	//		B = B + 3;
	//
	//		game->SetDisplayColour(R, G, B);	//set and show our coloured display;

	//			if (R == 255 && G == 255 && B == 255) 
	//			{
	//				maxReached = true;
	//			}
	//		}

	//		else if (maxReached == true) {
	//			R = R - 1;
	//			G = G - 2;
	//			B = B - 3;
	//			if (R == 0 && G == 0 && B == 0) maxReached = false;
	//			game->SetDisplayColour(R, G, B);	//set and show our coloured display;
	//		}

	//		//game->SetDisplayColour(R, G, B);	//set and show our coloured display;
	//	
	//	}

	//	delete game;				// Clean up
	//	game = nullptr;				
	//	
	//}

	return 0;						//Exit nicely

}