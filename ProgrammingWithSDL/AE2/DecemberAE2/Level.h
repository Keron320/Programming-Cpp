#include <iostream>
#include <string>
#include <vector>
#include <SDL.h>
#include "Bitmap.h"

struct SDL_Surface;
struct SDL_Texture;
struct SDL_Renderer;

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


	int getHeight();
	int getWidth();
	
	void tileBlock(int r, int g, int b);
	void levelRenderer();

	void levelData(SDL_Renderer* renderer);
	~Level();
};

