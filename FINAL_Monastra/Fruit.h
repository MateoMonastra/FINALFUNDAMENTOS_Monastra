#pragma once
#include "GameData.h"

#include "Snake.h"

struct Fruit
{
	COORD pos;
};

void ResetFruit(ConsoleData& consoleData, Snake snake[], Fruit& fruit);
void DrawFruit(ConsoleData& consoleData, Fruit& fruit);

