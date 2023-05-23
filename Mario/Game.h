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
	Text textfinish;
	Sprite floorSprite;
	Texture Pipe[2]; 
	Texture newBrick; 
	Sprite pipeSprite[4];
	Texture Brick;
	Sprite* hitSprite;
	Sprite brickSprite[7];
	Texture LiveMario;
	Sprite *liveSprite[3];
	int prevKeyCode; 
	int deneme = 2;

	int appear_turtle;
	int temp_appear = 0;
	int n_turtle = 0;


	int speed=10;
	int initial_live_s = 10;
	Object* objects; 
	int heading;
	
public:      
	Game(RenderWindow* window); //constructor 
	Turtle* addTurtle(int heading);		
	Mario* addMario(void);
	Turtle* turtle;
	Mario* mario;
	void update(void);
	void drawBackground(RenderWindow& window);
	void drawObjects(void);
	void removeObjects(Object*);
	bool checkBoundary(Object* obj);
	void checkHitTheBrickFromButtom(Object* obj);
	bool checkCollusionwBrick(Object* obj);
	bool checkCollusion(Turtle* t, Mario* m, int& side);
	void marioColsWithTurtle(Mario* mario);
	void checkTheScore(void);
	void checkTurtleHittedFromBottom(void);

	void checkTurtlesCollusion(Object* obj);

	FloatRect rect_turtle;
	FloatRect rect_t;
	
	bool onFloor(Object* obj); //Checks if object is touching a floor surface
	//bool checkCollusion(Turtle *t, Mario *m, int& side); ////Checks if Mario has hit a turtle and from which side
	~Game();

};

