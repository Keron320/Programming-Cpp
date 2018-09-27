#pragma once
#include "Creature.h"
class Monster : public Creature
{
public:
	Monster(int xpos, int ypos, std::string name);
	~Monster();
};

