#pragma once

#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <conio.h>

using namespace std;

struct ConsoleData
{
	COORD cursorPosition;
	HANDLE hwnd;
	CONSOLE_FONT_INFOEX fontInfo;
	SMALL_RECT rect;
	COORD coord;
	CONSOLE_CURSOR_INFO cci;

	int gameConsoleWide = 30;
	int gameConsoleHeight = 30;

	int menuConsoleWide = 100;
	int menuConsoleHeight = 55;
};