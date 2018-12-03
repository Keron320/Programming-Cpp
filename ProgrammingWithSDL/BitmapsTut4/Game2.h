#pragma once
#include <string>
#include <SDL.h>
#include "SDL_ttf.h"
#include <stdio.h>


struct SDL_Window;
struct SDL_Renderer;
class Bitmap; //04-01

class Game2
{
private :
	//SDL Stuff
	SDL_Window		*m_Window;
	SDL_Renderer	*m_Renderer;
	bool			m_running;
	
	//Bitmaps
	Bitmap* m_monster; // 04-01
	Bitmap* m_monsterTrans; // 04-01
	Bitmap* m_monsterTransKeyed; // 04-01


	//Font stuff
	TTF_Font*	m_pSmallFont; // 04-02
	TTF_Font*	m_pBigFont;	// 04-02

	void UpdateText(std::string msg, int x, int y, TTF_Font* font, SDL_Color colour);

public:
	Game2();
	~Game2();

	void Update(void);

	void SetDisplayColour(int R, int G, int B, int A);

	// To obtain the bitmap position and to set one
	void getPos();
	void setPos();

	//Bitmap control
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

};

