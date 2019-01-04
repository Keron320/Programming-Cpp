#pragma once
#include <string>
#include <SDL.h>
#include "SDL_ttf.h"
#include <stdio.h>
#include "Bitmap.h"
#include "Level.h"

//-----------------------------------------------------------------------------
//
// Copyright (C) Keron Sepp 2018-2019
// 
//
//
//
//
// DESCRIPTION:
//
//-----------------------------------------------------------------------------

//struct SDL_Window;
//struct SDL_Renderer;
//class Bitmap;
//class Level;

class Game2
{
private:
	//SDL Stuff
	SDL_Window		* m_Window;
	SDL_Renderer	*m_Renderer;
	SDL_Event		event;

	bool			m_running;

	//Bitmaps
	Bitmap* m_monster;
	Bitmap* m_monsterTrans;
	Bitmap* m_monsterTransKeyed;
	Bitmap* m_enemyTransKeyed; 
	//Menu buttons
	Bitmap* m_menuBar1;
	Bitmap* m_menuBar2;
	Bitmap* m_menuBar3;
	Bitmap* m_menuBarHL1;
	Bitmap* m_menuBarHL2;
	Bitmap* m_menuBarHL3;
	Bitmap* m_Panel;

	//Level
	Level*	m_level;


	//Font stuff
	TTF_Font*	m_pSmallFont; // 04-02
	TTF_Font*	m_pBigFont;	// 04-02

	void UpdateText(std::string msg, int x, int y, TTF_Font* font, SDL_Color colour);

public:
	Game2();
	~Game2();

	bool walkDir = false;
	bool playerDead = false;
	bool playerWin = false;

	int xposition = 100;
	int yposition = 100;

	//static callback method
	static Uint32 TimerCallback(Uint32 interval, void* gameObjectIn);

	void CreateTimerEvent();

	void Update(void);
	// Function to only display the main menu
	void displayMainMenu(int menuOption);

	void SetDisplayColour(int R, int G, int B, int A);

	//Bitmap control
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	//FPS stuff
	bool		m_updateLogic;
	bool		m_renderFrame;
	int			m_consecutiveLogicUpdates;
	const int	m_maxConsecutiveLogicUpdates = 10;
	SDL_TimerID	m_gameTimerID;

	//enums
	enum GameEvent { GE_TIMER, NUM_GAME_EVENTS };

	const int	FRAMES_PER_SECOND = 60;
	const int	MILLISECS_PER_FRAME = 1000 / FRAMES_PER_SECOND; //(Rounded down);
	SDL_TimerID	gametimer = SDL_AddTimer(MILLISECS_PER_FRAME, &Game2::TimerCallback, this);

	void CheckEvents();

	

};

