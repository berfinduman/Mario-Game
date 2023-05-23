#include "Mario.h"


Mario::Mario(RenderWindow *window) :Object(window)
{
	char path[64];

	for (int i = 0; i < size(textures)-1; i++)
	{
		sprintf(path, "../assets/mario%d.png", (i+1));

		if (!textures[i].loadFromFile(path))
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
				state =2;
			}
			if (dir == LEFT)
			{
				check_right = 0;
				setSpeed(-speed, 0);
				state = 2;
			}
			break;


		case 1:

			if (dir == RIGHT)
			{
				check_right = 1;
				setSpeed(speed, 0);
				state = 0;
			}
			if (dir == LEFT)
			{
				check_right = 0;
				setSpeed(-speed, 0);
				state = 0;
			}
			break;


		case 2:

			if (dir == RIGHT)
			{
				check_right = 1;
				setSpeed(speed, 0);
				state = 3;
			}
			if (dir == LEFT)
			{
				check_right = 0;
				setSpeed(-speed, 0);
				state = 3;
			}
			break;


		case 3:

			if (dir == RIGHT)
			{
				check_right = 1;
				setSpeed(speed, 0);
				state = 1;
			}
			if (dir == LEFT)
			{
				check_right = 0;
				setSpeed(-speed, 0);
				state = 1;
			}
			break;
	
	};



	
	if (check_right!=heading)
	{ 
		if(check_right)
		{
			sprite.setScale(-1.f, 1.f);
		}
		else 
		{
			sprite.setScale(1.f, 1.f);
		}
	}

	sprite.setTexture(textures[state]);
	
	heading= check_right;
	sprite.move(vx, vy);
	
	if(atFallingState and willHittedTheBrick()) // check  did mario hit the brick from right or left side if at falling state
		sprite.move(-vx, 0);
		
}

void Mario::fall(void)
{
	setSpeed(0, 40);
	sprite.move(vx, vy);
}



void Mario::jump(bool down)
{
	float y_vel = 9.8 * 10 / 5.0f;

	if (down) 
		setSpeed(0, y_vel);
	else
		setSpeed(0, -y_vel);

	sprite.move(vx, vy);


}

void Mario::draw(RenderWindow& window){

	if (state == 6) 
	{
		fall();
	}
		
	else if (state == 5)

	{
		atJumpingState = true;
		sprite.setTexture(textures[state]);


		if (0 <= (prev_y - sprite.getPosition().y) and (prev_y - sprite.getPosition().y) < jumpHeight)
		{
			
			if (DirJ == RIGHT)
			{
				sprite.move(10, 0);

				if (willHittedTheBrick()) // check  did mario hit the brick from right or left side if he did, take back the movement
				{
					sprite.move(-10, 0);
				}
			}
			if (DirJ == LEFT)
			{
				sprite.move(-10, 0);
				if (willHittedTheBrick()) // check  did mario hit the brick from right or left side if he did, take back the movement
				{
					sprite.move(10, 0);
				}
			}
			
			jump(false);

		}
		else if (prev_y - sprite.getPosition().y >= jumpHeight)
		{
			prev_y = sprite.getPosition().y - 1;
		}

		if (prev_y - sprite.getPosition().y < 0.0f)
		{
			
			if (DirJ == RIGHT)
			{
				sprite.move(10, 0);

				if (willHittedTheBrick()) // check  did mario hit the brick from right or left side if he did, take back the movement
				{
					sprite.move(-10, 0);
				}
			}
			if (DirJ == LEFT)
			{
				sprite.move(-10, 0);

				if (willHittedTheBrick()) // check  did mario hit the brick from right or left side if he did, take back the movement
				{
					sprite.move(10, 0);
				}
			}
			
			jump(true);

		}
		if (prev_y - sprite.getPosition().y < -jumpHeight)
		{
			hittedBrick = false;
			atJumpingState = false;
			DirJ = STABLE;
			state = 0;
			sprite.setTexture(textures[state]);
			jumpHeight = 250;
			checkCollusionBrick = false;
		}

	}
	else if (state == 4)  // sliding state
	{
		sprite.setTexture(textures[state]);

		if (scateDirection == Keyboard::Right and sprite.getPosition().x - prev_x_for_sliding < 60)  // 60 is sliding distance
		{
			sprite.move(10, 0);

			if(checkBoundary()) // check  did mario hit the boundary coniditons if he did, take back the movement 
				sprite.move(-10, 0);
		}
		else if (scateDirection == Keyboard::Left and prev_x_for_sliding - sprite.getPosition().x < 60) // 60 is sliding distance
		{
			sprite.move(-10, 0);

			if (checkBoundary()) // check  did mario hit the boundary coniditons if he did, take back the movement 
				sprite.move(10, 0);
		}
		else 
		{	//reset coniditons for stop
			scateDirection = Keyboard::Down; // stable condition variable is down
			atSlidingState = false;
			consecutiveEventCount = 0;
			consecutiveEvent = Keyboard::Down; // stable condition variable is down
			state = 0;
			sprite.setTexture(textures[state]);
		}

	}
	else
		atJumpingState = false;

	sprite.setTexture(textures[state]);
	Object::draw(window);
	
}


void Mario::consecutiveControl(Keyboard::Key pressedKey) // consecutive event count for sliding
{

	if (pressedKey == consecutiveEvent and pressedKey != Keyboard::Down) // count consecutive event for right and left
	{
		consecutiveEventCount++;
	}
	else 
	{
		if (consecutiveEventCount > 10)  // condition for sliding effect
		{
			//take start position and set state  and prepare for sliding
			prev_x_for_sliding = sprite.getPosition().x;
			state = 4;
			atSlidingState = true;
			scateDirection = consecutiveEvent;
			consecutiveEvent = pressedKey;
		}
		else
		{  // if not enugh for sliding and changed event then reset
			consecutiveEvent = pressedKey;
			consecutiveEventCount = 1;
		}
		
	}
}



bool Mario::willHittedTheBrick() // check if hit any of the bricks
{
	for (int i = 0; i < size(brickSprite); i++)
	{
		if (sprite.getGlobalBounds().intersects(brickSprite[i].getGlobalBounds()))
		{
			return true;
		}

	}

	return false;
}


bool Mario::checkBoundary() //check mario at boundary for sliding effect
{
	//check for pipes
	if (sprite.getGlobalBounds().intersects(pipeSprite[0].getGlobalBounds()) or sprite.getGlobalBounds().intersects(pipeSprite[1].getGlobalBounds()) or sprite.getGlobalBounds().intersects(pipeSprite[2].getGlobalBounds()) or sprite.getGlobalBounds().intersects(pipeSprite[3].getGlobalBounds()))
	{
		scateDirection = Keyboard::Down;

		return true;
	}

	//check for window
	if (sprite.getPosition().x > window->getSize().x or sprite.getPosition().x < 0.0f)
	{
		scateDirection = Keyboard::Down;
		return true;
	}

	return false;
}