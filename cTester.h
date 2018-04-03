#pragma once
#include <windows.h>
#include <wincon.h>
#include <string>

// The name of the testing file your program should open and read from when doing testing
const std::string  TEST_FILE_NAME = ("test.txt");

// Testing class - create an object of this time to test your block display code
class cTester
{
public:
	//  Constructor - pass in an Output handle, or 
	//	leave blank to use the default Console Output handle
	cTester(HANDLE consoleOutputHandle = NULL);

	// Destructor - nothing to be concerned with
	~cTester();

	// The "test" function is what does the actual test.
	//	1. Read the file and display the block 
	//	2. Call "test" and pass in the block string exactly as in the data file
	//	3. Return value is true if displayed correctly, false if errors
	bool test(const std::string& stringToTest);

	// value use when clearing the screen to 'empty'
	const CHAR_INFO EMPTY_FILL{ (WCHAR) ' ', 0 };

private:
	// Internal copy of the output console handle
	HANDLE		hConsole{ NULL };
};

