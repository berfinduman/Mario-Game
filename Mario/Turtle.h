#pragma once
#include "Common.h"
class Turtle : public Object {
/*protected:
	float vx;
	float vy;
*/

public:
	Turtle(RenderWindow* window);
	
	//virtual void move(void); 
	void fall(void); 
	void draw(RenderWindow& window);
	void jump(bool down);
	

};
  