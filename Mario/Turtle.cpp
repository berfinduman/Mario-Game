#include "Turtle.h"
Turtle::Turtle(RenderWindow* window) :Object(window)
{
	{
		char path[64];
		for (int i =0; i < 5; i++)
		{
			sprintf(path, "../assets/turtle%d.png", (i+1));
			if (!textures[i].loadFromFile(path)) //We added exception later on
			{
				cout << "File could not be found" << endl;
			}

		}
		state = 0;
		sprite.setTexture(textures[state]);
		//sprite.setOrigin(sprite.getTextureRect().width / 2.0f, sprite.getTextureRect().height);

		
		
	}
}
void Turtle::draw(RenderWindow& window)
{
	
	//cout << "Girdik bir elamate";

	

	sprite.setTexture(textures[state]);
	window.draw(sprite);

	if (!heading) sprite.move(vx, vy);
	else sprite.move(-vx, vy);


	switch(state)
	{
	case 0:

		state = 1;
	break;


	case  1:
	
		state = 0;
	break;
	

	case 2:
		state = 0;
	break;
	
	}
	

}


void Turtle::jump(bool down)
{
	if (down)
	{
		sprite.move(0, 40);
	}
	else
	{


	}

}

