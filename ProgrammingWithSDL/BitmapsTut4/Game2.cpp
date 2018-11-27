#include "Game2.h"
#include "input.h"
#include <stdio.h>
#include "Bitmap.h"



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


	// New Stuff Bitmaps
	m_monster = new Bitmap(m_Renderer, "assets/monster.bmp", 100, 100); // 04-01
	m_monsterTrans = new Bitmap(m_Renderer, "assets/monsterTrans.bmp", 200, 100); // 04-01
	m_monsterTransKeyed = new Bitmap(m_Renderer, "assets/monsterTransKeyed.bmp", 300, 100, true); // 04-01



	
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

	//Destroy the bitmaps
	
	if (m_monsterTransKeyed)
		delete m_monsterTransKeyed;

	if (m_monsterTrans)
		delete m_monsterTrans;

	if (m_monster)
		delete m_monster;
}


void Game2::Update(void)
{
	//CheckEvents();

	//wipe the display to the current set colour
	SDL_RenderClear(m_Renderer);
	
	//show our bitmaps
	m_monster->draw();
	m_monsterTrans->draw();
	m_monsterTransKeyed->draw();

	//showDrawing

	SDL_RenderPresent(m_Renderer);

	//pause for 1/60th sec
	SDL_Delay(16); // Delay for 16 millisec


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
