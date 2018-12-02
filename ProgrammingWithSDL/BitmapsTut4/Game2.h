#pragma once

#include <SDL.h>
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

