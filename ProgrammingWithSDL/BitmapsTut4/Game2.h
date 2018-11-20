#pragma once

#include <SDL.h>
#include <stdio.h>
class Game2
{
private :
	SDL_Window* m_Window;
	SDL_Renderer *m_Renderer;
public:
	Game2();
	~Game2();

	void SetDisplayColour(int R, int G, int B, int A);
};

