#include "Mario.h"

Mario::Mario(RenderWindow *window):Object(window)
{
	/*if (!textures[0].loadFromFile("../assets/pipe.png")) //We added exception later on
	{
		cout << "File could not be found" << endl;
	}
	*/
	char path[64];
	for (int i = 0; i < size(textures)-1; i++)
	{
		sprintf(path, "../assets/mario%d.png", (i+1));
		cout << path;
		if (!textures[i].loadFromFile(path)) //We added exception later on
		{
			cout << "File could not be found" << endl;
		}

	}
	speed = 8;
	state = 0;
	check_right = 1;

	sprite.setTexture(textures[state]); 
	right = 1;
	sprite.setScale(-1.f, 1.f);
}
void Mario::move(Directions dir)
{
	switch (state)
	{
	case 0:
		if (dir == RIGHT)
		{

			check_right = 1;
			sprite.move(Vector2f(speed, 0));
			state =2;
			cout << "State 0dan " << state << endl;
		}

		if (dir == LEFT)
		{

			check_right = 0;
			sprite.move(Vector2f(-speed, 0));
			state = 2;

			cout << "State 0dan " << state << endl;
		}
		if (dir == UP)
		{
			sprite.move(Vector2f(0, -speed*5));
			state = 5;

			cout << "State 0dan " << state << endl;
		}


		if (dir == STABLE) state = 0;	
		


	break;
	case 1:

		if (dir == RIGHT)
		{

			check_right = 1;

			sprite.move(Vector2f(speed, 0));
			state = 0;

			cout << "State 2den " << state << endl;
		}

		if (dir == LEFT)
		{

			check_right = 0;
			sprite.move(Vector2f(-speed, 0));
			state = 0;
			cout << "State 2den " << state << endl;

		}
		if (dir == STABLE) state = 0;

	break;

	case 2:

		if (dir == RIGHT)
		{

			check_right = 1;

			sprite.move(Vector2f(speed, 0));
			state = 3;

			cout << "State 2den " << state << endl;
		}

		if (dir == LEFT)
		{

			check_right = 0;
			sprite.move(Vector2f(-speed, 0));
			state = 3;
			cout << "State 2den " << state << endl;

		}
		if (dir == STABLE) state = 0;

	break;
	case 3:

		if (dir == RIGHT)
		{

			check_right = 1;
			sprite.move(Vector2f(speed, 0));
			state = 1;
			cout << "State 3den " << state << endl;
		}
		if (dir == LEFT)
		{

			check_right = 0;
			sprite.move(Vector2f(-speed, 0));
			state = 1;
			cout << "State 3den " << state << endl;

		}
		if (dir == STABLE) state = 0;

	break;
	
	case 4:

	break;
	case 5:
		sprite.move(Vector2f(0, speed * 5));
		state = 0;

		cout << "State 0dan " << state << endl;
	
	break;


};


	
	if (check_right!=right)
	{ 
		if(check_right){
		sprite.setScale(-1.f, 1.f);
		sprite.move(Vector2f(float(textures[state].getSize().x), 0));
		}
	else {
		sprite.move(Vector2f(-float(textures[state].getSize().x), 0));
		sprite.setScale(1.f, 1.f);
	}}
	sprite.setTexture(textures[state]);
	cout << "Right" << right << "Check" << check_right << endl;
	right= check_right;
	
	
}