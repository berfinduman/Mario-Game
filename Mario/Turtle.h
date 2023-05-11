#pragma once
#include "Common.h"
class Turtle : public Object {
	float vx;
	float vy;

public:
	Turtle(RenderWindow* window);
	void move(Directions dir);
	//void move(void); 
	void fall(void); 
	void jump(bool down);

};
