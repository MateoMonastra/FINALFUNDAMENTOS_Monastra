#include "Game.h"

#include "Utilities.h"

#include "Snake.h"
#include "Fruit.h"
#include "Menu.h"

enum class Scenes
{
	Rules,
	SelectDifficulty,
	Playing,
	GameOver,
};

Scenes currentScene;
ConsoleData consoleData;

const int MAX_SIZE = 90;
Snake snake[MAX_SIZE];
Fruit fruit;

Difficulty difficulty;

int difficultyOptions = 0;
int gameOverOptions = 0;

bool collect = false;
bool hasWon = false;

string win = "You won!!!";
string lose = "You Lose...";

static void InitPlay();
static void GetPlayInput();
static void GetRulesInput();
static void GetSelectDifficultyInput();
static void GetGameOverInput(Screen& currentScreen);
static void ColitionCheck();
static void DeltaTime();

void InitGame()
{
	currentScene = Scenes::Rules;

	hasWon = false;
	collect = false;

	consoleData.hwnd = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleData.cci);
	consoleData.cci.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleData.cci);

	SetConsoleSize(consoleData, 0);
	SetConsoleFont(24);

}

static void InitPlay()
{
	snake[0] = InitSnake(consoleData, difficulty);
	ResetFruit(consoleData, snake, fruit);
}

void GameUpdate(Screen& currentScreen)
{
	if (currentScene == Scenes::Rules)
	{
		GetRulesInput();
	}
	else if (currentScene == Scenes::SelectDifficulty)
	{
		GetSelectDifficultyInput();
	}
	else if (currentScene == Scenes::Playing)
	{
		DeltaTime();

		UpdateSnake(consoleData, snake);

		ColitionCheck();

		GetPlayInput();
	}
	else if (currentScene == Scenes::GameOver)
	{
		GetGameOverInput(currentScreen);
	}
}

void GameDrawing()
{
	if (currentScene == Scenes::Rules)
	{
		consoleData.cursorPosition.Y = (consoleData.gameConsoleHeight / 9);
		consoleData.cursorPosition.X = (1);
		SetConsoleCursorPosition(consoleData.hwnd, consoleData.cursorPosition);
		cout << "W: Move the snake upward";

		consoleData.cursorPosition.Y = (consoleData.gameConsoleHeight / 9 * 2);
		consoleData.cursorPosition.X = (1);
		SetConsoleCursorPosition(consoleData.hwnd, consoleData.cursorPosition);
		cout << "A: Move the snake to the left";

		consoleData.cursorPosition.Y = (consoleData.gameConsoleHeight / 9 * 3);
		consoleData.cursorPosition.X = (1);
		SetConsoleCursorPosition(consoleData.hwnd, consoleData.cursorPosition);
		cout << "S: Move the snake downward";

		consoleData.cursorPosition.Y = (consoleData.gameConsoleHeight / 9 * 4);
		consoleData.cursorPosition.X = (1);
		SetConsoleCursorPosition(consoleData.hwnd, consoleData.cursorPosition);
		cout << "D:Move the snake to the right";

		consoleData.cursorPosition.Y = (consoleData.gameConsoleHeight / 9 * 6);
		consoleData.cursorPosition.X = (1);
		SetConsoleCursorPosition(consoleData.hwnd, consoleData.cursorPosition);
		cout << "If you collide with any wall" << endl;
		cout << endl << " or your own tail" << endl;
		cout << endl << " you will lose the game.";

		consoleData.cursorPosition.Y = (consoleData.gameConsoleHeight - 2);
		consoleData.cursorPosition.X = (1);
		SetConsoleCursorPosition(consoleData.hwnd, consoleData.cursorPosition);
		cout << "PRESS ENTER TO PASS THE PAGE ";
	}
	else if (currentScene == Scenes::SelectDifficulty)
	{
		consoleData.cursorPosition.Y = (consoleData.gameConsoleHeight / 8);
		consoleData.cursorPosition.X = (6);

		SetConsoleTextAttribute(consoleData.hwnd, 3);
		SetConsoleCursorPosition(consoleData.hwnd, consoleData.cursorPosition);
		cout << "SELECT DIFFICULTY ";

		consoleData.cursorPosition.Y = (consoleData.gameConsoleHeight / 8 + 2);
		consoleData.cursorPosition.X = (6);
		SetConsoleCursorPosition(consoleData.hwnd, consoleData.cursorPosition);
		cout << "  WITH W AND S ";

		consoleData.cursorPosition.Y = (consoleData.gameConsoleHeight / 8 + 4);
		consoleData.cursorPosition.X = (6);
		SetConsoleCursorPosition(consoleData.hwnd, consoleData.cursorPosition);
		cout << "THEN USE ENTER: ";

		consoleData.cursorPosition.Y = (consoleData.gameConsoleHeight / 5 * 2);
		consoleData.cursorPosition.X = (6);
		SetConsoleCursorPosition(consoleData.hwnd, consoleData.cursorPosition);
		SetConsoleTextAttribute(consoleData.hwnd, FOREGROUND_GREEN);

		if (difficultyOptions == 0)
		{
			cout << "EASY (15 POINTS) <<";
		}
		else
		{
			cout << "EASY (15 POINTS)    ";
		}

		consoleData.cursorPosition.Y = (consoleData.gameConsoleHeight / 5 * 3);
		consoleData.cursorPosition.X = (6);
		SetConsoleCursorPosition(consoleData.hwnd, consoleData.cursorPosition);
		SetConsoleTextAttribute(consoleData.hwnd, FOREGROUND_INTENSITY);

		if (difficultyOptions == 1)
		{
			cout << "MEDIUM (45 POINTS) <<";
		}
		else
		{
			cout << "MEDIUM (45 POINTS)    ";
		}
		consoleData.cursorPosition.Y = (consoleData.gameConsoleHeight / 5 * 4);
		consoleData.cursorPosition.X = (6);
		SetConsoleCursorPosition(consoleData.hwnd, consoleData.cursorPosition);
		SetConsoleTextAttribute(consoleData.hwnd, FOREGROUND_RED);

		if (difficultyOptions == 2)
		{
			cout << "HARD (65 POINTS) <<";
		}
		else
		{
			cout << "HARD (65 POINTS)    ";
		}

	}
	else if (currentScene == Scenes::Playing)
	{
		DrawFruit(consoleData, fruit);

		SetConsoleTextAttribute(consoleData.hwnd, FOREGROUND_BLUE);

		DrawSnake(consoleData, snake);

		SetConsoleTextAttribute(consoleData.hwnd, 8);

		DrawFrame(consoleData, 0);
	}
	else if (currentScene == Scenes::GameOver)
	{

		if (hasWon)
		{
			SetConsoleTextAttribute(consoleData.hwnd, FOREGROUND_BLUE);
			DrawSnake(consoleData, snake);
		
			consoleData.cursorPosition.Y = (consoleData.gameConsoleHeight / 2) - 10;
			consoleData.cursorPosition.X = (consoleData.gameConsoleWide / 2) - lose.length() / 2;
			SetConsoleCursorPosition(consoleData.hwnd, consoleData.cursorPosition);
			cout << win;

			SetConsoleCursorPosition(consoleData.hwnd, consoleData.cursorPosition);

			ShowResult(consoleData, snake);

			consoleData.cursorPosition.Y = (consoleData.gameConsoleHeight / 2);
			consoleData.cursorPosition.X = (consoleData.gameConsoleWide / 2) - lose.length() / 2 - 3;
			SetConsoleCursorPosition(consoleData.hwnd, consoleData.cursorPosition);

			if (gameOverOptions == 0)
			{
				cout << "RETURN MENU <<";
			}
			else
			{
				cout << "RETURN MENU   ";
			}

			consoleData.cursorPosition.Y = (consoleData.gameConsoleHeight / 2) + 5;
			SetConsoleCursorPosition(consoleData.hwnd, consoleData.cursorPosition);

			if (gameOverOptions == 1)
			{
				cout << "PLAY AGAIN <<";
			}
			else
			{
				cout << "PLAY AGAIN   ";
			}
		}
		else
		{
			SetConsoleTextAttribute(consoleData.hwnd, FOREGROUND_RED);
			DrawSnake(consoleData, snake);
			
			consoleData.cursorPosition.Y = (consoleData.gameConsoleHeight / 2) - 10;
			consoleData.cursorPosition.X = (consoleData.gameConsoleWide / 2) - lose.length() / 2;
			SetConsoleCursorPosition(consoleData.hwnd, consoleData.cursorPosition);
			cout << lose;

			SetConsoleCursorPosition(consoleData.hwnd, consoleData.cursorPosition);

			ShowResult(consoleData, snake);

			consoleData.cursorPosition.Y = (consoleData.gameConsoleHeight / 2);
			consoleData.cursorPosition.X = (consoleData.gameConsoleWide / 2) - lose.length() / 2 - 3;
			SetConsoleCursorPosition(consoleData.hwnd, consoleData.cursorPosition);

			if (gameOverOptions == 0)
			{
				cout << "RETURN MENU <<";
			}
			else
			{
				cout << "RETURN MENU   ";
			}

			consoleData.cursorPosition.Y = (consoleData.gameConsoleHeight / 2) + 5;
			SetConsoleCursorPosition(consoleData.hwnd, consoleData.cursorPosition);

			if (gameOverOptions == 1)
			{
				cout << "PLAY AGAIN <<";
			}
			else
			{
				cout << "PLAY AGAIN   ";
			}
		}
	}
}

static void GetPlayInput()
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

static void GetRulesInput()
{
	if (_kbhit())
	{
		char input = toupper(_getch());

		if (input == (char)KEY_ENTER)
		{
			currentScene = Scenes::SelectDifficulty;
			system("cls");
		}
	}
}

static void GetSelectDifficultyInput()
{
	if (_kbhit())
	{
		char input = toupper(_getch());

		if (input == 'W' || input == 'S' || input == (char)KEY_ENTER)
		{
			switch (input)
			{
			case 'S':

				difficultyOptions++;

				if (difficultyOptions > 2)
				{
					difficultyOptions = 2;
				}

				break;

			case 'W':
				difficultyOptions--;

				if (difficultyOptions < 0)
				{
					difficultyOptions = 0;
				}
				break;

			case (char)KEY_ENTER:

				if (difficultyOptions == 0)
				{
					difficulty = Difficulty::EASY;
				}
				else if (difficultyOptions == 1)
				{
					difficulty = Difficulty::MEDIUM;
				}
				else if (difficultyOptions == 2)
				{
					difficulty = Difficulty::HARD;
				}

				system("cls");
				currentScene = Scenes::Playing;
				InitPlay();
				break;
			}
		}

	}
}

static void GetGameOverInput(Screen& currentScreen)
{
	if (_kbhit())
	{
		char input = toupper(_getch());

		if (input == 'W' || input == 'S' || input == (char)KEY_ENTER)
		{
			switch (input)
			{
			case 'S':

				gameOverOptions++;

				if (gameOverOptions > 1)
				{
					gameOverOptions = 1;
				}

				break;

			case 'W':
				gameOverOptions--;

				if (gameOverOptions < 0)
				{
					gameOverOptions = 0;
				}
				break;

			case (char)KEY_ENTER:

				if (gameOverOptions == 0)
				{
					currentScreen = Screen::Menu;
					InitMenu();
				}
				else if (gameOverOptions == 1)
				{
					currentScene = Scenes::SelectDifficulty;
				}

				system("cls");
				break;
			}
		}

	}
}

static void ColitionCheck()
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
			currentScene = Scenes::GameOver;
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
			currentScene = Scenes::GameOver;
			break;
		}
	}

	if (snake[0].pos.X < 1 || snake[0].pos.X > consoleData.gameConsoleWide - 2 || snake[0].pos.Y < 1 || snake[0].pos.Y > consoleData.gameConsoleHeight - 2)
	{
		currentScene = Scenes::GameOver;
	}
}

static void DeltaTime()
{
	if (difficulty == Difficulty::EASY)
	{
		Sleep(130);
	}
	else if (difficulty == Difficulty::MEDIUM)
	{
		Sleep(100);
	}
	else if (difficulty == Difficulty::HARD)
	{
		Sleep(70);
	}
}