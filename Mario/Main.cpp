#include "Common.h"
#include "Game.h"
#include "Menu.h"
#include <Windows.h>
/*

	 sf::RenderWindow window(sf::VideoMode (1024,768), "Mario Game");
	 sf::Texture texture_floor;
	 if (!texture_floor.loadFromFile("../assets/floor.png"))
	 {
		 cout << "File could not be found" << endl;
	 }
	 sf::Sprite sprite;
	 sprite.setTexture(texture_floor);
	while (window.isOpen())
	{


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		sprite.setPosition(0, 680);
		window.draw(sprite);
		window.display();
*/
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