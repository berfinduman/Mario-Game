#include "Turtle.h"
Turtle::Turtle(RenderWindow* window) :Object(window)
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
	sprite.setOrigin(sprite.getTextureRect().width / 2.0f, sprite.getTextureRect().height);

}
void Turtle::draw(RenderWindow& window)
{
	sprite.setTexture(textures[state]);
	
	if (!heading)
		sprite.move(vx, vy);
	else 
		sprite.move(-vx, vy);


	switch (state)
	{
		case 0:
			if (fallTurtle)
				state = 2;
			else 
				state = 1;

			if (isMeetTurtle)
			{
				meetingTime -= 1;
				if (meetingTime == 8) 
					state = 3;
			}
			break;


		case  1:
			if (fallTurtle)
				state = 2;
			else 
				state = 0;


			if (isMeetTurtle)
				state = 0;

			break;


		case 2:
			if (fallTurtle) 
				state = 2;
			else 
				state = 0;

			if (isMeetTurtle)
				state = 0;

			break;

		case 3: // bonus 2
			if (meetingTime  >0) // a few sec wait at head to head position 
			{
				meetingTime -= 1;
			}
			else if (meetingTime == 0)
			{
				//change the direction of turtle
				if (heading)
				{
					heading = 0;
					sprite.setScale(1.f, 1.f);
					setSpeed(10.0f, 0.0f);
				}
				else
				{
					heading = 1;
					sprite.setScale(-1.f, 1.f);
					setSpeed(10.0f, 0.0f);
				}

				//reset the variables
				isMeetTurtle = false;
				meetingTime = 10;
				checkTurtleCollusionable = true;
				state = 1;
			}
			break;

		case 4:

			if (deathFall) // check is it falling because of died
				fall();
			else 
			{
				if (turtleBottomHittedJumpTime != 0) {
					jump(2 >= turtleBottomHittedJumpTime);  //  bonusJumpTime = 4 and half for up , half for down direction  for jumping
						turtleBottomHittedJumpTime -= 1;
				}
				else if (turtleBottomHittedJumpTime==0) // finished jumping waiting  at reverse position
				{
					if (turtleBottomHittedWaitingTime != 0)
					{
						setSpeed(0, 0);
						checkTurtleCollusionable = false;  //can not touchable for turtles
						turtleBottomHittedWaitingTime -= 1;
					}
					else
					{
						//reset variables and stand up for turtle
						turtleBottomHittedWaitingTime = 80;
						deathFall = true; // check value at state 4 for is it deathFalling or not
						checkTurtleCollusionable = true;
						state = 0;
						turtleBottomHittedJumpTime = 4;
					}
				}
			}

	}


	window.draw(sprite);

}


void Turtle::jump(bool down)
{
	if (down)
	{
		setSpeed(0, 40);
	}
	else
	{
		setSpeed(0, -40);
	}
}



void Turtle::fall(void)
{	
	setSpeed(0, 40);
}



