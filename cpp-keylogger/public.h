#pragma once
// TODO: I don't think all of these includes are required.
// they are just some standard ones I usually use. Need to 
// go through here and remove what I don't need
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
// Stupid windows macro to fix min/max functions breaking all my unit test code
// See https://stackoverflow.com/questions/6884093/warning-c4003-not-enough-actual-parameters-for-macro-max-visual-studio-2010
#define NOMINMAX
#include <windows.h>
#include <winuser.h>
#include "prototypes.h"

