#pragma once
#include "Common.h"
 
class Mario:public Object {
	float vx=0;
	float vy=0;
public: 
	
	Mario(RenderWindow* window);
	void move(Directions dir);
	//void move(void); //Abstract method that will be overridden 
	void fall(void); //Abstract method that will be overridden 
	void jump(bool down);
};