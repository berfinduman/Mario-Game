#pragma once
#include "Common.h"
 

class Mario :public Object, public ScoreBoard 
{
public: 
	
	Mario(RenderWindow* window);

	void move(Directions dir);
	void fall(void);
	void jump(bool down);
	void draw(RenderWindow& window);

	Sprite brickSprite[7];
	Sprite pipeSprite[4];

	float prev_y = 0.0f;
	Directions DirJ;

	//sliding effect bonus 1
	float prev_x_for_sliding = 0.0f;
	int consecutiveEventCount = 0;
	Keyboard::Key consecutiveEvent = Keyboard::Down;
	Keyboard::Key slideDirection = Keyboard::Down;// temp definiton for initalize
	void consecutiveControl(Keyboard::Key key);

	bool atJumpingState = false;
	bool atSlidingState = false;
	bool atFallingState = false;
		

	bool willHittedTheBrick();
	bool checkBoundary();

};

