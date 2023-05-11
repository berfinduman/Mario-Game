#pragma once
#include "Common.h"
#include "Mario.h"
#include "Turtle.h"
#include "ScoreBoard.h"

class Game
{
	RenderWindow* window; //pointer
	Texture floor; 
	Font font;
	Text text;
	Sprite floorSprite;
	Texture Pipe[2]; 
	Sprite pipeSprite[4];
	Texture Brick;
	Sprite brickSprite[7];
	Texture LiveMario;
	Sprite liveSprite[3];
	
	Mario mario; 
	Turtle turtle;
	ScoreBoard scoreboard;
	int speed=10;
	int initial = 10;
public:    
	Game(RenderWindow* window); //constructor 
	void update(void);  
	void drawBackground(RenderWindow& window);
	//bool onFloor(Object* obj); //Checks if object is touching a floor surface
	//bool checkCollusion(Turtle *t, Mario *m, int& side); ////Checks if Mario has hit a turtle and from which side
	~Game();




};