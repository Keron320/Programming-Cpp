#include "Hero.h"
#include "Creature.h"



Hero::Hero(int xpos, int ypos, int lives, std::string name) : Creature (xpos, ypos, name)
{
}

Hero::~Hero()
{
}

void Hero::display()
{
	//Displays X and Y axis value and Name
	std::cout << "Lives: " << m_lives << std::endl;
	std::cout << "Score: " << m_score << std::endl;

	Creature::display();


}