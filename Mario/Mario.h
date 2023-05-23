#pragma once
#include "Common.h"
 

class Mario :public Object, public ScoreBoard 
{

public: 
	
	Mario(RenderWindow* window);
	void move(Directions dir);
	//void move(void); //Abstract method that will be overridden 
	void fall(void); //Abstract method that will be overridden 
	void jump(bool down);
	void draw(RenderWindow& window);

	float prev_y = 0.0f;
	float prev_x_for_sliding = 0.0f;
	bool atJumpingState=false;
	bool atSlidingState = false;
	bool atFallingState = false;
	Directions DirJ;

	int consecutiveEventCount = 0;
	Keyboard::Key consecutiveEvent = Keyboard::Down;
	Keyboard::Key scateDirection = Keyboard::Down;// temp definiton for initalize
	bool changedDirection = false;
	void consecutiveControl(Keyboard::Key key);
	bool willHittedTheBrick();
	bool checkBoundary();
	Sprite brickSprite[7];
	Sprite pipeSprite[4];
};

