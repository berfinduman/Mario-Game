#include "Mario.h"
//heading 0 is left
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
	
	state = 0;
	speed = 15;
	check_right = 1;

	sprite.setTexture(textures[state]); 
	sprite.setOrigin(sprite.getTextureRect().width / 2.0f, sprite.getTextureRect().height);
	
	heading = 1;
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
			setSpeed(speed, 0);
			sprite.move(vx, vy);
			state =2;
			//cout << "State 0dan " << state << endl;
		}

		if (dir ==JUMPR)
		{
			//cout << "Girdi";
			check_right = 1;
			jump(false);
			setSpeed(3*speed, 0);
			sprite.move(vx, vy);
			state = 5;
			//cout << "State 0dan " << state << endl;
		}
		if (dir == JUMPL)
		{
			//cout << "Girdi";
			check_right = 0;
			jump(false);
			setSpeed(-3 * speed, 0);
			sprite.move(vx, vy);
			state = 5;
			//cout << "State 0dan " << state << endl;
		}


		if (dir == LEFT)
		{

			check_right = 0;
			setSpeed(-speed, 0);
			sprite.move(vx, vy);
			state = 2;

			//cout << "State 0dan " << state << endl;
		}
		if (dir == UP)
		{
			

			//sprite.move(Vector2f(90, -float(window->getSize().y)/4.f));
			//cout << window->getSize().x<< endl;
			cout << "Neler oluyor"<< endl;
			//cout << float(window->getSize().y) << endl;
			//sprite.move(Vector2f(0, -75));

			prev_y = sprite.getPosition().y;
			state = 5;
			//cout << float(this->window->getSize().y) << endl;
			//cout << "State 0dan " << state << endl;
		}


		
		


	break;
	case 1:

		if (dir == RIGHT)
		{

			check_right = 1;

			setSpeed(speed, 0);
			sprite.move(vx, vy);
			state = 0;

			//cout << "State 2den " << state << endl;
		}

		if (dir == LEFT)
		{

			check_right = 0;
			setSpeed(-speed, 0);
			sprite.move(vx, vy);
			state = 0;
			//cout << "State 2den " << state << endl;

		}
		

	break;

	case 2:

		if (dir == RIGHT)
		{

			check_right = 1;

			setSpeed(speed, 0);
			sprite.move(vx, vy);
			state = 3;

			//cout << "State 2den " << state << endl;
		}

		if (dir == LEFT)
		{

			check_right = 0;
			setSpeed(-speed, 0);
			sprite.move(vx, vy);
			state = 3;
			//cout << "State 2den " << state << endl;

		}
	

	break;
	case 3:

		if (dir == RIGHT)
		{

			check_right = 1;
			setSpeed(speed, 0);
			sprite.move(vx, vy);
			state = 1;
			//cout << "State 3den " << state << endl;
		}
		if (dir == LEFT)
		{

			check_right = 0;
			setSpeed(-speed, 0);
			sprite.move(vx, vy);
			state = 1;
			//cout << "State 3den " << state << endl;

		}
	

	break;
	
	case 4:

	break;
	/*
	case 5:
		//cout << "now " << dir << "before"<< prevDir;
		if (prevDir == UP)
		{ 
		//sprite.move(Vector2f(-90, float(window->getSize().y) / 4.f));
		setSpeed(0, 120);
		sprite.move(vx, vy);

		//cout << "State 0dan " << state << endl;
		}
		else if (prevDir == JUMPR)
		{
			//cout <<"*---*-*--*-*-**-*-*-*-*-*-*-**-*--*";
		setSpeed(3 * speed, 120);
		sprite.move(vx, vy);

		}
		else if (prevDir == JUMPL)
		{
			//cout <<"*---*-*--*-*-**-*-*-*-*-*-*-**-*--*";
			setSpeed(-3 * speed, 120);
			sprite.move(vx, vy);

		}
		
		state = 0;
	break;*/
	

};


	
	if (check_right!=heading)
	{ 
		if(check_right){
		sprite.setScale(-1.f, 1.f);
		//sprite.move(Vector2f(float(textures[state].getSize().x), 0));
		}
	else {
		//sprite.move(Vector2f(-float(textures[state].getSize().x), 0));
		sprite.setScale(1.f, 1.f);
	}}
	sprite.setTexture(textures[state]);
	//cout << "Right" << heading << "Check" << check_right << endl;
	heading= check_right;
	
	
}

void Mario::jump(bool down)
{
	float y_vel = 9.8 * 10 / 5.0f;
	if (down)
	{
		
		setSpeed(0, y_vel);
		sprite.move(vx, vy);
	}

	else
	{
		setSpeed(0, -y_vel);
		sprite.move(vx, vy);
	}

}
void Mario::draw(RenderWindow& window)
{
	
	if (state==5)
	{
		atJumpingState = true;
		//if (DirJ == RIGHT)sprite.move(50, 0);
		sprite.setTexture(textures[state]);
		//cout << "PrevY :   " << prev_y << "NowY " << sprite.getPosition().y <<"FARK   " << sprite.getPosition().y - prev_y  << endl;
		
		if (0<=(prev_y -sprite.getPosition().y) and (prev_y - sprite.getPosition().y) <100)
		{ 
			if (DirJ == LEFT) sprite.move(-50, 0);
			if (DirJ == RIGHT)sprite.move(50, 0);
		jump(false);
		cout << "PrevY :   " << prev_y << "NowY " << sprite.getPosition().y <<"FARK   " << prev_y - sprite.getPosition().y << endl;

		}
		else if (prev_y - sprite.getPosition().y >= 100)
		{
			if (DirJ == RIGHT)sprite.move(-50, 0);
			if (DirJ == LEFT) sprite.move(+50, 0);
			prev_y = sprite.getPosition().y-1;
			cout << "Else" << prev_y << endl;
		}

		if (prev_y - sprite.getPosition().y < 0.0f)
		{

			jump(true);
			cout << "TRUEPrevY :   " << prev_y << "NowY " << sprite.getPosition().y << "FARK   " << prev_y - sprite.getPosition().y << endl;

		}
		if (prev_y - sprite.getPosition().y < -100.0f)
		{
			atJumpingState = false;

			state = 0;
			sprite.setTexture(textures[state]);
		}


	}
	window.draw(sprite);

}