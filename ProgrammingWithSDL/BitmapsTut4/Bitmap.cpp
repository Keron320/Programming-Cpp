#include "Bitmap.h"
#include "SDL.h"
#include "SDL_render.h"
#include <string>

using namespace std;


Bitmap::Bitmap(SDL_Renderer* renderer, string fileName, int xpos, int ypos, bool useTransparency)
{

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

void Bitmap::draw()
{
	//Render the bitmap at the x/y
	if (m_pbitmapTexture)
	{
		SDL_Rect destRect = { m_x, m_y, m_pbitmapSurface->w, m_pbitmapSurface->h };
		SDL_RenderCopy(m_pRenderer, m_pbitmapTexture, NULL, &destRect);
	}

}
	