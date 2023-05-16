#pragma once
#include "Common.h"
 
class Mario:public Object {
protected:
	
public: 
	
	Mario(RenderWindow* window);
	void move(Directions dir);
	//void move(void); //Abstract method that will be overridden 
	void fall(void); //Abstract method that will be overridden 
	void jump(bool down);
	void draw(RenderWindow& window);
	float prev_y = 0.0f;
	bool atJumpingState=false;
	Directions DirJ;
	
};

