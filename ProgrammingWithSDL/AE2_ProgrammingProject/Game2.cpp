#include "Game2.h"
#include "input.h"



Game2::Game2()
{
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
	}

	
}


Game2::~Game2()
{
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

void Game2::SetDisplayColour(int R, int G, int B, int A)
{
	if (m_Renderer)
	{
		//Render in a red color
		int result = SDL_SetRenderDrawColor(
			m_Renderer, // our target renderer
			R, //r
			G, //g
			B, //b
			A // alpha
		);

		//wipe the display color to set color
		SDL_RenderClear(m_Renderer);

		//Show what we've drawn
		SDL_RenderPresent(m_Renderer);

		//Pause for 5 sec
		SDL_Delay(100); //Delay takes millisecs
	}
}
