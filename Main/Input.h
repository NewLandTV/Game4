#ifndef __INPUT_H__
#define __INPUT_H__

#include <conio.h>
#include <Windows.h>

// Macro functions
#define GetKeyDown(keyCode) GetAsyncKeyState(keyCode) & 0x8000
#define GetKey(keyCode) GetAsyncKeyState(keyCode) & 0x8001
#define GetKeyUp(keyCode) GetAsyncKeyState(keyCode) & 0x0001
#define GetAnyKey() _kbhit()
#define GetKeyCode() _getch()

#endif