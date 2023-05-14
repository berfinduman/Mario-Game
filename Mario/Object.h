#pragma once
#include "Common.h"

using namespace sf;
class Object {
	Vector2f pos;
	Object* next; 
	friend class Game; 

protected:	
	
	RenderWindow* window; 
	int state; //Current animation state of the object (one of animation states)
	int heading=0; //Facing direction of object
	float vx;
	float vy;
	Texture textures[8];
	Sprite sprite;
public: 
	enum Directions 
	{
		UP, 
		DOWN,
		LEFT,
		RIGHT,
		STABLE,
		JUMPR
	};
	int right ; 
	int check_right;
	int speed;
	Object(RenderWindow* window);
	void setPosition(Vector2f pos);
	Vector2f getPosition();
	IntRect boundingBox(void);
	virtual void draw(RenderWindow& window);
	//void move(Directions dir); //Abstract method that will be overridden 
	void fall(void); //Abstract method that will be overridden 
	//virtual void jump(bool down); //Abstract method that will be overridden
	void setAngle(Vector2f pos, float);
	virtual ~Object() {


	}
	void setSpeed(float x, float y);






};