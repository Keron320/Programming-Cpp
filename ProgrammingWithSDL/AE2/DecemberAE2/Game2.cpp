#include "Game2.h"
#include "input.h"
#include <stdio.h>
#include "Bitmap.h"
#include "Creature.h"
#include "Level.h"

//-----------------------------------------------------------------------------
//
// Copyright (C) Keron Sepp 2018-2019
// 
//
//
//
//
// DESCRIPTION:  Game window and overal setup
//
//-----------------------------------------------------------------------------

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


	//	// start up
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS);
	TTF_Init();

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

	m_level = new Level(m_Renderer); //I moved this here

									 // New Stuff Bitmaps
									 //m_monster = new Bitmap(m_Renderer, "assets/monster.bmp", 50, 50); // Remove from screen for now
									 //m_monsterTrans = new Bitmap(m_Renderer, "assets/monsterTrans.bmp", 50, 100); // Remove from screen for now
	m_monsterTransKeyed = new Bitmap(m_Renderer, "assets/monsterTransKeyed.bmp", 100, 328, CCollisionRectangle(100, 328, 30, 30), m_level, true); // 04-01
	m_enemyTransKeyed = new Bitmap(m_Renderer, "assets/monsterTransKeyed.bmp", 300, 328, CCollisionRectangle(300, 328, 30, 30), m_level, true); // 04-01

																																				// Menubars
	m_menuBarHL1 = new Bitmap(m_Renderer, "assets/MenuBarSelected.bmp", 100, 100, CCollisionRectangle(), m_level, true);
	m_menuBarHL2 = new Bitmap(m_Renderer, "assets/MenuBarSelected.bmp", 100, 200, CCollisionRectangle(), m_level, true);
	m_menuBarHL3 = new Bitmap(m_Renderer, "assets/MenuBarSelected.bmp", 100, 300, CCollisionRectangle(), m_level, true);
	m_menuBar1 = new Bitmap(m_Renderer, "assets/MenuBar.bmp", 100, 100, CCollisionRectangle(), m_level, true);
	m_menuBar2 = new Bitmap(m_Renderer, "assets/MenuBar.bmp", 100, 200, CCollisionRectangle(), m_level, true);
	m_menuBar3 = new Bitmap(m_Renderer, "assets/MenuBar.bmp", 100, 300, CCollisionRectangle(), m_level, true);
	m_Panel = new Bitmap(m_Renderer, "assets/Panel.bmp", 100, 50, CCollisionRectangle(), m_level, true);
	//m_level init was here

	// start up
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS);

	//read in the font
	m_pSmallFont = TTF_OpenFont("assets/DejaVuSans.ttf", 15); // 04-02
	m_pBigFont = TTF_OpenFont("assets/DejaVuSans.ttf", 50); // 04-02

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

	// Cleaning up after menu boxes
	if (m_menuBar1)
		delete m_menuBar1;
	if (m_menuBar2)
		delete m_menuBar2;
	if (m_menuBar3)
		delete m_menuBar3;

	if (m_menuBarHL1)
		delete m_menuBarHL1;
	if (m_menuBarHL2)
		delete m_menuBarHL2;
	if (m_menuBarHL3)
		delete m_menuBarHL3;
	if (m_Panel)
		delete m_Panel;
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

	if (m_monsterTransKeyed->isColliding(m_enemyTransKeyed->GetCollisionRect()))
	{
		std::cout << "player touches enemy" << std::endl;
		playerDead = true;
	}

	//Get the positions of each element
	for (size_t y = 0; y < m_level->GetTiles().size(); y++)
	{
		for (int x = 0; x < m_level->GetTiles()[y].length(); x++)
		{				
			CCollisionRectangle* tileRect = m_level->GetTileRect(x, y);
			if (m_level->GetTiles()[y][x] == 'W')
			{
				// Player hits the wall
				if (m_monsterTransKeyed->isColliding(*tileRect))
				{
					std::cout << "Monster hit walls" << std::endl;
				}


				if (m_enemyTransKeyed->isColliding(*tileRect) && walkDir == false)
				{
					
					std::cout << "enemy touch wallsTRUE";
					walkDir = true;
				}

				else if (m_enemyTransKeyed->isColliding(*tileRect) && walkDir == true)
				{

					std::cout << "enemy touch wallsFALSE";
					walkDir = false;
				}
			}


			else if (m_level->GetTiles()[y][x] == 'F')
			{
			//// Player hits the floor
				if (m_monsterTransKeyed->isColliding(*tileRect))
				{
					m_monsterTransKeyed->moveUp();
					std::cout << "Player hit floor" << std::endl;
				}
			}

			else if (m_level->GetTiles()[y][x] == 'E')
			{
				// Player hits the exit
				if (m_monsterTransKeyed->isColliding(*tileRect))
				{
					playerWin = true;
				}


				if (m_enemyTransKeyed->isColliding(*tileRect) && walkDir == false)
				{

					std::cout << "enemy touch wallsTRUE";
					walkDir = true;
				}

				else if (m_enemyTransKeyed->isColliding(*tileRect) && walkDir == true)
				{

					std::cout << "enemy touch wallsFALSE";
					walkDir = false;
				}
			}
		}
	}

	if (walkDir == false)
	{
		m_enemyTransKeyed->enemyMovePatternLeft();
	}

	else if (walkDir == true)
	{
		m_enemyTransKeyed->enemyMovePatternRight();
	}


	SDL_SetRenderDrawColor(m_Renderer, 86, 171, 255, 255);

	//wipe the display to the current set colours
	SDL_RenderClear(m_Renderer);

	//show our bitmaps
	//Draw takes argument to scale x and y

	if (playerDead != true)
	{
	m_monsterTransKeyed->draw(2, 2); // Stop drawing the player if playerdead is true
	}

	else {
		std::string myString = "You died!";
		UpdateText(myString, 10, 20, m_pBigFont, { 255,255,255 });

		std::string myString2 = "Press Escape to return";
		UpdateText(myString2, 10, 70, m_pBigFont, { 255,255,255 });

		std::string myString3 = "to menu menu.";
		UpdateText(myString3, 10, 120, m_pBigFont, { 255,255,255 });

	}

	if (playerWin != true)
	{
		m_enemyTransKeyed->draw(2, 2); // Stop drawing the enemy if playerWin is true
	}

	else {
		std::string myString = "You Won!!";
		UpdateText(myString, 10, 20, m_pBigFont, { 255,255,255 });

		std::string myString2 = "Press Escape to return";
		UpdateText(myString2, 10, 70, m_pBigFont, { 255,255,255 });

		std::string myString3 = "to menu menu.";
		UpdateText(myString3, 10, 120, m_pBigFont, { 255,255,255 });

	}





	//UpdateText("Small Red", 50, 10, m_pSmallFont, { 255,0,0 });
	//UpdateText("Small Blue", 50, 40, m_pSmallFont, { 0,0,255 });

	//char char_array[] = "Big White";
	//UpdateText(char_array, 50, 140, m_pBigFont, { 255,255,255 });



	//Display level
	m_level->levelRenderer();

	////showDrawing
	SDL_RenderPresent(m_Renderer);


}

void Game2::displayMainMenu(int menuOption)
{

	CheckEvents();

	//wipe the display to the current set colour
	SDL_RenderClear(m_Renderer);

	//show our bitmaps
	//Draw takes argument to scale x and y
	//Draw the menubar box
	switch (menuOption)
	{
	case 1:
		m_menuBarHL1->draw(1, 1);
		m_menuBar2->draw(1, 1);
		m_menuBar3->draw(1, 1);
		// Display text on the empty menubars
		UpdateText("Exit", 150, 300, m_pBigFont, { 255,255,255 });
		UpdateText("Credits", 150, 200, m_pBigFont, { 255,255,255 });
		UpdateText("New game", 150, 100, m_pBigFont, { 255,255,255 });
		break;

	case 2:
		m_menuBar1->draw(1, 1);
		m_menuBarHL2->draw(1, 1);
		m_menuBar3->draw(1, 1);
		// Display text on the empty menubars
		UpdateText("Exit", 150, 300, m_pBigFont, { 255,255,255 });
		UpdateText("Credits", 150, 200, m_pBigFont, { 255,255,255 });
		UpdateText("New game", 150, 100, m_pBigFont, { 255,255,255 });
		break;

	case 3:
		m_menuBar1->draw(1, 1);
		m_menuBar2->draw(1, 1);
		m_menuBarHL3->draw(1, 1);
		// Display text on the empty menubars
		UpdateText("Exit", 150, 300, m_pBigFont, { 255,255,255 });
		UpdateText("Credits", 150, 200, m_pBigFont, { 255,255,255 });
		UpdateText("New game", 150, 100, m_pBigFont, { 255,255,255 });
		break;
	case 4:
		m_Panel->draw(1, 1);
		UpdateText("Game demo by: ", 110, 100, m_pBigFont, { 255,255,255 });
		UpdateText("Keron Sepp", 175, 200, m_pBigFont, { 255,255,255 });
		break;
	}


	//showDrawing
	//SDL_Delay(100); // Delay for 16 millisec
	SDL_RenderPresent(m_Renderer);
}

void Game2::SetDisplayColour(int R, int		G, int B, int A)
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
		//SDL_Delay(100); //Delay takes millisecs
	}
}

//Movement
void Game2::moveLeft()
{
	m_monsterTransKeyed->moveLeft();

}

void Game2::moveRight()
{
	m_monsterTransKeyed->moveRight();

}

void Game2::moveUp()
{
	m_monsterTransKeyed->moveUp();
}

void Game2::moveDown()
{
	m_monsterTransKeyed->moveDown();
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
