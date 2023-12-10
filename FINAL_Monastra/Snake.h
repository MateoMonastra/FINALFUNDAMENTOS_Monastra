#pragma once

#include "GameData.h"

struct Snake
{	
	COORD pos;

	int currentLength = 1;
	int landedFruits = 0;
	int catchedFruits = 0;
	
	int winingLength;
	
	char direction = {};
};

enum class Directions
{
	UP = 'W',
	DOWN = 'S',
	LEFT = 'A',
	RIGHT = 'D'
};

Snake InitSnake(ConsoleData consoleData);
void UpdateSnake(ConsoleData& consoleData, Snake snake[]);
void DrawSnake(ConsoleData& consoleData, Snake snake[]);
void ShowResult(ConsoleData& consoleData, Snake snake[]);