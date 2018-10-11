#pragma once
#include <string>

class Prop
{
private:
	//member variables
	int m_maxHitPoints;
	int m_currentHitPoints;
	std::string m_name;

	//private methods
	int getDamagePercentage(void);



public:
	Prop();
	Prop(std::string name, int maxHitPoints, int startHitPoints);

	//public methods
	void	displayDetails(void);
	int		getHitpoints(void);
	void	setHitpoints(int points);
	void	addHitpoints(int pointsToAdd);
	int		getMaxHitPoints(void);
	void	setMaxHitPoints(int maxPoints);

	~Prop();
};

