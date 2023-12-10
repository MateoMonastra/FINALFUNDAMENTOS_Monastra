#include "ScreenManager.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Screen.h"
#include "Game.h"
#include "Menu.h"
#include "Credits.h"

Screen currentScreen;

static void InitProgram();
static void Update();
static void Draw();
static void Close();


void RunProgram()
{
	InitProgram();

	while (currentScreen != Screen::Exit)
	{
		Draw();
		Update();
	}

	Close();
}

static void InitProgram()
{
	currentScreen = Screen::Game;

	srand(time(NULL));
	
	//InitMenu();
	InitGame();
}

static void Update()
{

	switch (currentScreen)
	{
	case Screen::Menu:
		MenuUpdate(currentScreen);
		break;
	case Screen::Game:
		GameUpdate(currentScreen);
		break;
	case Screen::Credits:
		CreditsUpdate(currentScreen);
		break;
	case Screen::Exit:
		Close();
		break;
	default:
		break;
	}

}

static void Draw()
{

	switch (currentScreen)
	{
	case Screen::Menu:
		MenuDrawing();
		break;
	case Screen::Game:
		GameDrawing();
		break;
	case Screen::Credits:
		CreditsDrawing();
		break;
	default:
		break;
	}
}

static void Close()
{
	exit;
}