#include <windows.h>        // for sleep()
#include <iostream>
#include <conio.h>
#include <assert.h>
#include <vector>
#include <string>
#include "cMaze.h"
#include "cTimer.h"
#include "cVector2.h"
#include "cMouse.h"

const int ESC_KEY = 27;

// Display mouse in the maze, and remove tracks
// second "ghost mouse" to remove tracks is to print the maze only once.	
void mousePrint(const cVector2& mousePos, const cVector2& mouse2Pos, cMaze& maze)
{
	HANDLE handleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handleOut, &info);
	COORD coord; // Mouse Coord
	COORD coord2;// Ghost mouse Coord to remove tracks
	coord.X = mousePos.x;
	coord.Y = mousePos.y;
	coord2.X = mouse2Pos.x;
	coord2.Y = mouse2Pos.y;
	std::string sMouse = "M";  // Displays mouse in the maze
	std::string sMouse2 = " "; // Follows mouse and replaces letter M with space to make it look like tracks are removed.
	DWORD d = 0;
	DWORD dw = 0;
	DWORD dstart = 0;
	WriteConsoleOutputCharacter(handleOut, sMouse.c_str(), sMouse.size(), coord, &d);
	WriteConsoleOutputCharacter(handleOut, sMouse2.c_str(), sMouse2.size(), coord2, &dw);
	// Needed to prevent other information being printed in maze like coordinates and timer.
	coord.Y = maze.getHeight() - 1;
	coord2.Y = maze.getHeight() - 1;
	SetConsoleCursorPosition(handleOut, coord);
}

// Function to prevent 'S' point from dissapearing when 'M' or " " are on top of it.
void startPosition(const cVector2& startPos, cMaze& maze)
{
HANDLE handleOut = GetStdHandle(STD_OUTPUT_HANDLE);
COORD mstart;
mstart.X = startPos.x;
mstart.Y = startPos.y;
SetConsoleCursorPosition(handleOut, mstart);
std::cout << maze.getStartChar();
}


int main()
{

	// create a maze variable and create a new maze
	cMaze   maze;
	maze.createRandomSize();
	// To make a copy of the maze
	std::vector<std::string> maze_copy = maze.getStrings();
	
		
	// print the maze
	maze.print();


	// Display timing updates
	std::cout << std::endl << std::endl << "Limit =  " << maze.getTimeLimit_ms() << " ms" << std::endl;
	std::cout << std::endl << "Press a key to start the mouse ...\n";
	_getch();

	// create a timer to keep track of elapsed time
	cTimer  timer;

	// create the "mouse"
	cMouse   mouse;

	// ensure the maze was created successfully with a start point
	cVector2 mousePos;
	cVector2 mouse2Pos;
	cVector2 startPos;

	// Gets strat position coordinates
	maze.getStart(startPos);  // this line is added so the start position is constantly and not affected by mouse or mouse2pos
	maze.getStart(mousePos);	
	maze.getStart(mouse2Pos); // this line is included, because otherwise the " " will make a hole at 0, 0 coordinates. 

	int prevMove = 0;
	do
	{
		// start keeping time
		timer.start();
		

		// make the mouse move - REPLACE WITH YOUR CODE
		mouse.MoveTo(mousePos);


		//maze.print();
		std::cout << std::endl << std::endl << std::endl << mouse.GetPos() << std::endl;

		// Start position, so it can't be overridden
		startPosition(startPos, maze);

		// Mouse movement function
		mousePrint(mousePos, mouse2Pos, maze);


		//Ghost mouse behind Mouse to erase tracks
		mouse2Pos = mousePos;
		

		// Mouse movement logic
		switch (prevMove) {
			// Detects walls and changes position to left every time the mouse hits the wall.
		case (1):
			if (maze_copy[mousePos.y][mousePos.x + 1] != maze.getWallChar()) {
				mousePos.x += 1;
				prevMove = 2;	
				
			}

			else if (maze_copy[mousePos.y + 1][mousePos.x] != maze.getWallChar()) {
				mousePos.y += 1;
				prevMove = 1;
			}

			else if (maze_copy[mousePos.y][mousePos.x - 1] != maze.getWallChar()) {
				mousePos.x -= 1;
				prevMove = 4;
			}

			else {
				mousePos.y -= 1;
				prevMove = 3;
			}
			break;

		case (2):
			if (maze_copy[mousePos.y - 1][mousePos.x] != maze.getWallChar()) {
				mousePos.y -= 1;
				prevMove = 3;
			}

			else if (maze_copy[mousePos.y][mousePos.x + 1] != maze.getWallChar()) {
				mousePos.x += 1;
				prevMove = 2;
			}

			else if (maze_copy[mousePos.y + 1][mousePos.x] != maze.getWallChar()) {
				mousePos.y += 1;
				prevMove = 1;
			}

			else {
				mousePos.x -= 1;
				prevMove = 4;
			}
			break;

		case (3):
			if (maze_copy[mousePos.y][mousePos.x - 1] != maze.getWallChar()) {
				mousePos.x -= 1;
				prevMove = 4;
			}

			else if (maze_copy[mousePos.y - 1][mousePos.x] != maze.getWallChar()) {
				mousePos.y -= 1;
				prevMove = 3;
			}

			else if (maze_copy[mousePos.y][mousePos.x + 1] != maze.getWallChar()) {
				mousePos.x += 1;
				prevMove = 2;
			}

			else {
				mousePos.y += 1;
				prevMove = 1;
			}
			break;

		default:
			if (maze_copy[mousePos.y + 1][mousePos.x] != maze.getWallChar()) {
				mousePos.y += 1;
				prevMove = 1;
			}

			else if (maze_copy[mousePos.y][mousePos.x - 1] != maze.getWallChar()) {
				mousePos.x -= 1;
				prevMove = 4;
			}

			else if (maze_copy[mousePos.y - 1][mousePos.x] != maze.getWallChar()) {
				mousePos.y -= 1;
				prevMove = 3;
			}

			else if (maze_copy[mousePos.y][mousePos.x + 1] != maze.getWallChar()) {
				mousePos.x += 1;
				prevMove = 2;
			}
			break;
		}
	
		
		// If 'M' coordinates are same as exit coordinates then cheese is found and game ends.
		if (maze_copy[mousePos.y][mousePos.x] == maze.getExitChar()) {
			mouse.Cheese();
		}
		// stop keeping time
		timer.stop();

		// Display timing updates
		std::cout << std::endl << std::endl << "Limit =  " << maze.getTimeLimit_ms() << " ms" << std::endl;
		std::cout << "Elapsed =  " << timer.getElapsed_ms() << " ms\n";

		// short delay between moves to make them visible
		Sleep(25);

		// Quit if Escape is pressed.
		if (_kbhit())
		{
			if (ESC_KEY == _getch())
				return 0;
		}

	} while (!mouse.FoundCheese());

	double elapsed = timer.getElapsed_ms();
	std::cout << std::endl << std::endl << "Total time elapsed: " << elapsed << std::endl << "Press a key to exit";
	std::cin.ignore();
	_getch();
}