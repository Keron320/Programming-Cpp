#include "Level.h"



Level::Level()
{


	//set the block dimensions
	//m_blockWidth = 10;
	//m_blockHeight = 10;

	//SDL_Surface* surface = SDL_CreateRGBSurface(0, m_blockWidth, m_blockHeight, 32, 0, 0, 0, 0);

	//Set the block colour
	//Uint32 blockColour = SDL_MapRGB(surface->format, 255, 0, 0);

	//Fill the rect
	//SDL_FillRect(swab, NULL, blockColour);

	//Create the bitmap texture
	//m_pbitmap = SDL_CreateTextureFromSurface(m_pRenderer, surface);

	//Don't need the surface anymore
	//SDL_FreeSurface(surface);

	//SDL_Rect destRect = { xpos, ypos, m_blockWidth, m_blockHeight };
	//SDL_RenderCopy(m_pRenderer, m_pbitmap, NULL, &destRect);


}

int Level::getHeight()
{
	//Get the number of rows in m_gridLayout
	return m_gridLayout.size();
}

int Level::getWidth()
{
	//Get the number of columns in m_gridLayout
	// Basically get the first rows string lenght and you are good because all columns have same amount of chars.
	return m_gridLayout[0].length(); 
}


void Level::levelData(SDL_Renderer* renderer)
{
	// Store renderer for future confiq and drawing
	m_pRenderer = renderer;

	//set the block dimensions
	m_blockWidth = 10;
	m_blockHeight = 10;

	//Level Data
	m_gridLayout.push_back("WWWWWW");
	m_gridLayout.push_back("W....W");
	m_gridLayout.push_back("W....W");
	m_gridLayout.push_back("W....W");
	m_gridLayout.push_back("W....W");
	m_gridLayout.push_back("WWWWWW");

}

Level::~Level()
{
	if (m_pbitmapTexture)
		SDL_DestroyTexture(m_pbitmapTexture);
	if (m_pbitmapSurface)
		SDL_FreeSurface(m_pbitmapSurface);
}
