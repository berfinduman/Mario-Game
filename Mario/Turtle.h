#pragma once
#include "Common.h"

class Turtle : public Object {
protected:
	

public:
	Turtle(RenderWindow* window);
	
	//virtual void move(void); 
	void fall(void) ; 
	bool deathFall=true;
	int bonusjumptime = 4;
	//auto t_start;

	int bonustime=80;
	void draw(RenderWindow& window);
	void jump(bool down);
	

	

};
  