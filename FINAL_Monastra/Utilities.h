#pragma once

#include "GameData.h"

const int KEY_ENTER = 13;
const int KEY_ESC = 27;

void SetConsoleSize(ConsoleData& consoleData, bool isForMenu);

void SetConsoleFont(int size);

void DrawFrame(ConsoleData& consoleData, int delay);


