#pragma once
#include <string>
#include <iostream>

class Prop
{
private:
	//member variables
	int m_maxHitPoints;
	int m_currentHitPoints;
	int m_startHitPoints;
	std::string m_name;

	//private methods
	int getDamagePercentage(void);



public:
	Prop();
	Prop(std::string name, int maxHitPoints, int startHitPoints, int currentHitPoints);

	//public methods
	void	displayDetails(void);
	int		getHitpoints(void);
	void	setHitpoints(int points);
	void	addHitpoints(int pointsToAdd);
	int		getMaxHitPoints(void);
	void	setMaxHitPoints(int maxPoints);

	//Name stuff
	void setName(std::string name);
	std::string getName(void);
	
	

	~Prop();
};

