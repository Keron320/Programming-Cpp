#include "Level.h"



Level::Level(SDL_Renderer* renderer)
{
	m_pRenderer = renderer;


	//set the block dimensions
	m_blockWidth = 10;
	m_blockHeight = 10;

	//Get LevelData
	levelData(m_pRenderer);
	
	m_pbitmapSurface = SDL_CreateRGBSurface(0, m_blockWidth * getWidth(), m_blockHeight* getHeight(), 32, 0, 0, 0, 0);
	

	//Create the bitmap texture
	m_pbitmapTexture = SDL_CreateTextureFromSurface(m_pRenderer, m_pbitmapSurface);
	
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
	//SDL_Surface* surface = SDL_CreateRGBSurface(0, m_blockWidth, m_blockHeight, 32, 0, 0, 0, 0);
	
	//Set the block colour
	SDL_Rect outlineRect = { m_x, m_y, m_blockWidth, m_blockHeight };
	SDL_SetRenderDrawColor(m_pRenderer, r, g, b, 0);
	SDL_RenderDrawRect(m_pRenderer, &outlineRect);

	//Don't need the surface anymore
	//SDL_FreeSurface(surface);

	//SDL_Rect destRect = { m_x, m_y, m_blockWidth, m_blockHeight };
	//SDL_RenderCopy(m_pRenderer, m_pbitmapTexture, NULL, &destRect);
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
				tileBlock(255,244,233);
			}
			 std::cout << m_x << "," << m_y << std::endl;
		}
	}
}

void Level::show()
{
	////Draw the object
	if (m_pbitmapTexture)
	{
		SDL_Rect destRect = { 0, 0, m_pbitmapSurface->w, m_pbitmapSurface->h };
		SDL_RenderCopy(m_pRenderer, m_pbitmapTexture, NULL, &destRect);
	}


	//// Create a rectangle
	//SDL_Rect r;
	//r.x = 50;
	//r.y = 50;
	//r.w = 50;
	//r.h = 50;

	//// Change color to blue!
	//SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 255, 255);

	//// Render our SDL_Rect
	//// The rectangle will now be blue
	//SDL_RenderDrawRect(m_pRenderer, &r);

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
