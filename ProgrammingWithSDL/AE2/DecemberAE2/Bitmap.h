#pragma once
#include <string>
#include "CCollisionRectangle.h"
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

//struct SDL_Surface;
//struct SDL_Texture;
//struct SDL_Renderer;



class Bitmap
{
private:
	Level* level;
	CCollisionRectangle CollisionRect;

	SDL_Surface *	m_pbitmapSurface;
	SDL_Texture*	m_pbitmapTexture;

	SDL_Renderer*	m_pRenderer;


	int m_x, m_y;
	int scalerX;
	int scalerY;

public:

	Bitmap();
	Bitmap(SDL_Renderer* renderer, std::string fileName, int xpos, int ypos, CCollisionRectangle passed_CollisionRect, Level* passed_level, bool useTransparency = false);
	~Bitmap();

	void draw(int m_scaleX, int m_scaleY);
	void setPos(int,int);
	//Bitmap control
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	void enemyMovePatternLeft();
	void enemyMovePatternRight();

	int levelXpos();
	int levelYpos();

	bool isColliding(CCollisionRectangle theCollider);

	CCollisionRectangle GetCollisionRect()
	{
		return CollisionRect;
	}

};

