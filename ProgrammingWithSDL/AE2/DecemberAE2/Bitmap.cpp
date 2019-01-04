#include "Bitmap.h"
#include "SDL.h"
#include "SDL_render.h"
#include "Level.h"
#include "Game2.h"
#include <string>

using namespace std;

//-----------------------------------------------------------------------------
//
// Copyright (C) Keron Sepp 2018-2019
// 
//
//
//
//
// DESCRIPTION:  Loading bitmaps
//
//-----------------------------------------------------------------------------



Bitmap::Bitmap()
{
}

Bitmap::Bitmap(SDL_Renderer* renderer, string fileName, int xpos, int ypos, CCollisionRectangle passed_CollisionRect, Level* passed_level, bool useTransparency)
{

	level = passed_level;
	CollisionRect = passed_CollisionRect;
	// Store renderer for future confiq and drawing
	m_pRenderer = renderer;

	// Create bitmap surface
	m_pbitmapSurface = SDL_LoadBMP(fileName.c_str());
	if (!m_pbitmapSurface)
	{
		//Bitmap not loaded? Output the error
		printf("SURFACE for bitmap '%s' not loaded! \n", fileName.c_str());
		printf("%s\n", SDL_GetError());
	}

	else
	{
		//If we are to use transparency, going to assume
		//the colour is magenta ( r = 255, g = 0, b = 255 );
		if (useTransparency)
		{
			Uint32 colourKey = SDL_MapRGB(m_pbitmapSurface->format, 255, 0, 255);
			SDL_SetColorKey(m_pbitmapSurface, SDL_TRUE, colourKey);
		}

		//Create the texture
		m_pbitmapTexture = SDL_CreateTextureFromSurface(m_pRenderer, m_pbitmapSurface);
		if (!m_pbitmapSurface)
		{
			//Bitmap not loaded? Output the error
			printf("SURFACE for bitmap '%s' not loaded! \n", fileName.c_str());
			printf("%s\n", SDL_GetError());
		}
	}

	//store the position values
	m_x = xpos;
	m_y = ypos;
}


Bitmap::~Bitmap()
{
	if (m_pbitmapTexture)
		SDL_DestroyTexture(m_pbitmapTexture);
	if (m_pbitmapSurface)
		SDL_FreeSurface(m_pbitmapSurface);
}

void Bitmap::draw(int m_scaleX, int m_scaleY)
{
	// To scale the bitmap
	scalerX = m_scaleX;
	scalerY = m_scaleY;
	//Render the bitmap at the x/y
	if (m_pbitmapTexture)
	{

		SDL_Rect destRect = { m_x, m_y, m_pbitmapSurface->w*scalerX, m_pbitmapSurface->h*scalerY };
		SDL_RenderCopy(m_pRenderer, m_pbitmapTexture, NULL, &destRect);

	} 

}

//Set the starting position of the sprite
void Bitmap::setPos(int x, int y)
{
	m_x = x;
	m_y = y;
}

//Move bitmap Left
void Bitmap::moveLeft()
{
	m_x = m_x - 15;
	CollisionRect.SetRectangle(m_x, m_y, CollisionRect.GetRectangle().w, CollisionRect.GetRectangle().h);
}

//Move bitmap Right
void Bitmap::moveRight()
{
	m_x = m_x + 15;
	CollisionRect.SetRectangle(m_x, m_y, CollisionRect.GetRectangle().w, CollisionRect.GetRectangle().h);
}
//Move bitmap Down
void Bitmap::moveDown()
{
	m_y = m_y + 15;
	CollisionRect.SetRectangle(m_x, m_y, CollisionRect.GetRectangle().w, CollisionRect.GetRectangle().h);


}

void Bitmap::enemyMovePatternLeft()
{
	m_x = m_x - 1;
	CollisionRect.SetRectangle(m_x, m_y, CollisionRect.GetRectangle().w, CollisionRect.GetRectangle().h);
}

void Bitmap::enemyMovePatternRight()
{
	m_x = m_x + 1;
	CollisionRect.SetRectangle(m_x, m_y, CollisionRect.GetRectangle().w, CollisionRect.GetRectangle().h);
}

//Move bitmap Up
void Bitmap::moveUp()
{
	m_y = m_y - 15;
	CollisionRect.SetRectangle(m_x, m_y, CollisionRect.GetRectangle().w, CollisionRect.GetRectangle().h);
}
int Bitmap::levelXpos()
{
	return m_x;

}

int Bitmap::levelYpos()
{
	return m_y;
}



bool Bitmap::isColliding(CCollisionRectangle theCollider)
{
	std::cout << CollisionRect.GetRectangle().x << "," << CollisionRect.GetRectangle().y << "," << CollisionRect.GetRectangle().w << "," << CollisionRect.GetRectangle().h << endl;
	std::cout << theCollider.GetRectangle().x << "," << theCollider.GetRectangle().y << "," << theCollider.GetRectangle().w << "," << theCollider.GetRectangle().h << endl;

	return !(CollisionRect.GetRectangle().x + CollisionRect.GetRectangle().w < theCollider.GetRectangle().x ||
		CollisionRect.GetRectangle().y + CollisionRect.GetRectangle().h < theCollider.GetRectangle().y || //I added ()'s
		CollisionRect.GetRectangle().x > theCollider.GetRectangle().x + theCollider.GetRectangle().w ||
		CollisionRect.GetRectangle().y > theCollider.GetRectangle().y + theCollider.GetRectangle().h); //I added ()'s
}