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
	int appear_turtle;
	int temp_appear = 0;
	int n_turtle = 0;
	
	//Mario* mario; 
	//Turtle* turtle;
	ScoreBoard scoreboard;
	int speed=10;
	int initial = 10;
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
	
	bool onFloor(Object* obj); //Checks if object is touching a floor surface
	//bool checkCollusion(Turtle *t, Mario *m, int& side); ////Checks if Mario has hit a turtle and from which side
	~Game();

};

