#include "Fruit.h"

void ResetFruit(ConsoleData& consoleData, Snake snake[], Fruit& fruit)
{
	fruit.pos.X = (rand() % (consoleData.gameConsoleWide - 4)) + 2;
	fruit.pos.Y = (rand() % (consoleData.gameConsoleHeight - 4)) + 2;

	for (int i = 0; i < snake[0].currentLength; i++)
	{
		if (snake[i].pos.X == fruit.pos.X && snake[i].pos.Y == fruit.pos.Y)
		{
			i = -1;

			fruit.pos.X = (rand() % (consoleData.gameConsoleWide - 4)) + 2;
			fruit.pos.Y = (rand() % (consoleData.gameConsoleHeight - 4)) + 2;
		}
	}

	snake[0].landedFruits++;
}

void DrawFruit(ConsoleData& consoleData, Fruit& fruit)
{
	SetConsoleCursorPosition(consoleData.hwnd, fruit.pos);
	SetConsoleTextAttribute(consoleData.hwnd, 10);

	cout << "*";
}