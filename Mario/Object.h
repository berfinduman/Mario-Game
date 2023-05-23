#pragma once
#include "Common.h"

using namespace sf;
class Object {

	Vector2f pos;
	Object* next; 
	friend class Game; 

protected:	

	bool hittedBrick = false;
	RenderWindow* window; 
	float jumpHeight = 250.0f;
	int heading = 0; //facing direction of object 
	float vx;
	float vy;
	Texture textures[8];
	Sprite sprite;

	//turtle
	bool isMeetTurtle=false; 
	int meetingTime = 10; 
	bool fallTurtle=false; 
	bool checkTurtleCollusionable = true; 

public: 
	enum Directions 
	{
		UP, 
		DOWN,
		LEFT,
		RIGHT,
		STABLE,
		JUMPR,
		JUMPL
	};
	int state;
	int right ; 
	int check_right;
	int speed; 
	Object(RenderWindow* window);
	void setPosition(Vector2f pos);
	Vector2f getPosition();
	IntRect boundingBox(void);
	virtual void draw(RenderWindow& window);
	bool atJumpingState=false;
	virtual void fall(void);
	void setAngle(Vector2f pos, float);
	virtual ~Object() {};
	void setSpeed(float x, float y);
	virtual void jump(bool down);
	Vector2f getSpeed(void); 
	int initial_jumping_mario=0;
	float prev_y = 0.0f;
	bool checkCollusionBrick = false; 






};