/*
filename: main.cpp
Author: Keron Sepp
Date 26/09/18
Project: Excercise 01 from Tutorial 01 (Computer Games Programming unit)
*/

#include <iostream>
#include <conio.h>
#include "Creature.h"
#include "Hero.h"
#include "Monster.h"

using namespace std;


int main() {

	//Creating two creatures
	Creature Creature1(4, 5, "Donkey");
	Creature Creature2(5, 2, "Duck");

	Hero Hero1(19, 2, 1, "Hero");
	Monster Monster1(2, 20,"Bob the monster");

	//Play loop until hero is eaten
	while(Monster1.eaten(&Hero1) == false)
	{
	Monster1.display();
	Hero1.display();
	Monster1.chase(&Hero1);
	Monster1.display();
	Hero1.display();
	}

/*
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
*/	
	

	_getch();
	return 0;
}