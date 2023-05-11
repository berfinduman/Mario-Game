#pragma once
#include "Common.h"

using namespace sf;
class Object {
	Vector2f pos;

protected:	
	
	RenderWindow* window; 
	int state; //Current animation state of the object (one of animation states)
	int heading; //Facing direction of object

	Texture textures[8];
	Sprite sprite;
public: 
	enum Directions 
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};
	int right ; 
	int check_right;
	int speed;
	Object(RenderWindow* window);
	void setPosition(Vector2f pos);
	Vector2f getPosition();
	IntRect boundingBox(void);
	void draw(RenderWindow& window);
	void move(Directions dir); //Abstract method that will be overridden 
	void fall(void); //Abstract method that will be overridden 
	void jump(bool down); //Abstract method that will be overridden 







};