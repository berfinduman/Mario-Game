#pragma once
#include "Common.h"
#include "Mario.h"
#include "Turtle.h"
#include "ScoreBoard.h"

class Menu
{
	RenderWindow* menuWindow; //pointer
	Font font;
	Text text[2];
	bool start;
	Texture marioHead;
	Sprite marioHeadSprite;
	Texture backGround;
	Sprite backGroundSprite;

public:
	Menu(RenderWindow* menuWindow); //constructor 
	void update(void);
	void drawBackground();
	bool getStarted();
	//bool onFloor(Object* obj); //Checks if object is touching a floor surface
	//bool checkCollusion(Turtle *t, Mario *m, int& side); ////Checks if Mario has hit a turtle and from which side
	~Menu();




};