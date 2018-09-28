#include "Creature.h"


// Creature attributes
Creature::Creature(int xpos, int ypos, std::string name)
{
	//Creatures position on X axis
	m_xpos = xpos;
	//Creatures position on Y axis
	m_ypos = ypos;
	//Name of the creature
	m_name = name;
}

void Creature::display()
{
	//Displays X and Y axis value and Name
	std::cout << "X: " << m_xpos << std::endl;
	std::cout << "Y: " << m_ypos << std::endl;
	std::cout << "Name:" << m_name << std::endl;
}

Creature::~Creature()
{
}

// Character movement
void Creature::left() {
	//move 1 point to the left
	m_ypos = (m_ypos - 1);
}

void Creature::right() {
	//move 1 point to the right
	m_ypos = (m_ypos + 1);
}

void Creature::up() {
	//move 1 point to the up
	m_xpos = (m_xpos + 1);
}

void Creature::down() {
	//move 1 point to the down
	m_xpos = (m_xpos - 1);
}

// Setting the xpos,ypos
void Creature::setX(int x) {
	m_xpos = x;
}

void Creature::setY(int y) {
	m_ypos = y;
}


// To get xpos, ypos value
int Creature::getX() {

	return m_xpos;
}

int Creature::getY() {

	return m_ypos;
}
