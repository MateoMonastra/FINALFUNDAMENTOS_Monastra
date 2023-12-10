#include "Snake.h"

#include "Utilities.h"

Snake InitSnake(ConsoleData consoleData)
{
	Snake snake;

	snake.winingLength = 5;

	snake.pos.X = consoleData.consoleWide / 2;
	snake.pos.Y = consoleData.consoleHeight / 2;
	snake.direction = 'A';

	snake.currentLength = 1;
	snake.landedFruits = 0;
	snake.catchedFruits = 0;

	return snake;
}

void UpdateSnake(ConsoleData& consoleData, Snake snake[])
{
	consoleData.cursorPosition.X = snake[snake[0].currentLength - 1].pos.X;
	consoleData.cursorPosition.Y = snake[snake[0].currentLength - 1].pos.Y;

	SetConsoleCursorPosition(consoleData.hwnd, consoleData.cursorPosition);

	cout << " ";

	if (snake[0].currentLength > 1)
	{
		for (int i = snake[0].currentLength - 1; i > 0; i--)
		{
			snake[i] = snake[i - 1];
		}
	}

	switch (snake[0].direction)
	{
	case (char)Directions::LEFT:
	{
		snake[0].pos.X--;
		break;
	}
	case (char)Directions::RIGHT:
	{
		snake[0].pos.X++;
		break;
	}
	case (char)Directions::UP:
	{
		snake[0].pos.Y--;
		break;
	}
	case (char)Directions::DOWN:
	{
		snake[0].pos.Y++;
		break;
	}
	}
	
}

void DrawSnake(ConsoleData& consoleData, Snake snake[])
{
	SetConsoleTextAttribute(consoleData.hwnd, FOREGROUND_BLUE);

	for (int i = 0; i < snake[0].currentLength; i++)
	{
		SetConsoleCursorPosition(consoleData.hwnd, snake[i].pos);
		cout << (char)219;
	}
}

void ShowResult(ConsoleData& consoleData, Snake snake[])
{
	string points = "Total points: ";

	consoleData.cursorPosition.Y = (consoleData.consoleHeight / 2) + 1;
	consoleData.cursorPosition.X = (consoleData.consoleWide / 2) - (points.length() / 2) - 1;

	SetConsoleCursorPosition(consoleData.hwnd, consoleData.cursorPosition);

	cout << points << snake[0].currentLength;
}
