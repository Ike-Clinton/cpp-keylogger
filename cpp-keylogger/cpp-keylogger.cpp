#include "stdafx.h"
#include "public.h"
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

int main(int argc, char* argv[])
{
	// New Catch sessions for running our tests in test.cpp
	Catch::Session session; // There must be exactly one instance
	int returnCode = session.applyCommandLine(argc, argv);
	if (returnCode != 0) // Indicates a command line error
		return returnCode;

	// writing to session.configData() or session.Config() here 
	// overrides command line args
	// only do this if you know you need to

	int numFailed = session.run();
	// Note that on unices only the lower 8 bits are usually used, clamping
	// the return value to 255 prevents false negative when some multiple
	// of 256 tests has failed
	return (numFailed < 0xff ? numFailed : 0xff);
}




