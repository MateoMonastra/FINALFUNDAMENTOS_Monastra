#pragma once

#include "GameData.h"

void SetConsoleSize(ConsoleData& consoleData);

void SetConsoleFont(int wide, int height);

void DrawFrame(ConsoleData& consoleData, int delay);

int GetWiningLength();

void DeltaTime();