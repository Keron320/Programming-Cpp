#include "Monster.h"




Monster::Monster(int xpos, int ypos, std::string name) : Creature (xpos, ypos, name)
{

}

// Monsters chasing algorithm
void Monster::chase(Hero*HeroToChase)
{
	int heroX = HeroToChase->getX();
	int heroY = HeroToChase->getY();
	
	if (m_xpos > heroX)
	{
		down();
	}
	if (m_xpos < heroX)
	{
		up();
	}
	if (m_ypos > heroY)
	{
		left();
	}
	if (m_ypos < heroY)
	{
		right();
	}
}

// Function that sees if the hero is eaten or not
bool Monster::eaten(Hero*HeroToChase)
{
	int heroX = HeroToChase->getX();
	int heroY = HeroToChase->getY();

	if ((m_xpos == heroX) && (m_ypos == heroY))
	{
		return true;
	}

	else
	{
		return false;
	}
}

Monster::~Monster()
{
}
