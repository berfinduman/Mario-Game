#include  "Object.h"

Object::Object(RenderWindow* window) {
	this->window = window;
	next = NULL;
}
void Object::setPosition(Vector2f pos)
{
	this->pos = pos; 
	sprite.setPosition(pos);
}

void Object::draw(RenderWindow& window)
{
	window.draw(sprite);
}
Vector2f Object::getPosition(void)
{
	return sprite.getPosition();
}
void Object::setAngle(Vector2f pos, float angle)
{	
	sprite.setOrigin(
		sprite.getTextureRect().width/2.f,
		sprite.getTextureRect().height / 2.f);

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


