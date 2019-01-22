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
	int m_xMAX;
	int m_yMAX; // for jumping and stuff


	int scalerX;
	int scalerY;

public:

	Bitmap();
	Bitmap(SDL_Renderer* renderer, std::string fileName, int xpos, int ypos, CCollisionRectangle passed_CollisionRect, Level* passed_level, bool useTransparency = false);
	~Bitmap();

	void draw(int m_scaleX, int m_scaleY);
	void setPos(int,int);
	//Bitmap control
	void moveLeft(int speed);
	void moveRight(int speed);
	void moveUp(int speed);
	void moveDown(int speed);

	
	void isFalling();

	int getPosX();
	int getPosY();
	int getPosXMax(int x);
	int getPosYMax(int y);

	// Enemy "A.I" 
	void enemyMovePatternLeft();
	void enemyMovePatternRight();

	// Level stuff
	int levelXpos();
	int levelYpos();


	//Collision stuff
	bool isColliding(CCollisionRectangle theCollider);

	CCollisionRectangle GetCollisionRect()
	{
		return CollisionRect;
	}

};

