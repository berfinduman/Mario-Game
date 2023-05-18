#pragma once
#include "Common.h"

using namespace sf;
class Object {
	Vector2f pos;
	Object* next; 
	friend class Game; 

protected:	
	
	RenderWindow* window; 
	float jumpHeight = 250.0f; //mario
	 //Current animation state of the object (one of animation states)
	int heading=0; //Facing direction of object 
	float vx;
	float vy;
	Texture textures[8];
	Sprite sprite;
	bool headOnTurtle=false; //turtle
	int headingTime = 10; //turtle
	bool fallTurtle=false; //turtle
	bool checkTurtleCollusionable = true; //turtle
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
	int check_right; //mario
	int speed; 
	Object(RenderWindow* window);
	void setPosition(Vector2f pos);
	Vector2f getPosition();
	IntRect boundingBox(void);
	virtual void draw(RenderWindow& window);
	bool atJumpingState=false; //mario
	//void move(Directions dir); //Abstract method that will be overridden 
	void fall(void); //Abstract method that will be overridden 
	//virtual void jump(bool down); //Abstract method that will be overridden
	void setAngle(Vector2f pos, float);
	virtual ~Object() {


	}
	void setSpeed(float x, float y);
	virtual void jump(bool down);
	Vector2f getSpeed(void); 
	int initial_jumping_mario=0;
	float prev_y = 0.0f;
	bool checkCollusionBrick = false; 






};