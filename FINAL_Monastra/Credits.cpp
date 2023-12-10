#include "Credits.h"

#include "Utilities.h"

HANDLE creditsHandle;

void GetCreditsInput(Screen& currentScreen);

void InitCredits()
{
	creditsHandle = GetStdHandle(STD_OUTPUT_HANDLE);
}

void CreditsUpdate(Screen& currentScene)
{
	GetCreditsInput(currentScene);
}

void CreditsDrawing()
{
	SetConsoleCursorPosition(creditsHandle, { 0,5 });

	cout << "    ___      ___      __      ________   _______     _______ ___  ___                             " << endl;
	cout << "   |'  \\    /'  |    /''\\    |'      '\\ /'     '|   |   _  '|'  \\/'  |                            " << endl;
	cout << "    \\   \\  //   |   /    \\   (.  ___  :(: ______)   (. |_)  :\\   \\  /                             " << endl;
	cout << "    /\\\\  \\/.    |  /' /\\  \\  |: \\   ) ||\\/    |     |:     \\/ \\\\  \\/                              " << endl;
	cout << "   |: \\.        | //  __'  \\ (| (___\\ ||// ___)_    (|  _  \\\\ /   /                               " << endl;
	cout << "   |.  \\    /:  |/   /  \\\\  \\|:       :(:      '|   |: |_)  :/   /                                " << endl;
	cout << "   |___|\\__/|___(___/    \\___(________/ \\_______)   (_______|___/                                 " << endl;
	cout << "                                                                                                  " << endl;
	cout << "    ___      ___      __ ___________ _______   ______       ___      ___ __    __   ___  ______   " << endl;
	cout << "   |'  \\    /'  |    /''('     _   '/'     '| /    ' \\     |'  \\    /'  |' \\  |/'| /  ')/    ' \\  " << endl;
	cout << "    \\   \\  //   |   /    )__/  \\\\__(: ______)// ____  \\     \\   \\  //  /||  | (: |/   /// ____  \\ " << endl;
	cout << "    /\\\\  \\/.    |  /' /\\  \\ \\\\_ /   \\/    | /  /    ) :)     \\\\  \/. ./ |:   |    __//  /    ) :)" << endl;
	cout << "   |: \\.        | //  __'  \\|.  |   // ___)(: (____/ //       \\.    //  |.  | (//    (: (____/ // " << endl;
	cout << "   |.  \\    /:  |/   /  \\\\  \\:  |  (:      '\\        /         \\\\   /   /\\  | |: | \\  \\        /  " << endl;
	cout << "   |___|\\__/|___(___/    \\___\\__|   \\_______)\\'_____/           \\__/   (__\\_| (__|  \\__\\'_____/   " << endl;
	cout << "                                                                                                  " << endl;
	cout << "    ___      ___    ______   _____  ___       __       ________ ___________ _______       __      " << endl;
	cout << "   |'  \\    /'  |  /    ' \ (\'   \\|'  \        /''\\     /'       ('     _   '/'      \\     /''\\     " << endl;
	cout << "    \\   \\  //   | // ____  \|. \\    \\    |   /    \\   (:   \\___/ )__/  \\\\__|:        |   /    \\    " << endl;
	cout << "    /\\\\  \\/.    |/  /    ) :|: \\.   \\\\  |  /' /\\  \\   \\___  \\      \\\\_ /  |_____/   )  /' /\\  \\   " << endl;
	cout << "   |: \\.        (: (____/ //|.  \\    \\. | //  __'  \\   __/  \\\\     |.  |   //      /  //  __'  \\  " << endl;
	cout << "   |.  \\    /:  |\\        / |    \\    \\ |/   /  \\\\  \\ /' \\   :)    \\:  |  |:  __   \\ /   /  \\\\  \\ " << endl;
	cout << "   |___|\\__/|___| \\'_____/   \\___|\\____\\(___/    \\___(_______/      \\__|  |__|  \\___(___/    \\___)" << endl;
	cout << endl << endl << endl << "                           PRESS ESCAPE TO GO BACK TO THE MENU                                     " << endl;

}

void GetCreditsInput(Screen& currentScreen)
{
	if (_kbhit())
	{
		char input = toupper(_getch());

		if (input == (char)KEY_ESC)
		{ 
			currentScreen = Screen::Menu;
			system("cls");
		}
	}

}