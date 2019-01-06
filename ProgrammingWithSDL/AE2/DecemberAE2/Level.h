#include <iostream>
#include <string>
#include <vector>
#include <SDL.h>
#include "CCollisionRectangle.h"

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

#pragma once
class Level
{

private:
	SDL_Surface* m_pbitmapSurface;
	SDL_Texture* m_pbitmapTexture;
	SDL_Renderer*	m_pRenderer;

	std::vector<std::string> m_gridLayout;
	int m_x, m_y;

	int	m_blockWidth;
	int	m_blockHeight;

public:
	Level(SDL_Renderer* renderer);

	//Debug
	void getData();

	int getHeight();
	int getWidth();
	
	void tileBlock(int r, int g, int b);
	void levelRenderer();

	std::vector<std::string> GetTiles()
	{
		return	m_gridLayout;
	}

	void getTile(int,int);

	CCollisionRectangle* GetTileRect(int x, int y)
	{
		return new CCollisionRectangle(x * m_blockWidth, y * m_blockHeight, m_blockWidth, m_blockHeight);
	}

	void levelData(SDL_Renderer* renderer);
	~Level();
};

