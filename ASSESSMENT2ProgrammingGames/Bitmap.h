#pragma once
#include <string>

struct SDL_Surface;
struct SDL_Texture;
struct SDL_Renderer;


class Bitmap
{
private:
	SDL_Surface*	m_pbitmapSurface;
	SDL_Texture*	m_pbitmapTexture;
	SDL_Renderer*	m_pRenderer;


	int m_x, m_y;
	int scalerX;
	int scalerY;

public:

	
	Bitmap(SDL_Renderer* renderer, std::string fileName, int xpos, int ypos, bool useTransparency = false);
	~Bitmap();

	void draw(int m_scaleX, int m_scaleY);
	void setPos();
	//Bitmap control
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
};

