#include "Game.h"


Game::Game(){

	m_Window = nullptr;
	m_Renderer = nullptr;

	// start up
	SDL_Init(SDL_INIT_VIDEO);



	// create the window
	m_Window = SDL_CreateWindow(
		"My First window", // title
		250,	//initial x pos
		50,		// initial y pos
		640,	// width in pixels
		480,	// height in pixels
		0		//window behaviour flags
	);

	if (!m_Window)
	{
		printf("WINDOW initialisation failed %s\n", SDL_GetError());
		printf("Press any key to continue\n");
		getchar();
		return;
	}

	// now create renderer
	m_Renderer = SDL_CreateRenderer(
		m_Window,	// link the renderer to our window
		-1,			//index rendering driver
		0			//renderer behaviour flags
	);

		if (!m_Renderer)
		{
			printf("RENDERER initialisation failed %s\n", SDL_GetError());
			printf("Press any key to continue\n");
			getchar();
			return;
		}

	//Clean up
	//Don't forget we destroy in the reverse order

	if (m_Renderer)
	{
		SDL_DestroyRenderer(m_Renderer);
	}

	if (m_Window) {
		SDL_DestroyWindow(m_Window);
	}
}

Game::~Game()
{
}

void Game::SetDisplayColour(void)
{
	if (m_Renderer)
	{
		//Render in a red color
		int result = SDL_SetRenderDrawColor(
			m_Renderer, // our target renderer
			255, //r
			0, //g
			0, //b
			255 // alpha
		);

		//wipe the display color to set color
		SDL_RenderClear(m_Renderer);

		//Show what we've drawn
		SDL_RenderPresent(m_Renderer);

		//Pause for 5 sec
		SDL_Delay(5000); //Delay takes millisecs
	}
}
