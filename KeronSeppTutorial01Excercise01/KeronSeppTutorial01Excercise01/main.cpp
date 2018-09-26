/*
filename: main.cpp
Author: Keron Sepp
Date 26/09/18
Project: Excercise 01 from Tutorial 01 (Computer Games Programming unit)
*/

#include <iostream>
#include <conio.h>
#include "Creature.h"

using namespace std;


int main() {

	//Creating two creatures
	Creature Creature1(4, 5, "Donkey");
	Creature Creature2(5, 2, "Duck");

	//Displaying the original values ( should be 0 and 0 and name)
	Creature1.display();
	Creature2.display();

	//Setting creature 1 position
	Creature1.setX(10);
	Creature1.setY(15);

	//Setting creature 2 position
	Creature2.setX(18);
	Creature2.setY(19);

	//Displaying the updated values
	Creature1.display();
	Creature2.display();
	
	
	// Move around the creature 5 times
		// Get Creature current position
		Creature1.getX();
		Creature1.getY();
			// Move creature around
			Creature1.down();
				//Display result
				Creature1.display();
		// Get Creature current position
		Creature1.getX();
		Creature1.getY();
			Creature1.down();
				//Display result
				Creature1.display();
		// Get Creature current position
		Creature1.getX();
		Creature1.getY();
			Creature1.up();
				//Display result
				Creature1.display();
			Creature1.left();
				//Display result
				Creature1.display();
		// Get Creature current position
		Creature1.getX();
		Creature1.getY();
			Creature1.right();
				//Display result
				Creature1.display();

	// Move around the second creature 5 times
	// Get Creature current position
		Creature2.getX();
		Creature2.getY();
			// Move creature around
			Creature2.down();
	// Get Creature current position
		Creature2.getX();
		Creature2.getY();
			// Move creature around
			Creature2.down();
				//Display result
				Creature2.display();
	// Get Creature current position
		Creature2.getX();
		Creature2.getY();
			// Move creature around
			Creature2.left();
				//Display result
				Creature2.display();
		// Get Creature current position
		Creature2.getX();
		Creature2.getY();
			// Move creature around
			Creature2.left();
				//Display result
				Creature2.display();
		// Get Creature current position
		Creature2.getX();
		Creature2.getY();
			// Move creature around
			Creature2.left();
				//Display result
				Creature2.display();


	_getch();
	return 0;
}