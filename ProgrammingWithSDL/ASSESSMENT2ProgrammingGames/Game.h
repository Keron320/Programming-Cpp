#ifndef GAME_H
#define GAME_H
#include <SDL.h>
#include <stdio.h>

//#pragma once

class Game
{
private:

	SDL_Window* m_Window;
	SDL_Renderer *m_Renderer;

public:
	Game();
	~Game();

	void SetDisplayColour(void);


}

#endif // GAME_H





