#include "Prop.h"



//Unused function
int Prop::getDamagePercentage(void)
{
	return 0;
}

//Constructor method
Prop::Prop()
{
	int m_maxHitPoints = 1;
	int m_startHitPoints = 2;
	int m_currentHitPoints = 23;
	m_name = "original name";
}

//What makes prop a prop
Prop::Prop(std::string name, int maxHitPoints, int startHitPoints, int currentHitPoints)
{
	int m_maxHitPoints = maxHitPoints;
	int m_startHitPoints = startHitPoints;
	int m_currentHitPoints = currentHitPoints;
	m_name = name;

}


// Displaying all the props details
void Prop::displayDetails(void)
{
	//Print out the prop information
	std::cout << "Name:" << m_name << "\n";
	// Display HP:100/80 MaxHP and CurrentHP
	std::cout << "HP:" << m_maxHitPoints << "/" << m_currentHitPoints << "\n";


}

//	Return the amount of hitpoints
int Prop::getHitpoints(void)
{
	return m_currentHitPoints;
}
// Set specific amount of health points
void Prop::setHitpoints(int points)
{
	// Set the health to any number you want, is okay if you overdo it
	m_currentHitPoints = points;

}
// Add hitpoints to the current pool of health
void Prop::addHitpoints(int pointsToAdd)
{
	// Add health points to current HP pool
	m_currentHitPoints = m_currentHitPoints + pointsToAdd;

	//Only be able to set health points if the player has less health than the maximum capacity is
	if (m_currentHitPoints >= m_maxHitPoints)
	{
		// If the player is getting more health than possible then s
		m_currentHitPoints = m_maxHitPoints;
	}
}
// Get the maxHP value
int Prop::getMaxHitPoints(void)
{
	return m_maxHitPoints;
}
// Set HP to whatever you want
void Prop::setMaxHitPoints(int maxPoints)
{
	m_maxHitPoints = maxPoints;
}
// Set name to whatever you want
void Prop::setName(std::string name)
{
	m_name = name;
}
// Get the name that was set
std::string Prop::getName(void)
{
	return m_name;
}


//Destructor method
Prop::~Prop()
{
}
