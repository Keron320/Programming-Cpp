#pragma once
#include "Creature.h"
class Hero : public Creature
{
protected:
	int score;
	int lives;
	

public:

	Hero(int xpos, int ypos, int lives, std::string name);
	~Hero();
};

