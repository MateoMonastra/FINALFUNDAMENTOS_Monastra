#include "Game.h"

#include "Utilities.h"

#include "Snake.h"
#include "Fruit.h"

ConsoleData consoleData;
Snake snake[50];
Fruit fruit;


bool isGameOver = false;
bool hasWon = false;
bool collect = false;

string win = "You won!!!";
string loose = "You Lose...";

static void GetInput();
static void ColitionCheck();

void InitGame()
{

	isGameOver = false;
	hasWon = false;
	collect = false;

	consoleData.hwnd = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleData.cci);
	consoleData.cci.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleData.cci);
	
	snake[0] = InitSnake(consoleData);
	
	SetConsoleSize(consoleData);
	SetConsoleFont(10, 10);

	ResetFruit(consoleData,snake,fruit);
}

void GameUpdate(Screen& currentScene)
{
		DeltaTime();
		
		UpdateSnake(consoleData, snake);

		ColitionCheck();
		
		GetInput();

	if (isGameOver && hasWon)
	{
		consoleData.cursorPosition.Y = (consoleData.consoleHeight / 2);
		consoleData.cursorPosition.X = (consoleData.consoleWide / 2) - win.length() / 2;
		SetConsoleCursorPosition(consoleData.hwnd, consoleData.cursorPosition);
		cout << win;

		SetConsoleCursorPosition(consoleData.hwnd, consoleData.cursorPosition);

		ShowResult(consoleData, snake);

		cin.get();

		system("cls");
		SetConsoleTextAttribute(consoleData.hwnd, 0);
	}
	else if (isGameOver && !hasWon)
	{
		consoleData.cursorPosition.Y = (consoleData.consoleHeight / 2);
		consoleData.cursorPosition.X = (consoleData.consoleWide / 2) - loose.length() / 2;
		SetConsoleCursorPosition(consoleData.hwnd, consoleData.cursorPosition);
		cout << loose;

		SetConsoleCursorPosition(consoleData.hwnd, consoleData.cursorPosition);

		ShowResult(consoleData,snake);

		cin.get();

		system("cls");
		SetConsoleTextAttribute(consoleData.hwnd, 0);
	}
}

void GameDrawing()
{
	DrawSnake(consoleData,snake);

	DrawFruit(consoleData,fruit);

	if (isGameOver)
	{
		SetConsoleTextAttribute(consoleData.hwnd, FOREGROUND_RED);
	}
	
	SetConsoleTextAttribute(consoleData.hwnd, 8);
	
	DrawFrame(consoleData, 0); 
}

void GetInput()
{
	bool reverse = false;

	if (_kbhit())
	{
		char input = toupper(_getch());

		if (input == (char)Directions::LEFT || input == (char)Directions::RIGHT || input == (char)Directions::UP || input == (char)Directions::DOWN)
		{
			switch (input)
			{
			case (char)Directions::LEFT:
			{
				if (snake[0].direction == (char)Directions::RIGHT)
				{
					reverse = true;
				}

				break;
			}
			case (char)Directions::RIGHT:
			{
				if (snake[0].direction == (char)Directions::LEFT)
				{
					reverse = true;
				}

				break;
			}
			case (char)Directions::UP:
			{
				if (snake[0].direction == (char)Directions::DOWN)
				{
					reverse = true;
				}

				break;
			}
			case (char)Directions::DOWN:
			{
				if (snake[0].direction == (char)Directions::UP)
				{
					reverse = true;
				}

				break;
			}
			}

			if (!reverse)
			{
				snake[0].direction = input;
			}
		}
	}
}

void ColitionCheck()
{
	if ((snake[0].pos.X == fruit.pos.X) && (snake[0].pos.Y == fruit.pos.Y))
	{
		collect = true;
		ResetFruit(consoleData, snake, fruit);
	}

	if (collect)
	{
		snake[0].currentLength++;
		snake[0].catchedFruits++;

		collect = false;

		if (snake[0].currentLength == snake[0].winingLength)
		{
			hasWon = true;
			isGameOver = true;
		}
	}

	for (int i = snake[0].catchedFruits; i < snake[0].landedFruits; i++)
	{
		if ((snake[snake[0].currentLength - 1].pos.X == fruit.pos.X) && snake[snake[0].currentLength - 1].pos.Y == fruit.pos.Y)
		{
			collect = true;
		}
	}

	for (int i = 1; i < snake[0].currentLength; i++)
	{
		if (snake[0].pos.X == snake[i].pos.X && snake[0].pos.Y == snake[i].pos.Y)
		{
			isGameOver = true;
			break;
		}
	}

	if (snake[0].pos.X < 1 || snake[0].pos.X > consoleData.consoleWide - 2 || snake[0].pos.Y < 1 || snake[0].pos.Y > consoleData.consoleHeight - 2)
	{
		isGameOver = true;
	}
}
