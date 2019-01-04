#include "SDL.h"
#include "SDL_render.h"
#include <string>

#pragma once
class CCollisionRectangle
{
public:
	CCollisionRectangle();
	CCollisionRectangle(int x, int y, int w, int h );
	~CCollisionRectangle();


	void SetRectangle(int x, int y, int w, int h);
	SDL_Rect GetRectangle()
	{
		return CollisionRect;
	}


private:
	SDL_Rect CollisionRect;
};

