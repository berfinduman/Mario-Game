#pragma once
#include "Common.h"
 

class Mario :public Object, public ScoreBoard 
{
protected:

	

public: 
	
	Mario(RenderWindow* window);
	void move(Directions dir);
	//void move(void); //Abstract method that will be overridden 
	void fall(void); //Abstract method that will be overridden 
	void jump(bool down);
	void draw(RenderWindow& window);

	float prev_y = 0.0f;
	float prev_x = 0.0f;
	bool atJumpingState=false;
	bool atScatingState = false;
	Directions DirJ;

	int consecutiveEventCount = 0;
	Keyboard::Key consecutiveEvent = Keyboard::Down;
	Keyboard::Key scateDirection = Keyboard::Down;// temp definiton for initalize
	bool changedDirection = false;
	void consecutiveControl(Keyboard::Key key);

};

