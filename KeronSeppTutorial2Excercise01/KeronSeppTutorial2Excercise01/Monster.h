#pragma once
#include "Creature.h"
#include "Creature.h"
#include "Hero.h"
#include <string>
class Monster : public Creature
{
public:

	Monster(int xpos, int ypos, std::string name);
	void chase(Hero*HeroToChase);
	bool eaten(Hero*HeroToChase);

	~Monster();

};

