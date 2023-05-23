#pragma once
#include "Common.h"
#include "Mario.h"
#include "Turtle.h"
#include "ScoreBoard.h"

class Game
{
	RenderWindow* window;
	Object* objects;

	Font font;
	Text text;
	Text textfinish;
	
	Texture floor; 
	Sprite floorSprite;

	Texture Pipe[2]; 
	Sprite pipeSprite[4];

	Texture newBrick; 
	Texture Brick;
	Sprite brickSprite[7];

	Sprite* hitSprite;

	Texture LiveMario;
	Sprite *liveSprite[3];

	//flags
	int prevKeyCode; 
	int deneme = 2;
	int appear_turtle;
	int temp_appear = 0;
	int n_turtle = 0;
	int speed=10;
	int initial_live_s = 10;
	int heading;
	
public:     
	FloatRect rect_turtle;
	FloatRect rect_t;

	Turtle* turtle;
	Mario* mario;

	Game(RenderWindow* window);

	Turtle* addTurtle(int heading);		
	Mario* addMario(void);

	void update(void);
	void drawBackground(RenderWindow& window);
	void drawObjects(void);
	void removeObjects(Object*);
	void checkHitTheBrickFromButtom(Object* obj);
	void marioColsWithTurtle(Mario* mario);
	void checkTheScore(void);
	void checkTurtleHittedFromBottom(void);
	void checkTurtlesCollusion(Object* obj);

	bool checkBoundary(Object* obj);
	bool checkCollusionwBrick(Object* obj);
	bool checkCollusion(Turtle* t, Mario* m, int& side);
	bool onFloor(Object* obj);
	
	~Game();

};

