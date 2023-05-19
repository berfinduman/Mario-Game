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
	speed = 10;
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
			//sprite.move(vx, vy);
			state =2;
			//cout << "State 0dan " << state << endl;
		}

		

		if (dir == LEFT)
		{

			check_right = 0;
			setSpeed(-speed, 0);
			//sprite.move(vx, vy);
			state = 2;

			//cout << "State 0dan " << state << endl;
		}
		/*
		if (dir == UP)
		{
			

			//sprite.move(Vector2f(90, -float(window->getSize().y)/4.f));
			//cout << window->getSize().x<< endl;
			//cout << float(window->getSize().y) << endl;
			//sprite.move(Vector2f(0, -75));

			prev_y = sprite.getPosition().y;
			state = 5;
			//cout << float(this->window->getSize().y) << endl;
			//cout << "State 0dan " << state << endl;
		}*/

	break;
	case 1:

		if (dir == RIGHT)
		{

			check_right = 1;

			setSpeed(speed, 0);
			//sprite.move(vx, vy);
			state = 0;

			//cout << "State 2den " << state << endl;
		}

		if (dir == LEFT)
		{

			check_right = 0;
			setSpeed(-speed, 0);
			//sprite.move(vx, vy);
			state = 0;
			//cout << "State 2den " << state << endl;

		}
		

	break;

	case 2:

		if (dir == RIGHT)
		{

			check_right = 1;

			setSpeed(speed, 0);
			//sprite.move(vx, vy);
			state = 3;

			//cout << "State 2den " << state << endl;
		}

		if (dir == LEFT)
		{

			check_right = 0;
			setSpeed(-speed, 0);
			//sprite.move(vx, vy);
			state = 3;
			//cout << "State 2den " << state << endl;

		}
	

	break;
	case 3:

		if (dir == RIGHT)
		{

			check_right = 1;
			setSpeed(speed, 0);
			
			state = 1;
			//cout << "State 3den " << state << endl;
		}
		if (dir == LEFT)
		{

			check_right = 0;
			setSpeed(-speed, 0);
			//sprite.move(vx, vy);
			state = 1;
			//cout << "State 3den " << state << endl;

		}
	

	break;
	
	;
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
	sprite.move(vx, vy);
	
	
}

void Mario::fall(void)

{
	setSpeed(0, 40);
	sprite.move(vx, vy);
}




void Mario::jump(bool down)
{
	float y_vel = 9.8 * 10 / 5.0f;
	if (down) setSpeed(0, y_vel);
	else setSpeed(0, -y_vel);
	sprite.move(vx, vy);

}
void Mario::draw(RenderWindow& window){

	if (state == 6) {
		cout << "Düþüyor Mario "<<endl; 
		
		fall(); }
		
	else if (state == 5)
	{
		atJumpingState = true;
		//if (DirJ == RIGHT)sprite.move(50, 0);
		sprite.setTexture(textures[state]);

		//cout << "PrevY :   " << prev_y << "NowY " << sprite.getPosition().y <<"FARK   " << sprite.getPosition().y - prev_y  << endl;
		cout << "Girdi1" << endl;

		if (0 <= (prev_y - sprite.getPosition().y) and (prev_y - sprite.getPosition().y) < jumpHeight)
		{
			//initial_jumping_mario = 1;
			if (DirJ == RIGHT)sprite.move(10, 0);
			if (DirJ == LEFT) sprite.move(-10, 0);

			jump(false);
			cout << "Girdi2" << endl;
			cout << "PrevY :   " << prev_y << "NowY " << sprite.getPosition().y << "FARK   " << prev_y - sprite.getPosition().y << endl;

		}
		else if (prev_y - sprite.getPosition().y >= jumpHeight)
		{

			prev_y = sprite.getPosition().y - 1;
			cout << "Else" << prev_y << endl;

		}

		if (prev_y - sprite.getPosition().y < 0.0f)
		{
			if (DirJ == RIGHT)sprite.move(+20, 0);
			if (DirJ == LEFT) sprite.move(-20, 0);
			jump(true);
			cout << "TRUEPrevY :   " << prev_y << "NowY " << sprite.getPosition().y << "FARK   " << prev_y - sprite.getPosition().y << endl;

		}
		if (prev_y - sprite.getPosition().y < -jumpHeight)
		{
			cout << "Girdi3" << endl;
			atJumpingState = false;
			DirJ = STABLE;
			state = 0;
			sprite.setTexture(textures[state]);
			//initial_jumping_mario = 0;
			jumpHeight = 250;
			checkCollusionBrick = false;

		}
	}
	/*
	else if (state == 4) {
				atScatingState = true;
				sprite.setTexture(textures[state]);

				cout << prev_x << sprite.getPosition().x << "  Bunlar pozisyonlar" << endl;
				if (scateDirection == Keyboard::Right and sprite.getPosition().x - prev_x < 100)
				{
					sprite.move(10, 0);
				}
				else if (scateDirection == Keyboard::Left and prev_x - sprite.getPosition().x < 100) {
					sprite.move(-10, 0);
				}
				else
				{
					scateDirection = Keyboard::Down;
					atScatingState = false;
					consecutiveEventCount = 0;
					consecutiveEvent = Keyboard::Down;
					state = 0;
					sprite.setTexture(textures[state]);
				}

	}	
	*/	

	
	else atJumpingState = false;
	sprite.setTexture(textures[state]);
	window.draw(sprite);
}
/*
void Mario::consecutiveControl(Keyboard::Key pressedKey) {


	if (pressedKey == consecutiveEvent and pressedKey != Keyboard::Down)
	{
		consecutiveEventCount++;
	}
	else {

		if (consecutiveEventCount > 10) {
			prev_x = sprite.getPosition().x;
			state = 4;
			atScatingState = true;
			cout << "Kayma yönü consecutivve" << endl;
			cout << consecutiveEvent << endl;
			scateDirection = consecutiveEvent;
			consecutiveEvent = pressedKey;
		}
		else
		{
			consecutiveEvent = pressedKey;
			consecutiveEventCount = 1;
		}

	}
}*/