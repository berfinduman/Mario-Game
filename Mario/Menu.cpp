#include "Menu.h"
#include "Common.h"
#include "Game.h"
#pragma once
Menu::Menu(RenderWindow* window) {
	this->menuWindow = window;
	drawBackground();
}



void Menu::drawBackground() {
	if (font.loadFromFile("../assets/font.ttf") == false)
	{
		throw("Font files could not be opened!");
	}
	if (marioHead.loadFromFile("../assets/mariohead.png") == false)
	{
		throw("Textures files could not be opened!");
	}
	if (backGround.loadFromFile("../assets/background.png") == false)
	{
		throw("Textures files could not be opened!");
	}

	backGroundSprite.setTexture(backGround);
	backGroundSprite.setTextureRect(IntRect(0, 0, menuWindow->getSize().x, menuWindow->getSize().y));

	menuWindow->draw(backGroundSprite);

	text[1].setFont(font); 
	text[1].setString("1985 NINTENDO");
	text[1].setCharacterSize(80); 
	text[1].setPosition(float(menuWindow->getSize().x / 2 - text[1].getGlobalBounds().width / 2), float(menuWindow->getSize().y / 6 - text[1].getGlobalBounds().height / 2));
	text[1].setFillColor(Color().Yellow);

	text[0].setOutlineThickness(2);
	text[0].setFont(font);
	text[0].setString("Start Game");
	text[0].setCharacterSize(40); 
	text[0].setPosition(float(menuWindow->getSize().x / 2 - text[0].getGlobalBounds().width / 2), float(menuWindow->getSize().y / 2 - text[0].getGlobalBounds().height / 2));

	marioHeadSprite.setTexture(marioHead);
	marioHeadSprite.setScale(3.f, 3.f);
	marioHeadSprite.setPosition(float(menuWindow->getSize().x / 2 - marioHeadSprite.getGlobalBounds().width / 2) ,text[1].getGlobalBounds().top + text[1].getGlobalBounds().height + 50);

}


void Menu::update(void) {
	Mouse mouse;

	while (menuWindow->isOpen()) {

		Event event;
		Vector2f mouseLocation = Vector2f(mouse.getPosition(*menuWindow).x, mouse.getPosition(*menuWindow).y);

		if (text[0].getGlobalBounds().contains(mouseLocation)) {
			//text size up
			text[0].setCharacterSize(80);
			text[0].setOutlineColor(Color().Red);
			text[0].setOutlineThickness(10);
			text[0].setPosition(float(menuWindow->getSize().x / 2 - text[0].getGlobalBounds().width / 2), float(menuWindow->getSize().y / 2 - text[0].getGlobalBounds().height / 2));
		}
		else if(text[0].getCharacterSize() == 80) {//control is sized up
			//resize text
			text[0].setCharacterSize(40);
			text[0].setOutlineColor(Color().Black);
			text[0].setOutlineThickness(2);
			text[0].setOutlineThickness(0);
			text[0].setPosition(float(menuWindow->getSize().x / 2 - text[0].getGlobalBounds().width / 2), float(menuWindow->getSize().y / 2 - text[0].getGlobalBounds().height / 2));
		}


		while (menuWindow->pollEvent(event))
		{
			if (event.type == Event::Closed)
				menuWindow->close();
				
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Escape)
				{
					menuWindow->close();
				}
			}
			if (event.type == Event::MouseButtonPressed) {

				Vector2f mouseClick = Vector2f(event.mouseButton.x, event.mouseButton.y);

				if (text[0].getGlobalBounds().contains(mouseClick)) {
					//open game
					menuWindow->close();
					RenderWindow* gamewindow = new RenderWindow(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "MARIO GAME");
					Game game(gamewindow);
					game.update();

				}
			}
		

		}

		menuWindow->clear();
		menuWindow->draw(backGroundSprite);
		menuWindow->draw(text[1]);
		menuWindow->draw(marioHeadSprite);
		menuWindow->draw(text[0]);

		menuWindow->display();
		sleep(milliseconds(100)); //10 fps menu
	}

}


Menu::~Menu() 
{
	menuWindow->close();
}