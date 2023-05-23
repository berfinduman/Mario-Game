#pragma once
#include "Common.h"
#include "Mario.h"
#include "Turtle.h"
#include "ScoreBoard.h"

class Menu
{
	RenderWindow* menuWindow; 

	Font font;
	Text text[2];

	Texture marioHead;
	Sprite marioHeadSprite;

	Texture backGround;
	Sprite backGroundSprite;

public:

	Menu(RenderWindow* menuWindow);
	void update(void);
	void drawBackground();
	~Menu();

};