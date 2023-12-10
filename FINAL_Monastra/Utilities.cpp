#include "Utilities.h"

void SetConsoleSize(ConsoleData& consoleData, bool isForMenu)
{
	if (!isForMenu)
	{
	consoleData.coord.X = consoleData.gameConsoleWide; 
	consoleData.coord.Y = consoleData.gameConsoleHeight;
	}
	else
	{
		consoleData.coord.X = consoleData.menuConsoleWide;
		consoleData.coord.Y = consoleData.menuConsoleHeight;
	}

	consoleData.rect.Top = 0;
	consoleData.rect.Left = 0;
	consoleData.rect.Bottom = consoleData.coord.Y - 1;
	consoleData.rect.Right = consoleData.coord.X - 1;

	consoleData.hwnd = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleScreenBufferSize(consoleData.hwnd, consoleData.coord);
	SetConsoleWindowInfo(consoleData.hwnd, TRUE, &consoleData.rect);

	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleData.cci);
	consoleData.cci.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleData.cci);
}

void SetConsoleFont(int size)
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;

	cfi.dwFontSize.X = size;
	cfi.dwFontSize.Y = size;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;

	wcscpy_s(cfi.FaceName, L"Lucida Console");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void DrawFrame(ConsoleData& consoleData, int delay)
{
	consoleData.cursorPosition = { 0,0 };

	SetConsoleCursorPosition(consoleData.hwnd, consoleData.cursorPosition);
	cout << (char)201;

	for (int i = 0; i < (consoleData.gameConsoleWide - 2); i++)
	{
		cout << (char)205;
	}

	cout << (char)187;

	consoleData.cursorPosition.X = consoleData.gameConsoleWide - 1;
	consoleData.cursorPosition.Y = 1;

	for (int i = 0; i < (consoleData.gameConsoleHeight - 2); i++)
	{
		SetConsoleCursorPosition(consoleData.hwnd, consoleData.cursorPosition);
		cout << (char)186;
		consoleData.cursorPosition.Y++;
	}

	SetConsoleCursorPosition(consoleData.hwnd, consoleData.cursorPosition);

	cout << (char)188;

	consoleData.cursorPosition.X--;
	SetConsoleCursorPosition(consoleData.hwnd, consoleData.cursorPosition);

	for (int i = 0; i < (consoleData.gameConsoleWide - 2); i++)
	{
		cout << (char)205;
		consoleData.cursorPosition.X--;
		SetConsoleCursorPosition(consoleData.hwnd, consoleData.cursorPosition);
	}

	SetConsoleCursorPosition(consoleData.hwnd, consoleData.cursorPosition);

	cout << (char)200;

	consoleData.cursorPosition.Y--;
	SetConsoleCursorPosition(consoleData.hwnd, consoleData.cursorPosition);

	for (int i = 0; i < (consoleData.gameConsoleHeight - 2); i++)
	{
		cout << (char)186 << endl;
		consoleData.cursorPosition.Y--;
		SetConsoleCursorPosition(consoleData.hwnd, consoleData.cursorPosition);
	}
}

void DeltaTime()
{
	Sleep(100);
}