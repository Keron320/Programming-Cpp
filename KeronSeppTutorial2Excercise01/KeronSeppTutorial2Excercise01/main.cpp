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
#include "Prop.h"
#include "CopyCharacter.h"
#include "PointerCharacter.h"

using namespace std;

Prop myProp;
Prop myProp2;
Prop myProp3;

void propDisplay(Prop* myProp)
{
	//Set all the stuff
	myProp->setHitpoints(100);
	myProp->setMaxHitPoints(120);
	myProp->setName("Chair");

	//Get all the stuff
	myProp->getHitpoints();
	myProp->getMaxHitPoints();
	myProp->getName();

	//Display all the stuff
	myProp->displayDetails();
}

void propDisplay2(Prop myProp2)
{
	//Set all the stuff
	myProp2.setHitpoints(100);
	myProp2.setMaxHitPoints(120);
	myProp2.setName("Chair");

	//Get all the stuff
	myProp2.getHitpoints();
	myProp2.getMaxHitPoints();
	myProp2.getName();

	//Display all the stuff
	myProp2.displayDetails();
}

void propDisplay3(Prop myProp3)
{
	//Set all the stuff
	myProp3.setHitpoints(100);
	myProp3.setMaxHitPoints(120);
	myProp3.setName("Chair");

	//Get all the stuff
	myProp3.getHitpoints();
	myProp3.getMaxHitPoints();
	myProp3.getName();

	//Display all the stuff
	myProp3.displayDetails();
}

void UpdatePropDetailsCopy(Prop p, int hp)
{
	p.setHitpoints(hp);
}

void UpdatePropDetailsPointer(Prop* p, int hp)
{
	p->setHitpoints(hp);
}


int main() {
	Prop prop1;
	Prop prop2;

	CopyCharacter copyChar("copy");
	PointerCharacter* pointChar = new PointerCharacter("pointer");

	//print prop details
	prop1.displayDetails();

	//update copy.prop
	UpdatePropDetailsPointer(&prop1, 100);
	//print again
	prop1.displayDetails();
	//update copy.prop
	UpdatePropDetailsCopy(prop1, 100);
	//print again
	prop1.displayDetails();



	/*cout << myProp.getName() << endl;

	propDisplay(&myProp);
	cout << myProp.getName() << endl;*/



	//propDisplay(myProp2);

	//propDisplay(myProp3);



	//Creating two creatures
	Creature Creature1(4, 5, "Donkey");
	Creature Creature2(5, 2, "Duck");

	Hero Hero1(19, 2, 3, "Hero");
	Monster Monster1(2, 20, "Bob the monster");

	//Play loop until hero is eaten
	while (Monster1.eaten(&Hero1) == false && Hero1.getLives() != 0)
	{
		Monster1.display();
		Hero1.display();
		Monster1.chase(&Hero1);
		Monster1.display();
		Hero1.display();

		if (Monster1.eaten(&Hero1) == true && Hero1.getLives() != 0)
		{
			//Decrease hp by 1 when eaten and HP is not 0
			Hero1.setLives(Hero1.getLives() - 1);
			//New Coordinates
			Hero1.setX(13);
			Hero1.setY(15);
			
		}

	}




	_getch();
	return 0;
}