#include "Common.h"
#include "Game.h"
#include "Menu.h"
#include <Windows.h>
int main()
{
	try {
		HWND hWnd = GetConsoleWindow();
		ShowWindow(hWnd, SW_MINIMIZE); // minimize window when exe runned

		RenderWindow* menuWindow;
		menuWindow = new RenderWindow(VideoMode(1920, WINDOW_HEIGHT), "Menu");
		menuWindow->create(sf::VideoMode::getFullscreenModes()[0], "SFML Pencere", sf::Style::Fullscreen);

		Menu menu(menuWindow);
		menu.update();
		exit(0);
	}
	catch (const char* msg)
	{

		cout << msg << endl;
	}
}