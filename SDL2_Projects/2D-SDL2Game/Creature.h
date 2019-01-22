#pragma once
#include "Bitmap.h"
class Creature : public Bitmap
{
public:

	Creature(SDL_Renderer* renderer, std::string fileName, int xpos, int ypos, bool useTransparency = false);
	~Creature();
};

