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
	}
}