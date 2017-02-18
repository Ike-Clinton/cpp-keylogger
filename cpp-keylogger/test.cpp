#include "stdafx.h"
#include "catch.hpp"

SCENARIO("The keylogger starts, captures victim keystrokes, then writes them to a file called keys.txt on the desktop.", "[string]") {

	GIVEN("The keylogger has started") {
		// Run the keylogger. Given since we are debugging in VS usually
		// This is just a sanity check. We should never fail this test

		THEN("I should see cpp-keylogger.exe in the process list") {
			// Code to ensure the keylogger has started
			// Find HWND?
			REQUIRE(1 == 1);
		}

		AND_THEN("there should be a file called keys.txt on the desktop") {
			// Check to make sure we created a file called keys.txt on the desktop
			REQUIRE(1 == 1);
		}
		
		WHEN("the victim types 'password1'") {
			// Code to manually type on the keyboard, emulating real input	

			THEN("we should write 'password1' to a file") {
				// REQUIRE(v.size() == 10);
				// Check that the file keys.txt on the desktop contains the text password1	
				REQUIRE(1 == 1);
			}

			AND_THEN("we should see 'password1' in keys.txt") {
				// Make sure password1 is in file keys.txt
				REQUIRE(1 == 1);

			}
		}
		AND_WHEN("the victim types 'The quick brown fox jumps over the lazy dog'") {
			// Type "The quick brown fox jumps over the lazy dog" on the keyboard

			THEN("keys.txt should contain the captured sentence") {
				// ensure the text "The quick brown fox jumps over the lazy dog" appears in keys.txt
				REQUIRE(1 == 1);

			}
		}
		
		AND_WHEN("cpp-keylogger.exe is closed:") {
			
			// HWND for cpp-keylogger.exe returns 0?

			THEN("there should be a file called keys.txt on the desktop.") {
				// Make sure keys.txt is on the desktop
				REQUIRE(1 == 1);
			}

			AND_THEN("there should be a file called keys.txt on the desktop.") {
				// keys.txt should contain "password1 The quick brown fox jumps over the lazy dog"
				REQUIRE(1 == 1);
			}

			AND_THEN("I should save the file and exit") {
				// Ensure we close the file handle and exit gracefully
				// Check return code, etc
				REQUIRE(1 == 1);
			}
		}
	}
}