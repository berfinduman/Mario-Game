#include "Common.h"
#include "Game.h"
#include "Menu.h"
#include <Windows.h>
int main()
{
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_MINIMIZE); // minimize window when exe runned

	RenderWindow* menuWindow;
	menuWindow= new RenderWindow(VideoMode(1920, WINDOW_HEIGHT), "Menu");

	Menu menu(menuWindow);
	menu.update();
	
	exit(0);
}