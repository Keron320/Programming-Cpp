// Keron_Sepp_DAC416_AE1_Project.cpp : Defines the entry point for the console application.
// LAST EDIT: 16.11.2017 - 22.55
// ASSESSMENT No 1.

#include "stdafx.h"	// Created by visual studio 2017
#include <iostream> // To print text and input values (cout,cin)
#include <ctime>    // To get accurate and different random values when using rand()
#include <cstdlib>  // To use rand() tags
#include <string>   // To use std::string
#include <conio.h>  // To use _getch();
#include <Windows.h>// To use ClearScreen functions (HANDLE,DWORD and so on)
void ClearScreen(void)
{
	HANDLE handleOut; // HANDLE is used by applications that need to read or write to the console
	CONSOLE_SCREEN_BUFFER_INFO conbufferinfo; // Contains info about console screen buffer
	DWORD count; // DWORD is a 32-bit unsigned integer
	DWORD cellCount;
	COORD coords = { 0, 0 }; // Defines the coordinates of a character cell in a console screen buffer.(0,0) is at the top, left cell of the buffer.
	handleOut = GetStdHandle(STD_OUTPUT_HANDLE);   //The standard output device. This is the active console screen buffer
	if (handleOut == INVALID_HANDLE_VALUE) return; // If the function fails, the return value is INVALID_HANDLE_VALUE
	// GetConsoleScreenBufferInfo Retrieves information about the specified console screen buffer.
	// Get the current screen buffer size and window position.
	if (!GetConsoleScreenBufferInfo(handleOut, &conbufferinfo)) return; // & is address of operator
	// dwSize - The size of the structure, in bytes. X coord and Y coord
	cellCount = conbufferinfo.dwSize.X *conbufferinfo.dwSize.Y; // * Is dereference operator
	//Fill the entire buffer with spaces
	//Writes a character to the console screen buffer a specified number of times, beginning at the specified coordinates.
	if (!FillConsoleOutputCharacter(
		handleOut,
		(TCHAR) ' ',//TCHAR stands for char and is used in Unicode build. This code would work with just char too instead of TCHAR
		cellCount,  //Gets the amount of cells to fill
		coords,     //Starts filling from 0,0
		&count      //functions require a variable to store how many characters were written
	)) return;
	//Moves cursor back to 0,0 every time
	SetConsoleCursorPosition(handleOut, coords);
}
void endmessage(void) {
	std::cout << std::endl << "Press any key to continue..." << std::endl;
}
void score(void) {
	std::cout << "Your final score is: " << std::endl;
}
void gametitle(void) {
	ClearScreen(); //Clears the screen when player wants read instructions first or returns to main menu after starting the new game.
	// Introduction - Games welcome message and title
	std::cout << " _____ _   _  _____  ______      _____    " << std::endl;
	std::cout << " |   || | | || |     | | | | | | |     |" << std::endl;
	std::cout << "  | | | |_| || |__   | |_/ / | |   | |  " << std::endl;
	std::cout << "  | | |  _  ||  __|  |  __/  | |   | | " << std::endl;
	std::cout << "  | | | | | || |___  | |     | |   | | " << std::endl;
	std::cout << "  | | | | | ||  ___  | |     | |   | |  " << std::endl;
	std::cout << ":::::::::::::::::::::::::::::::::::::::::" << std::endl;
	std::cout << " GREETINGS MORTAL! ARE YOU READY TO DIE? " << std::endl;
	std::cout << ":::::::::::::::::::::::::::::::::::::::::" << std::endl;
	std::cout << "Press numbers to interact with the main menu!" << std::endl << std::endl << std::endl << std::endl;
}
// Common enemy and player related stats
struct stats {
	int health;
	int willpower;
	int willpower_regeneration;
	int attack;
	int special_attack;
	int maximum_willpower;
	int maximum_health;
	int action_chance;
};
int main()
{
	gametitle();
	// Placed in main so the random number will be always unique and generate random numbers every time through the entire code, instead of one section of the code.
	srand(time(0));
	// Other integers
	int hero_selection;     // Player can choose between heroes he wants to play with
	int player_choice;      // Used when player has to make a decision
	int first_turn;         // Used to determine who will start first through a roll
	int heal;               // Healing ability
	int over_heal;          // When healing heals more than maximum HP
	int player_score = 0;   // Score is set to 0 when game starts; Player gets score by killing enemies
	// Chars
	char response;			// player response on 1 letter questions like menu and "play again?"
	// Booleans
	bool first_heal;        // Determines the first time "heal" is used, so players cant heal more than once in a turn
	bool player_turn;       // Determines when player turn ends, so computer can play
	bool dodge_withdraw = false, player_dodge = false; // d_wd when active makes it easier to get hit when on/off, p_d means the dodge ability is on or off
	bool enemy_dodge = false;
	bool cheat = false;
	// User can select to either start a new game by pressing 1 or 2 to exit game
	std::cout << "(1) NEW GAME" << std::endl;
	std::cout << "(2) INSTRUCTIONS" << std::endl;
	std::cout << "(3) CREDITS" << std::endl;
	std::cout << "(4) EXIT GAME" << std::endl << std::endl;
	// Remembers player input from 1 to 3. If player presses anything else the game will display "Invalid input" and return to main (Starts the program again from the start)
	std::cin >> response;
	// If player presses 1 the game will start.
	if (response == '1') {
		ClearScreen();
		std::cout << "Choose your hero!" << std::endl;
		std::cout << "(1) KORAX - HIGH HP, LOW POWER " << std::endl;
		std::cout << "(2) THE SERPENT RIDER - HIGH POWER, MEDIUM HP " << std::endl;
		std::cout << "(3) CRONOS - MEDIUM POWER and HP " << std::endl;
		std::cout << "(4) Back to main menu " << std::endl;
		// When player starts the game again after defeat the values are restored to default;
		stats player = { 150,50,5,0,0,50,150,0 };
		stats enemy = { 100,50,5,0,0,50,100,0 };
		// Remembers numbers from 1 to 3 - depending which hero player would like.(Or any other input, which will result wrong behavior of the program though)
		enum hero { KORAX = 1, THE_SERPENT_RIDER, CRONOS, MENU };
		std::cin >> hero_selection;
		switch (hero_selection) {
		case KORAX:
			std::cout << "You have selected KORAX!" << std::endl;
			// Unique hero stats. It is duplicated because each hero has different stats, instead of constant value
			player.health = player.health - 20;
			player.maximum_health = player.health;
			player.maximum_willpower = player.willpower;
			break; // Stops the loop to go on, will not show other cases.
		case THE_SERPENT_RIDER:
			std::cout << "You have selected THE SERPENT RIDER!" << std::endl;
			player.health = player.health - 60;
			player.willpower = player.willpower + 50;
			player.maximum_health = player.health;
			player.maximum_willpower = player.willpower;
			break;
		case CRONOS:
			std::cout << "You have selected CRONOS!" << std::endl;
			player.health = player.health - 40;
			player.willpower = player.willpower + 25;
			player.maximum_health = player.health;
			player.maximum_willpower = player.willpower;
			break;
		case MENU:
			return main();
			break;
			// When user types something different than expected
		default:
			ClearScreen();
			std::cout << "Invalid input!" << std::endl;
			std::cout << "Returning to main menu!" << std::endl;
			return main();
			break;
		}
		ClearScreen();
		std::cout << "PRESS 9 ON YOUR TURN TO FLEE BACK TO MAIN MENU!" << std::endl;
		std::cout << "You have entered the pit!" << std::endl;
		std::cout << "HP:" << player.health << "/" << player.maximum_health << " WP:" << player.willpower << "/" << player.maximum_willpower << std::endl;

		// Game will roll from 1 to 2 to determine whether the player or the enemy has the first turn
		first_turn = rand() % 2 + 1; // Rolls from 1 to 2
		if (first_turn = 2) { // If the game rolls more than 1 the player will start his turn first
			player_turn = true;
			std::cout << "You have the first turn!" << std::endl << std::endl;
		}
		else { // If the game rolls less than 2 the enemy will start his turn first
			player_turn = false;
			std::cout << "The enemy will have the first turn!" << std::endl << std::endl;
			std::cout << enemy.health << " HP  " << enemy.willpower << " WP " << std::endl;
		}
		do {
			if (player_turn == true) {
				std::cout << "Your turn!" << std::endl;
				std::cout << "You: " << player.health << " HP  " << player.willpower << " WP    " << "SCORE: " << player_score
					<< "   Enemy: " << enemy.health << " HP  " << enemy.willpower << " WP " << std::endl << std::endl;
				std::cout << "(1)Attack! (1-10 dmg- 80% hit chance) " << std::endl;
				std::cout << "(2)Special Attack! (5-20 dmg, 50% hit chance, 25WP)" << std::endl;
				std::cout << "(3)Re-charge - Restore 20WP" << std::endl;
				std::cout << "(4)Heal - Convert up to 50% of WP into HP" << std::endl;
				std::cout << "(5)Dodge - Decreases enemys chance of hitting by 30%, but decreases energy charging rate by 50% during this turn." << std::endl;
				// Labeling system using cases.
				enum action { ATTACK = 1, SPECIAL_ATTACK, RE_CHARGE, HEAL, DODGE };
				// Remembers player input from 1 to 5 (Or any other input, which will result wrong behavior of the program though)
				std::cin >> player_choice;
				switch (player_choice) {
				case ATTACK:// When player presses 1 and casts attack
					ClearScreen();  // Clears the screen of all previous data
					player.action_chance = rand() % 10 + 1; // Basic attack has 80% chance to hit.
					if ((player.action_chance >= 3 && dodge_withdraw != true && enemy_dodge != true)    // Determines enemy chance of getting hit based on different attributes
						|| (player.action_chance >= 2 && dodge_withdraw == true)
						|| (player.action_chance >= 6 && enemy_dodge == true)) {
						player.attack = rand() % 10 + 1;    // Generates attack from 1 to 10
						std::cout << "You attacked the enemy!" << " Enemy lost: " << player.attack << " Health points" << std::endl;
						enemy.health = (enemy.health - player.attack);  // Calculates the player attack from the enemy health_pool
						player.willpower = (player.willpower + 5);  // Attack is finished and player will restore 5 WP
						if (player.willpower >= player.maximum_willpower) { // Occurs when player has more WP than should
							std::cout << "Maximum willpower of " << player.maximum_willpower << " reached" << std::endl;
							player.willpower = player.maximum_willpower;
						}
						player_turn = false;    // Last line in this case, ends player turn
						break;  // Stops the loop and goes on with the code.
					}
					else {  // if action_chance rolls less than 3, then else block will be executed instead
						std::cout << "You missed your hit!" << std::endl;
						if (player.willpower >= player.maximum_willpower) { // If player has maximum WP
							std::cout << "Maximum willpower of " << player.maximum_willpower << " reached" << std::endl;
						}
						else {  // if has less than max then adds +5 per turn
							player.willpower = (player.willpower + 5);
						}   // Prevents player getting more WP than possible
						if (player.willpower > player.maximum_willpower) {
							player.willpower = player.maximum_willpower;
						}
						player_turn = false;    //ends player turn
						break;
					}
				case SPECIAL_ATTACK: // When player presses 2 and casts Special attack
					ClearScreen();
					if (player.willpower >= 25) {   // Special attack works only if player has 25 or more WP remaining
						player.action_chance = rand() % 10 + 1; // Special-attack has 50% chance to hit.
						if ((player.action_chance >= 5 && dodge_withdraw != true && enemy_dodge != true)
							|| ((player.action_chance >= 4 && dodge_withdraw) == true)
							|| ((player.action_chance >= 8 && enemy_dodge) == true)) {
							player.willpower = (player.willpower - 25); // Player will lose 25 willpower points if attack succeeds
							player.special_attack = rand() % 15 + 5;    // Random number between 5 and 20
							std::cout << "You used your special attack!" << " Enemy lost: " << player.special_attack << " Health points" << std::endl;
							enemy.health = (enemy.health - player.special_attack);
						}
						//When game rolls less than 6 meaning player will miss the attack
						else {  //Player will lose 25 willpower even if attack fails
							std::cout << "You missed your hit!" << std::endl;
							player.willpower = (player.willpower - 25);
						}
					}
					//If player has less than 25WP points the player is unable to cast special attack
					else {
						std::cout << "You do not have enough willpower" << std::endl;
						break;
					}
					player_turn = false;
					break;
				case RE_CHARGE: // When player presses 3 and casts Recharge
					ClearScreen();
					if (player.willpower >= player.maximum_willpower) { // If player has more WP than should
						std::cout << "Maximum willpower of " << player.maximum_willpower << " reached" << std::endl;
						break;
					}
					else {
						dodge_withdraw = true; // 10% easier to get hit Attack/S_A hit chance changes based if d_w is true or false
						std::cout << "You decide to rest for a turn!" << std::endl;
						std::cout << player.willpower << " + " << (player.willpower_regeneration * 4) << " WP" << std::endl;    // Displays the WP value.
						player.willpower = (player.willpower + (player.willpower_regeneration * 4));    // Adds 20 to player
						// Activates in case player gains more than maximum allowed points of willpower
						if (player.willpower > player.maximum_willpower) {
							player.willpower = player.maximum_willpower;
						}
					}
					player_turn = false;
					break;
				case HEAL:// When player presses 4 and casts heal
					ClearScreen();
					if (first_heal == true) {
						first_heal = false; // Prevents player to use healing more than once in a turn
						if (player.health >= player.maximum_health) {   // When player has maximum health or more
							std::cout << "You are already on full health!" << std::endl;
							break;
						}
						else if (player.willpower > 10) {   // If player has more than 10 WP left
							std::cout << "You used heal on yourself!" << std::endl;
							player.willpower = player.willpower / 2;    // Up to Half of willpower will be used to heal
							heal = player.willpower;    // Remaining willpower will be used to heal
							player.health = player.health + heal;   // Player health will be increased by the amount of "heal"
							if (player.health >= player.maximum_health) {   // If player overheals more than maximum HP
								over_heal = player.health - player.maximum_health;  // Calculation to return player some of the wp in case overhealing
								player.willpower = player.willpower + over_heal;
								player.health = player.maximum_health;
								break;
							}
							if (player.willpower > player.maximum_willpower) {  // Prevents player to gain more wp than maximum
								player.willpower = player.maximum_willpower;    // If player has more than MAX wp it will restore it to "max wp"
								break;
							}
						}
						else {
							std::cout << "You are low on willpower," << std::endl;  //When player is low on WP
							break;
						}
					}
					else if (first_heal == false) { // When player casts heal the first_turn will turn false to prevent healing more than once in one turn
						std::cout << "You already healed yourself this turn!" << std::endl;
						break;
					}

				case DODGE:// When player presses 5 and casts dodge
					ClearScreen();
					player_dodge = true;
					std::cout << "You are trying to dodge the enemy attack" << std::endl;
					player.willpower = (player.willpower + (player.willpower_regeneration / 2));
					player_turn = false;
					if (player.willpower >= player.maximum_willpower) { // Prevents player to gain more wp than maximum
						player.willpower = player.maximum_willpower;
						break;
					}
					break;
				default:
					ClearScreen();
					std::cout << "Invalid input!" << std::endl;
					if (player_choice == 1337) {    // If player knows the cheat
						cheat = true;
						enemy.health = 1;
						enemy.maximum_health = 1;
						std::cout << "You see the enemy weakening" << std::endl;
					}
					else if (player_choice == 9000) {
						cheat = true;
						player.health = 9001;
						player.maximum_health = 9001;
						player.willpower = 9001;
						player.maximum_willpower = 9001;
						std::cout << "It's over 9000!" << std::endl;
					}
					else if (player_choice == 666) {    // To end your life initially for testing purpose, does not count as cheat
						player.health = 0;
						player.maximum_health = 0;
						std::cout << "You accidentally summoned diablo who rips you apart." << std::endl;
					}
					else if (player_choice == 111) {    // To end your life initially for testing purpose, does not count as cheat
						enemy.health = 0;
					}
					else if (player_choice == 9) {  // If player wants to quit back to menu
						return main();
					}
					break;
				}
			}
			// When enemy perishes ( Has 0 or less HP )
			if (enemy.health <= 0) {
				player_turn = true;
				player_score = player_score + 100;  // Player gets 100 points of score
				std::cout << "Enemy has perised, you are awared 100 points!" << std::endl;
				if ( enemy.maximum_health <= 145 && enemy.maximum_willpower <= 95){ // To prevent going over 150 and 100
					enemy.maximum_health = enemy.maximum_health + 5;    // When the enemy perishes another one will enter the arena with more HP
					enemy.maximum_willpower = enemy.maximum_willpower + 5;  // When the enemy perishes another one will enter the arena with more WP
				}
				enemy.health = enemy.maximum_health;    // Enemy HP is restored
				enemy.willpower = enemy.maximum_willpower;  // enemy WP is restored
			}
			// ENEMY ATTACKS AND ABILITIES
			else {
				if (player_turn == false) {
					first_heal = true;
					std::cout << "Enemy turn! " << std::endl;
					//Basic attack
					if (player.health > 0 && enemy.willpower <= 25) {
						enemy.action_chance = rand() % 10 + 1;
						// This IF block determines enemy hit-chance based on player choices
						if ((enemy.action_chance >= 3 && dodge_withdraw != true && player_dodge != true)
							|| ((enemy.action_chance >= 2 && dodge_withdraw) == true)
							|| ((enemy.action_chance >= 6 && player_dodge) == true)) {
							enemy.attack = rand() % 9 + 1;  // Generates attack from 1 to 10
															// Using player_attack to show how much HP enemy lost while showing the damage
							std::cout << "Enemy attacked you!" << " You lost: " << enemy.attack << " Health points" << std::endl;
							// calculates the player attack from the enemy health_pool
							player.health = (player.health - enemy.attack);
							enemy.willpower = enemy.willpower + 5;
							if (enemy.willpower >= enemy.maximum_willpower) {
								enemy.willpower = enemy.maximum_willpower;
							}
						}
						else {
							if (enemy.willpower >= enemy.maximum_willpower) {
								enemy.willpower = enemy.maximum_willpower;
							}
							std::cout << "Enemy missed the attack!" << std::endl;
						}
					}
					// Special attack
					else if ((player.health > 0 && enemy.willpower > 24 && enemy.health > 70)
						|| (player.health > 0 && enemy.willpower == 50 && enemy.health > 50)) { // 0 will change. peaceholder
						enemy.action_chance = rand() % 10 + 1;
						// This IF block determines enemy hit-chance based on player choices
						if ((enemy.action_chance >= 5 && dodge_withdraw != true && player_dodge != true)
							|| ((enemy.action_chance >= 4 && dodge_withdraw) == true)
							|| ((enemy.action_chance >= 8 && player_dodge) == true)) {
							enemy.attack = rand() % 20 + 5; // Generates attack from 1 to 10
							// Using player_attack to show how much HP enemy lost while showing the damage
							std::cout << "Enemy used special attack on you!" << " You lost: " << enemy.attack << " Health points" << std::endl;
							// Calculates the player attack from the enemy health_pool
							player.health = (player.health - enemy.attack);
							enemy.willpower = (enemy.willpower - 25);   // Player will lose 25 willpower points if attack succeeds
							if (enemy.willpower >= enemy.maximum_willpower) {
								enemy.willpower = enemy.maximum_willpower;
							}
						}
						else {
							std::cout << "Enemy missed the attack!" << std::endl;
							enemy.willpower = enemy.willpower - 25;
						}
					}
					// RE-Charge
					else if (enemy.health >= 50 && enemy.willpower < 25) {
						dodge_withdraw = true;  // 10% easier to get hit
						std::cout << "Enemy decided to rest for a turn!" << std::endl;
						std::cout << enemy.willpower << " + " << (enemy.willpower_regeneration * 4) << " WP" << std::endl;  // Displays the WP value.
						enemy.willpower = (enemy.willpower + (enemy.willpower_regeneration * 4));   // Adds 20 to player
						// Activates in case player gains more than maximum allowed points of willpower
						if (enemy.willpower > enemy.maximum_willpower) {
							enemy.willpower = enemy.maximum_willpower;
						}
					}
					// HEAL
					else if (enemy.health <= 40 && enemy.willpower >= 24) { // Prevents player to use healing more than once in a turn
						if (enemy.willpower > 10) { // If player has more than 10 WP left
							std::cout << "Enemy used heal!" << std::endl;
							enemy.willpower = enemy.willpower / 2;  // Up to Half of willpower will be used to heal
							heal = enemy.willpower; // Remaining willpower will be used to heal
							enemy.health = enemy.health + heal; // Player health will be increased by the amount of "heal"
							if (enemy.health >= enemy.maximum_health) { // If player over heals more than maximum HP
								over_heal = enemy.health - enemy.maximum_health;    // Calculation to return player some of the WP in case over healing
								enemy.willpower = enemy.willpower + over_heal;
								enemy.health = enemy.maximum_health;
							}
							if (enemy.willpower > enemy.maximum_health) {   // Prevents player to gain more WP than maximum
								enemy.willpower = enemy.maximum_health;
							}
							enemy.action_chance = rand() % 10 + 1;
							//  This IF block determines enemy hit-chance based on player choices
							if ((enemy.action_chance >= 3 && dodge_withdraw != true && player_dodge != true)
								|| ((enemy.action_chance >= 2 && dodge_withdraw) == true)
								|| ((enemy.action_chance >= 6 && player_dodge) == true)) {
								enemy.attack = rand() % 9 + 1;  // Generates attack from 1 to 10
								// Using player_attack to show how much HP enemy lost while showing the damage
								player.health = (player.health - enemy.attack);
								std::cout << "Enemy attacked you!" << " You lost: " << enemy.attack << " Health points" << std::endl;
							}
							else {
								std::cout << "Enemy missed the attack!" << std::endl;
							}
						}
					}
					//Dodge
					else if (enemy.willpower >= 10 && enemy.health > 40 && player.health >= 80) {
						enemy_dodge = true;
						std::cout << "Enemy tries to dodge your poor attempt you call attack " << std::endl;
						enemy.willpower = (enemy.willpower + (enemy.willpower_regeneration / 2));
						if (enemy.willpower > enemy.maximum_willpower) {
							enemy.willpower = enemy.maximum_willpower;
						}
					}
					else {
						enemy.action_chance = rand() % 10 + 1;
						// This IF block determines enemy hit-chance based on player choices
						if ((enemy.action_chance >= 3 && dodge_withdraw != true && player_dodge != true)
							|| ((enemy.action_chance >= 2 && dodge_withdraw) == true)
							|| ((enemy.action_chance >= 6 && player_dodge) == true)) {
							enemy.attack = rand() % 9 + 1; // Generates attack from 1 to 10
							// Using player_attack to show how much HP enemy lost while showing the damage
							std::cout << "Enemy attacked you!" << " You lost: " << enemy.attack << " Health points" << std::endl;
							// Calculates the player attack from the enemy health_pool
							player.health = (player.health - enemy.attack);
							enemy.willpower = enemy.willpower + 5;
							if (enemy.willpower >= enemy.maximum_willpower) {
								enemy.willpower = enemy.maximum_willpower;
							}
						}
					}
					player_turn = true; // When enemy finishes his turn, the player will get a new turn
				}
			}
		} while (player.health > 0);    // Loop lasts until player has more than 0 HP
		if (player.health <= 0) {   // when player has equal or less HP
			std::cout << "LOSER!" << std::endl;
			if (cheat == true) {
				std::cout << "Hax0rs are unwanted in this game!" << std::endl;
			}
			//Rewards player with title message based on score
			else if (player_score == 0) {
				score();
				std::cout << player_score << std::endl;
				std::cout << "Wimps should not play this game" << std::endl;
			}
			else if (player_score >= 100 && player_score <= 299) {
				score();
				std::cout << player_score << std::endl;
				std::cout << "You are not worthy." << std::endl;
			}
			else if (player_score >= 300 && player_score <= 499) {
				score();
				std::cout << player_score << std::endl;
				std::cout << "You did well!" << std::endl;
			}
			else if (player_score >= 500 && player_score <= 999) {
				score();
				std::cout << player_score << std::endl;
				std::cout << "Golly, you're the best!" << std::endl;
			}
			else if (player_score >= 1000) {
				score();
				std::cout << player_score << std::endl;
				std::cout << "Is there something you need? Can I carry your weapon? Shine your boots? Backrub, perhaps?!" << std::endl;
			}
			else {
				endmessage();   //Program will terminate with end message if something does not work.
				return 0;
			}
			std::cout << "Would you like to start over? (y/n)" << std::endl;
			std::cin >> response;   // Records player choice either y or "else"
			if (response == 'y') {
				ClearScreen();
				return main();
			}
			// When player press n or anything else the program will shut down
			else {
				return 0;
			}
		}
	}
	else if (response == '2') {
		ClearScreen();
		gametitle();
		std::cout << "Thank you for playing THE PIT! " << std::endl;
		std::cout << "To start the game please press number 1 in the main menu." << std::endl;
		std::cout << "Hero selection screen will appear and you can choose between three heroes." << std::endl;
		std::cout << "After choosing your hero the game will start and you can start the combat with the enemy." << std::endl;
		std::cout << "When enemy perishes you will be awarded 100 points and the new enemy will appear, stronger than the last one." << std::endl;
		std::cout << "The game will last until the player loses all his health." << std::endl;
		std::cout << "Remember you can always press 9 during your turn to return to main menu!" << std::endl;
		endmessage();
		_getch();
		return main();
	}
	// If player presses 2 the game will display good bye message and shut down
	else if (response == '4') {
		std::cout << "This game is too difficult for you anyway." << std::endl;
		endmessage();
		_getch();
		return 0;
	}
	else if (response == '3') {
		ClearScreen();
		gametitle();
		std::cout << "Programming: Keron Sepp" << std::endl;
		std::cout << "Game design: Keron Sepp" << std::endl;
		std::cout << "Additional support:	" << std::endl;
		std::cout << "Programming ideas and support: Dave Cobb" << std::endl;
		std::cout << "Playtesting: Marko Ojasoo" << std::endl;
		std::cout << "Balancing and difficulty testing: Roberta Elisabeth Kollo" << std::endl;
		endmessage();
		_getch();
		return main();
	}
	// If the player types anything else than 1 or 2
	else {
		std::cout << "Invalid input!" << std::endl;
		return main();
	}
}
/*/
DEV DIARY 07.10.2017

Made the basic structure and gave my game a fancy title!
Finished making basic main menu and added hero selection with unbalanced stats.


DEV DIARY 08.10.2017

Made some design ideas and basic structure to follow, to keep the main game working.
Made user to have player choices between 3 characters, have not focused on the stats fully yet. Main goal is to get one hero working properly, before attempting to
get all 3 working and balanced.

DEV DIARY 09.10.2017

Added cstdlib and ctime libraries to get accurate random numbers to decide who starts the turn first and to design computers AI.
Added random enemy spawns between 3 different enemies with different stats.Made basic attack functions, Game is not yet playable as enemy will not attack the player and
will dissapear after player has done something.

DEV DIARY 10.10.2017
Fixed the last else if statements to just else {} on the last options to optimize the program.
Optimised the code, removed unessecary lines, from 200 lines to 100 lines.Still working on getting "turn based" systems to work and make AI to work.
Struggling with while loop, and getting the game working rather than just display text.

DEV DIARY 14.10.2017
Trying to get the Character selection working when player inputs wrong value.Started to experiment with "switch" tag and case / default instead of always.
Fixed the main menu, when user enters invalid input the program will return to main and give the player another try to either start the game or exit program.

DEV DIARY 15.10.2017
Decided to use "Do_While" loop on character selection, It appears to be working and the switches / cases work aswell.Changed the number inputs from '1' to 1 because using int works just as good.
I had idea to make the invalid input make the player tho try choosing character gain instead of returning to main, but right now it works like that aswell, not perfect but works.
Decided to look into the matter which hero selection and managed to get it working as I wanted it to work!yay.

DEV DIARY 17.10.2017
Trying to play around with the <switch> tag, added some random functions to calculate the first turn.Having trouble getting the turn based combat system done.

DEV DIARY 21.10.2017
I finally managed to get the game working!The loop works!Enemy attacks me.Finally!Now I have to make improvements in the AI and it is almost ready for additional tweaking.

DEV DIARY 26.10.2017
Tweaked the code, optimised it by making it look readable, trying to limit myself 80 characters per line, introduced myself to stairing the code.Tweaked the games fighting mechanics
to make the game more balanced.Finally found a solution to a problem that was gamebreaking.Game did not understand when player had maximum amount of Willpower so I managed to fix it really
easily by adding an if block to the mana restoration case.So now if player has 45 out of 50 mana he can rest but will get only + 5 instead of over - reaching the maximum and having 70 mana which was
game - breaking.From now on I try to make simple comments and place them properly.Following the good ways of programming.

DEV DIARY 29.10.2017
Fixed minor lines of code that were unnessescary.Trying to implement a healing system in the game, working on that currently.Also trying to use enum sytem to make code readabilty better.

DEV DIARY 31.10.2017

Fixed a lot of warnings that compiler gave me.Starting from Player == '4'.3.2.1 as I started using enum which made player input unessescary.Fixed bug where player selection did not start properly, as new_game
was not declared true.so now when loop starts it will go true and wont break.Implemented the healing system so it works properly and returns overused mana because assingment said
that healing must use UP TO half of the mana. not spend players mana.

DEV DIARY 01.11.2017
Made a lot of changes to the code.Learnt how to{} are placed and increased the code readabilty.Made some changes to optimisation by removing lines that ever unessescary.Checked for logic errors.
Made working dodge system and healing system.So far the game runs well and no bugs have been found yet.

DEV DIARY 05.11.2017
The game is now basically completed.I have successfully implemented the A.I that can heal himself, attack the player, use special_attacks and dodge if needed.

DEV DIARY 11.11.2017
The game is completed.The A.I Works and the extra mark things are implemented.However I added "Different enemies" as if one perishes  new oene will spawn with extra 5 max

DEV DIARTY 13.11.2017
Did some minor bug fixes and trying to get screen clearing to work. Added more functions to make the good look better and take less lines.
Implemented back to main menu button when player starts the game.

DEV DIARTY 14.11.2017
After doing research screen clear related functions that windows library offers I managed to get the screen clearing to work somehow, but it does not work perfectly.
Some of the text overlaps and it gets all messy.

DEV DIARY 15.11.2017
Finally managed to get screen clearing to work properly as intended. Used the function in different places on my code.
Added CREDITS and INTRODUCTION to the main menu.
Added the pit game in the functions list and to few places in code as credits and introductions.
Added Cheat codes in the game to test game faster and for fun.
*/
