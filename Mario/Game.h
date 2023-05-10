#pragma once
#include "Common.h"
class Game
{
	RenderWindow* window; //pointer
	Texture floor; 
	Sprite floorSprite;
	Texture Pipe[4]; 
	Sprite pipeSprite[8];
	Texture Brick[80];
	Sprite brickSprite[7];
	int speed=10;
public:    
	Game(); //constructor 
	void update(void);  




};