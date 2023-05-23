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
		sprite.setOrigin(sprite.getTextureRect().width / 2.0f, sprite.getTextureRect().height);

		//sprite.setOrigin(sprite.getTextureRect().width / 2.0f, sprite.getTextureRect().height);

		
		
	}
}
void Turtle::draw(RenderWindow& window)
{
	
	//cout << "Girdik bir elamate";

	

	sprite.setTexture(textures[state]);
	

	if (!heading) sprite.move(vx, vy);
	else sprite.move(-vx, vy);


	switch (state)
	{
	case 0:
		if (fallTurtle) state = 2;
		else state = 1;
		if (isMeetTurtle)
		{
			headingTime -= 1;

			if (headingTime == 8) state = 3;

		}
		break;


	case  1:
		if (fallTurtle) state = 2;
		else state = 0;


		if (isMeetTurtle) state = 0;
		break;


	case 2:
		if (fallTurtle) state = 2;
		else state = 0;
		if (isMeetTurtle) state = 0;
		break;

	case 3:


		if (headingTime  >0)
		{
			headingTime -= 1;
		}
		else if (headingTime == 0)
		{
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
			isMeetTurtle = false;
			headingTime = 10;
			checkTurtleCollusionable = true;
			state = 1;
		}
		break;

	case 4:
		cout << "turtle reverse direct. "<<fallFree << endl;
		if (fallFree)
		fall();
		else 
		{
			cout << "*/*/*/*/GIRDIIIIIIIIIIII" << endl;

			if (bonusjumptime != 0) {
				

				jump(2 >= bonusjumptime);  // yukarý aþþaðý
				bonusjumptime -= 1;
				

			}
			else if (bonusjumptime==0)
			{
			if (bonustime != 0)
			{
				setSpeed(0, 0);
				checkTurtleCollusionable = false; 
				bonustime -= 1;
			}
			else
			{
				bonustime = 80;

				fallFree = true; // can fall free state
				checkTurtleCollusionable = true;
				state = 0;
				bonusjumptime = 4;
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



