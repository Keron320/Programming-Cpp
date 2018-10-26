#pragma once
#include <string>
#include <iostream>

class Creature
{
protected:
	int m_xpos;
	int m_ypos;
	std::string m_name;

public:
	//Creature that takes x,y pos and name
	Creature(int xpos, int ypos, std::string name);

	// display that has void return and parameter lists
	void display();

	// Directions
	void left();
	void right();
	void up();
	void down();

	// Functions to set X and Y
	void setX(int);
	void setY(int);

	// Functions to get X and Y
	int getX();
	int getY();



	
	~Creature();
};

