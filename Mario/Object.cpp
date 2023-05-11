#include  "Object.h"

Object::Object(RenderWindow* window) {
	this->window = window;
	//setPosition(this->pos);
	//draw(*window);


}
void Object::setPosition(Vector2f pos)
{
	this->pos = pos;
	sprite.setPosition(pos);
	//cout << "set position." << pos.x << pos.y;
}

void Object::draw(RenderWindow& window)
{
	//cout << pos.x << pos.y; for check
	window.draw(sprite);
}