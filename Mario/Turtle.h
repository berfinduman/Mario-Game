#pragma once
#include "Common.h"

class Turtle : public Object {

public:

	Turtle(RenderWindow* window);

	bool deathFall=true;

	//bonus  3
	int turtleBottomHittedJumpTime = 4;
	int turtleBottomHittedWaitingTime=80;

	void draw(RenderWindow& window);
	void jump(bool down);
	void fall(void) ; 
	

	

};
  