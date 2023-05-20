#include  "Object.h"

Object::Object(RenderWindow* window) {
	this->window = window;
	next = NULL;
	//setPosition(this->pos);
	//draw(*window);


}
void Object::setPosition(Vector2f pos)
{
	
	this->pos = pos; //not needed 
	sprite.setPosition(pos);
	
	//cout << "set position." << pos.x << pos.y;
}

void Object::draw(RenderWindow& window)
{
	//cout << pos.x << pos.y; for check
	//sprite.move(0, 10);
	window.draw(sprite);
}
Vector2f Object::getPosition(void)
{
	return sprite.getPosition();
}
void Object::setAngle(Vector2f pos, float angle)
{	
	sprite.setOrigin(sprite.getTextureRect().width/2.f, sprite.getTextureRect().height / 2.f) ;
	sprite.setRotation(angle);
	setPosition(pos);
	
}

void Object::setSpeed(float x, float y) 

{
	vx = x; 
	vy = y;
}
Vector2f Object::getSpeed(void)
{
	return Vector2f(vx, vy);
}

void Object::jump(bool down) 
{
	
}


void Object::fall(void)
{
	
}


