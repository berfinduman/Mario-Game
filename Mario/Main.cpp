#include "Common.h"
#include "Game.h"
#include "Menu.h"
#include <Windows.h>
int main()
{
	HWND hWnd = GetConsoleWindow();

	// minimize the window
	ShowWindow(hWnd, SW_MINIMIZE);
	
	RenderWindow* gamewindow;
	RenderWindow* menuWindow;
	menuWindow= new RenderWindow(VideoMode(1920, WINDOW_HEIGHT), "Menu");

	Menu menu(menuWindow);
	menu.update();
	if(menu.getStarted()) {
		menu.~Menu();
		gamewindow = new RenderWindow(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "MARIO GAME");
		Game game(gamewindow);
		game.update();
	}
	exit(0);
}