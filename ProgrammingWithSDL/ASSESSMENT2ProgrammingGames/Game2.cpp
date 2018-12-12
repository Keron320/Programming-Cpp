#include "Game2.h"
#include "input.h"
#include <stdio.h>
#include "Bitmap.h"



void Game2::UpdateText(std::string msg, int x, int y, TTF_Font * font, SDL_Color colour)
{
	SDL_Surface* surface = nullptr;
	SDL_Texture* texture = nullptr;

	int texW = 0;
	int texH = 0;

	//SDL_Color color { 0,0,0 };

	//char msg[100]
	//sprintf_s(msg, "Checks: %d", m_checkTally);

	surface = TTF_RenderText_Solid(font, msg.c_str(), colour);
	if (!surface)
	{
		//Surface not loaded? Output error
		printf("SURFACE for font not loaded! \n");
		printf("%s\n", SDL_GetError());
	}

	else
	{
		texture = SDL_CreateTextureFromSurface(m_Renderer, surface);
		if (!texture)
		{
			//Surface not loaded? Output error
			printf("SURFACE for font not loaded! \n");
			printf("%s\n", SDL_GetError());
		}
		else
		{
			SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
			SDL_Rect textRect = { x, y, texW, texH };

			SDL_RenderCopy(m_Renderer, texture, NULL, &textRect);
		}
	}

	if (texture)
		SDL_DestroyTexture(texture);

	if (surface)
		SDL_FreeSurface(surface);
}

Game2::Game2()
{
	m_Window = nullptr;
	m_Renderer = nullptr;
	   	 
	// start up
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init(); //04-02

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
	
	//read in the font
	m_pSmallFont = TTF_OpenFont("assets/DejaVuSans.ttf", 15); // 04-02
	m_pBigFont = TTF_OpenFont("assets/DejaVuSans.ttf", 50); // 04-02


	//start up
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);


	//FPS things

	m_updateLogic = true;
	m_renderFrame = true;
	m_consecutiveLogicUpdates = 0;
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


Uint32 Game2::TimerCallback(Uint32 interval, void * gameObjectIn)
{
	if (gameObjectIn)
	{
		Game2* gameObject = static_cast<Game2*>(gameObjectIn);
		gameObject->CreateTimerEvent();
	}

	// Returning 0 instead of interval will cancel the timer
	return interval;
}

void Game2::CreateTimerEvent()
{
	SDL_Event event;
	SDL_UserEvent userEvent;

	//set up userEvent with default data;
	userEvent.type = SDL_USEREVENT;
	userEvent.data1 = NULL;
	userEvent.data2 = NULL;

	//this is a TIMER event
	userEvent.code = GE_TIMER;

	//Create the event
	event.type = SDL_USEREVENT;
	event.user = userEvent;

	//Push the event
	SDL_PushEvent(&event);
}

void Game2::Update(void)
{
	CheckEvents();

	//wipe the display to the current set colour
	SDL_RenderClear(m_Renderer);
	
	//show our bitmaps
	m_monster->draw();
	m_monsterTrans->draw();
	m_monsterTransKeyed->draw();

	UpdateText("Small Red", 50, 10, m_pSmallFont, { 255,0,0 });
	UpdateText("Small Blue", 50, 40, m_pSmallFont, { 0,0,255 });

	char char_array[] = "Big White";
	UpdateText(char_array, 50, 140, m_pBigFont, { 255,255,255 });

	std::string myString = "Big Green";
	UpdateText(myString, 50, 70, m_pBigFont, { 0,255,0 });

	//testString += to_string(testNumber);
	//UpdateText(testString, 50, 210, m_pBigFont, { 255,255,255 });


	
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

void Game2::getPos()
{
}

void Game2::setPos()
{
	//m_monster->setPos();
}

//Movement
void Game2::moveLeft()
{
	m_monster->moveLeft();
}

void Game2::moveRight()
{
	m_monster->moveRight();
}

void Game2::moveUp()
{
	m_monster->moveUp();
}

void Game2::moveDown()
{
	m_monster->moveDown();
}

void Game2::CheckEvents()
{
	//poll the event queue
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_USEREVENT:
		{
			if (event.user.code == GE_TIMER)
			{
				// we have a ping!
				// if the logic taking too long ensures frame is rendered occasionally and input is responsive
				// this essentially ignores logic updates if there are a lot of consecutive ones
				if (++m_consecutiveLogicUpdates < m_maxConsecutiveLogicUpdates)
				{
					m_updateLogic = true;
				}

				//only render frame	if no events left to proccess
				if (SDL_PeepEvents(NULL, 1, SDL_PEEKEVENT, SDL_USEREVENT, SDL_USEREVENT) == 0)
				{
					m_renderFrame = true;
					m_consecutiveLogicUpdates = 0;
				}
			}
		}
		}
	}
}

