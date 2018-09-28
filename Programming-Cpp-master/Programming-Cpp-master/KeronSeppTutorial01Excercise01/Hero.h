#pragma once
#include "Creature.h"
#include <string>
class Hero : public Creature
{
protected:
	int m_score = 0;
	int m_lives = 3;
public:

	Hero(int xpos, int ypos, int lives, std::string name);

	~Hero();

	void display();
};

