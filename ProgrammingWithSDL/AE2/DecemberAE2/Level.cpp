#include "Level.h"

//-----------------------------------------------------------------------------
//
// Copyright (C) Keron Sepp 2018-2019
// 
//
//
//
//
// DESCRIPTION:  Level data, wall data, etc.
//
//-----------------------------------------------------------------------------


Level::Level(SDL_Renderer* renderer)
{
	//Get LevelData
	levelData(renderer);
}

void Level::getData()
{
	std::cout << m_x << ":X value" << std::endl;
	std::cout << m_y << ":Y value" <<std::endl;
	std::cout << m_blockWidth << ":BW value"<< std::endl;
	std::cout << m_blockHeight << ":BH value"<< std::endl;
}

int Level::getHeight()
{
	//Get the number of rows in m_gridLayout
	return m_gridLayout.size();
}

int Level::getWidth()
{
	//Get the number of columns in m_gridLayout
	// Basically get the first rows string lenght because all columns have same amount of chars.
	return m_gridLayout[0].length();
}

void Level::tileBlock(int r, int g, int b)
{
	
	SDL_Rect rect = { m_x, m_y, m_blockWidth, m_blockHeight };
	CCollisionRectangle(m_x, m_y, m_blockWidth, m_blockHeight);

	SDL_SetRenderDrawColor(m_pRenderer, r, g, b, 255);
	SDL_RenderFillRect(m_pRenderer, &rect);
}


void Level::levelRenderer()
{
	for (int i = 0; i < getHeight(); i++)
	{
		//Go through levels width
		for (int j = 0; j < getWidth(); j++)
		{
			//Calculating the block position
			m_x = (j * m_blockWidth);
			m_y = (i * m_blockHeight);
			//Drawing the blocks depending where W is
			if (m_gridLayout[i][j] == 'W')
			{
				//Block attributes, color and so on
				tileBlock(128, 128, 128);
			}
			if (m_gridLayout[i][j] == 'F')
			{
				//Block attributes, color and so on
				tileBlock(139, 69, 19);
			}
			if (m_gridLayout[i][j] == 'E')
			{
				//Block attributes, color and so on
				tileBlock(200, 150, 79);
			}
			//std::cout << m_x << "," << m_y << std::endl;
		}
	}
}

void Level::getTile(int, int)
{
}

void Level::levelData(SDL_Renderer* renderer)
{
	// Store renderer for future confiq and drawing
	m_pRenderer = renderer;

	//set the block dimensions
	m_blockWidth = 100;
	m_blockHeight = 100;

	//Level Data
	m_gridLayout.push_back("......W");
	m_gridLayout.push_back("......W");
	m_gridLayout.push_back("W.....W");
	m_gridLayout.push_back("W.....E");
	m_gridLayout.push_back("FFFFFFF");
	m_gridLayout.push_back("FFFFFFF");
}

Level::~Level()
{
	if (m_pbitmapTexture)
		SDL_DestroyTexture(m_pbitmapTexture);
	if (m_pbitmapSurface)
		SDL_FreeSurface(m_pbitmapSurface);
}
