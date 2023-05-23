#include "Game.h"
#include "Turtle.h"
#include "Menu.h"
using namespace std;


Game::Game(RenderWindow* window)
{
	this->window = window;
	srand(time(NULL)); 
	appear_turtle = rand() % 20 + 5;
	mario = addMario();
	drawBackground(*window);
	
	for (int i = 0; i < size(brickSprite); i++) {
		mario->brickSprite[i] = brickSprite[i];
	}
	for (int i = 0; i < size(pipeSprite); i++) {
		mario->pipeSprite[i] = pipeSprite[i];
	}
	
	mario->setPosition(Vector2f(float(Pipe[0].getSize().x + 55), float(window->getSize().y - (floor.getSize().y + Pipe[0].getSize().y + 45))));
	
} 

Mario* Game::addMario(void)
{
	Mario* mario = new Mario(window);
	mario->next = objects;
	objects = mario;
	return mario;
}

void Game::drawBackground(RenderWindow& window) {
	if (!floor.loadFromFile("../assets/floor.png")) 
	{
		cout << "File could not be found" << endl;
	}
	if (!Pipe[0].loadFromFile("../assets/pipe.png")) 
	{
		cout << "File could not be found" << endl;
	}
	if (!Pipe[1].loadFromFile("../assets/pipeS.png"))
	{
		cout << "File could not be found" << endl;
	}
	if (!Brick.loadFromFile("../assets/brick.png"))
	{
		cout << "File could not be found" << endl;
	}
	if (!LiveMario.loadFromFile("../assets/mariohead.png"))
	{
		cout << "File could not be found" << endl;
	}
	if (!font.loadFromFile("../assets/font.ttf"))
	{
		cout << "Font could not be found" << endl; 
	}
	if (!newBrick.loadFromFile("../assets/yenibrick2.png"))
	{
		cout << "Font could not be found" << endl;
	}


	floor.setRepeated(true);
	floorSprite.setTexture(floor);
	floorSprite.setTextureRect(IntRect(0, 0, window.getSize().x, floor.getSize().y));
	floorSprite.setPosition(0.0f, float(window.getSize().y - (floor.getSize().y + 100)));
	
	
	text.setFont(font); 
	text.setString(mario->getScore());
	text.setCharacterSize(36);
	text.setPosition(10 , 5);


	textfinish.setFont(font); // font is a sf::Font
	textfinish.setCharacterSize(75); // in pixels, not points!
	textfinish.setPosition(270,450 );
	text.setString("");
	textfinish.setFillColor(sf::Color::Red);

	
	for (int i = 0; i < size(liveSprite); i++)
	{
		liveSprite[i]= new Sprite(LiveMario);
		liveSprite[i]->setPosition(initial_live_s, 60);
		initial_live_s += LiveMario.getSize().x;
	}

	pipeSprite[0].setTexture(Pipe[0]);
	pipeSprite[0].setPosition(float(window.getSize().x - (Pipe[0].getSize().x)), float(window.getSize().y - (floor.getSize().y + Pipe[0].getSize().y + 100)));
	
	pipeSprite[1].setTexture(Pipe[0]);
	pipeSprite[1].setScale(-1.f, 1.f);
	pipeSprite[1].setPosition(float(Pipe[0].getSize().x), float(window.getSize().y - (floor.getSize().y + Pipe[0].getSize().y + 100)));
	
	pipeSprite[2].setTexture(Pipe[1]);
	pipeSprite[2].setPosition(0, float(Pipe[1].getSize().y));

	pipeSprite[3].setTexture(Pipe[1]);
	pipeSprite[3].setScale(-1.f, 1.f);
	pipeSprite[3].setPosition(float(window.getSize().x), float(Pipe[1].getSize().y));

	Brick.setRepeated(true);

	for (int i = 0; i < size(brickSprite); i++){
		brickSprite[i].setTexture(Brick);
	}

	brickSprite[0].setTextureRect(IntRect(0, 0, 14*float(Brick.getSize().x), Brick.getSize().y));
	brickSprite[0].setPosition(0, 300); 

	
	brickSprite[1].setTextureRect(IntRect(0, 0, 14 * float(Brick.getSize().x), Brick.getSize().y));
	brickSprite[1].setPosition(float(window.getSize().x)- 14 * float(Brick.getSize().x), 300); 
	
	
	brickSprite[2].setTextureRect(IntRect(0, 0, 4 * float(Brick.getSize().x), Brick.getSize().y));
	brickSprite[2].setPosition(0, 500); 

	
	brickSprite[3].setTextureRect(IntRect(0, 0, 4 * float(Brick.getSize().x), Brick.getSize().y));
	brickSprite[3].setPosition(float(window.getSize().x) - 4 * float(Brick.getSize().x), 500);

	
	brickSprite[4].setTextureRect(IntRect(0, 0, 16 * float(Brick.getSize().x), Brick.getSize().y));
	brickSprite[4].setPosition(float(window.getSize().x/2 - 8 * float(Brick.getSize().x)), 450); 

	
	brickSprite[5].setTextureRect(IntRect(0, 0, 12 * float(Brick.getSize().x), Brick.getSize().y));
	brickSprite[5].setPosition(0, 700);
	
	brickSprite[6].setTextureRect(IntRect(0, 0, 12 * float(Brick.getSize().x), Brick.getSize().y));
	brickSprite[6].setPosition(float(window.getSize().x) - 12 * float(Brick.getSize().x), 700); 

	hitSprite = new Sprite(newBrick); 

}

void Game::update(void)
{
	while (window->isOpen())
	{

		Event event;
		bool isKeyPressedActive = false; // solution for first input delay - for keys which are not released


		if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::Left)) {
			isKeyPressedActive = true;
		}


		while (window->pollEvent(event) || isKeyPressedActive)
		{
			if (event.type == Event::Closed or event.key.code == Keyboard::Escape)
				window->close();
			
			if(!(mario->state == 6))
			{ 
				if ((event.type == Event::KeyPressed || isKeyPressedActive) and !mario->atSlidingState) // sliding state untouchable
				{
				
					if(!mario->atJumpingState) 
					{
						Vector2f prevPos = mario->getPosition();

						 if (Keyboard::isKeyPressed(Keyboard::Up))
						{
							mario->state = 5;
							mario->prev_y = mario->sprite.getPosition().y;

							// reset sliding state , can not slide
							mario->consecutiveEventCount = 1;
							mario->atSlidingState = 0;
						}
						else if (Keyboard::isKeyPressed(Keyboard::Right))
						 {
							 mario->consecutiveControl(Keyboard::Right); // control consecutive event for slide effect

							 if (Keyboard::isKeyPressed(Keyboard::Up))
							 {
								 mario->state = 5;
								 mario->prev_y = mario->sprite.getPosition().y;
								 mario->DirJ = Object::Directions::RIGHT;

								 //if jumping reset sliding state 
								 mario->atSlidingState = 0; 
							 }
							 else if(!mario->atSlidingState)
								mario->move(Object::Directions::RIGHT);

						}
						else if (Keyboard::isKeyPressed(Keyboard::Left))
						{
							 mario->consecutiveControl(Keyboard::Left);// control consecutive event for slide effect

							 if (Keyboard::isKeyPressed(Keyboard::Up))
							 {
								 mario->state = 5;
								 mario->prev_y = mario->sprite.getPosition().y;
								 mario->DirJ = Object::Directions::LEFT;

								 //if jumping reset sliding state 
								 mario->atSlidingState = 0;
							 }
							 else if (!mario->atSlidingState)
								 mario->move(Object::Directions::LEFT);
				
						} // end of keyboard actions
						 

						if (checkBoundary(mario))
						{
							mario->setSpeed(0, 0);
							mario->setPosition(prevPos);
						}
						prevKeyCode = event.key.code;
					}

					else 
					{
						if (Keyboard::isKeyPressed(Keyboard::Left))
						{
							mario->DirJ = Object::Directions::LEFT;
						}
						else if (Keyboard::isKeyPressed(Keyboard::Right))
						{
							mario->DirJ = Object::Directions::RIGHT;
						}else 
							mario->DirJ = Object::Directions::STABLE;
					}
				}
			
				else  // stable condition { not action at keyboard  or at sliding state }
				{
		
					if(!mario->atSlidingState) 
					{
						// check if characater try to be stable after consecutive event
						mario->consecutiveControl(Keyboard::Down);
					}
	
					if(prevKeyCode != Keyboard::Up and !mario->atSlidingState)
					{
						mario->state = 0;
						mario->sprite.setTexture(mario->textures[mario->state]);
					}

				}
			}

			isKeyPressedActive = false; // to exit to out of action while while
		}


		if (temp_appear == appear_turtle and n_turtle!=NUM_TURTLES)
		{
			heading = rand() % 2;
			turtle = addTurtle(heading);
			if (!heading)
				turtle->setPosition(
					Vector2f(Pipe[1].getSize().x+40,
						Pipe[1].getSize().y+60));
			else
				turtle->setPosition(Vector2f(float(window->getSize().x-Pipe[1].getSize().x)-40,
					Pipe[1].getSize().y +60));

			appear_turtle+= rand() % 30 + 10;
			n_turtle += 1;
		}

		temp_appear += 1;

		window->clear();
		window->draw(floorSprite);

		for (int i = 0; i < size(pipeSprite); i++)
			window->draw(pipeSprite[i]);
		
		drawObjects();

		for (int i = 0; i < size(brickSprite); i++)
			window->draw(brickSprite[i]);
		

		for (int i = 0; i < mario->getLives(); i++) 
		{ 
			if (liveSprite[i])
			{
				window->draw(*liveSprite[i]); 
			} 
		}

		checkTheScore();

		text.setString(mario->getScore());
		window->draw(text);
		
		window->display();
		sleep(milliseconds(1000 / speed)); // speed = fps

		if (!mario->getLives() or mario->getScore() == "500")
		{
			if (!mario->getLives()) 
				textfinish.setString("YOU LOSE");	
			else
				textfinish.setString("YOU WIN");
			
			window->draw(textfinish);
			window->display();
			sleep(milliseconds(1800));
			window->close();

			//return to menu
			RenderWindow* menuWindow; 
			menuWindow = new RenderWindow(VideoMode(1920, WINDOW_HEIGHT), "Menu");
			Menu menu(menuWindow);
			menu.update();

		}
	}
}
Game::~Game()
{
	window->close();
}
Turtle* Game::addTurtle(int heading)
{
	Turtle* turtle = new Turtle(window);

	if (heading) 
	{
		turtle->sprite.setScale(-1.f, 1.f);
	}

	turtle->heading = heading;
	turtle->next = objects; 
	objects = turtle;

	return turtle;
}


void Game::drawObjects(void)
{
	Object* cur = objects;
	Vector2f prevPosdraw;

	if (mario->getScore() == "500" or !mario->getLives())
		cur = NULL;

	while (cur)
	{
		if (Turtle* cur_turtle = dynamic_cast<Turtle*> (cur))
		{
			
			if (cur_turtle->state != 4)
			{
				if (onFloor(cur_turtle))
				{
					checkTurtlesCollusion(cur_turtle); // check turtle collusion for bonus 2 and take action
		
					cur_turtle->fallTurtle = false;

					if (!cur_turtle->isMeetTurtle) 
						cur_turtle->setSpeed(10.0f, 0.0f);
				
				}
				else
				{
					cur_turtle->setSpeed(0.0f, 10.0f);
					cur_turtle->fallTurtle = true;
				}


				if (cur_turtle->getPosition().x < 10.0f and cur_turtle->heading == 1)
				{
					cur_turtle->sprite.setScale(1.f, 1.f);
					cur_turtle->heading = 0;
				}
				else if (cur_turtle->getPosition().x > 950 and cur_turtle->heading == 0)
				{
					cur_turtle->sprite.setScale(-1.f, 1.f);
					cur_turtle->heading = 1;

				}


				if (pipeSprite[0].getGlobalBounds().intersects(cur_turtle->sprite.getGlobalBounds()))
				{

					cur_turtle->setPosition(
						Vector2f(float(window->getSize().x - Pipe[1].getSize().x) - 40,
							Pipe[1].getSize().y + 60));

					cur_turtle->sprite.setScale(-1.f, 1.f);
					cur_turtle->heading = 1;
				}

				if (pipeSprite[1].getGlobalBounds().intersects(cur_turtle->sprite.getGlobalBounds()))
				{
					cur_turtle->setPosition(
						Vector2f(Pipe[1].getSize().x + 40,
							Pipe[1].getSize().y + 60));

					cur_turtle->sprite.setScale(1.f, 1.f);
					cur_turtle->heading = 0;
				}

				checkTurtleHittedFromBottom(); // check turtle hitted from bottom and take action according that -- Bonus 3

			}
			
		}
		else if (Mario* cur_mario = dynamic_cast<Mario*>(cur))
		{
			if (cur_mario->state == 5)
			{
				if (checkBoundary(cur_mario))
				{
					
					if (cur_mario->DirJ== Object::Directions::RIGHT)
					{
						cur_mario->sprite.setPosition(
							cur->sprite.getPosition().x - 50,
							cur_mario->sprite.getPosition().y);
					}
					else 
					{
						cur_mario->sprite.setPosition(
							cur_mario->sprite.getPosition().x + 50,
							cur_mario->sprite.getPosition().y);
					}
					
					cur_mario->jump(true);
					cur_mario->state = 0;
					cur_mario->atJumpingState = false;
					
				}
			}


			if(cur_mario->state!=6)
			{ 

				if (checkCollusionwBrick(cur_mario))
				{
					cur_mario->atFallingState = false; // free fall without jump from up brickes to down

					if (onFloor(cur_mario))
					{ 
						if (cur_mario->atJumpingState)
						{
							cur_mario->DirJ = Mario::STABLE;
							cur_mario->state = 0;
							cur_mario->sprite.setTexture(cur_mario->textures[cur_mario->state]);
						}
				
					}
					else 
						checkHitTheBrickFromButtom(cur_mario); // control mario if hit brick from buttom for bonus 3 and take action
				
				}
				else 
				{
					if (!(cur_mario->atJumpingState)) { // falling state

						cur_mario->jump(true);
						cur_mario->atFallingState = true;
					
					}

				}

				marioColsWithTurtle(cur_mario);

			}
		}

		cur->draw(*window);
		cur = cur->next;

 	}
}
void Game::removeObjects(Object* obj)
{
	Object* cur = objects;
	Object* prev = NULL;
	while (cur)
	{
		if (cur == obj)
		{
			if (prev)
				prev->next = cur->next;
			else
				objects = cur->next;

			delete cur;

			return;
		}
	
		prev = cur;
		cur = cur->next; 
	}
}

bool Game::checkCollusionwBrick(Object* obj)
{
	for (int i = 0; i < size(brickSprite); i++)
	{
		if (obj->sprite.getGlobalBounds().intersects(brickSprite[i].getGlobalBounds()) or floorSprite.getGlobalBounds().intersects(obj->sprite.getGlobalBounds()))
		{
			return true;
		}

	}
	return false; 
}
bool Game::onFloor(Object* obj)
{
	FloatRect rect;
	
	if (dynamic_cast<Turtle*> (obj))
	{
		if (obj->heading)
			rect = FloatRect(obj->sprite.getPosition().x- obj->sprite.getGlobalBounds().width / 2,
				obj->sprite.getPosition().y - obj->sprite.getGlobalBounds().height / 2,
				obj->textures->getSize().x,
				(obj->sprite.getGlobalBounds().height / 2)); // (x, y, width, height)
		else
			rect = FloatRect(obj->sprite.getPosition().x - obj->sprite.getGlobalBounds().width / 2,
				obj->sprite.getPosition().y - obj->sprite.getGlobalBounds().height / 2,
				obj->textures->getSize().x,
				(obj->sprite.getGlobalBounds().height / 2)); // (x, y, width, height)
	}
	else
		rect = FloatRect(obj->sprite.getPosition().x - obj->sprite.getGlobalBounds().width / 2,
			obj->sprite.getPosition().y - obj->sprite.getGlobalBounds().height / 4,
			obj->textures->getSize().x,
			(obj->sprite.getGlobalBounds().height / 4));


	for (int i = 0; i < size(brickSprite); i++)
	{
		if (rect.intersects(brickSprite[i].getGlobalBounds()) or rect.intersects(floorSprite.getGlobalBounds()))
		{
			return true;
		}
	}


	return false;
}

void Game::checkHitTheBrickFromButtom(Object* obj)
{	
	// control head of mario for collusion
	FloatRect rect_top(obj->sprite.getPosition().x - obj->sprite.getGlobalBounds().width / 2,
		obj->sprite.getPosition().y - obj->sprite.getGlobalBounds().height,
		obj->textures->getSize().x,
		(obj->sprite.getGlobalBounds().height / 4));
	
	for (int i = 0; i < size(brickSprite); i++) //control every sprite
	{
		if (rect_top.intersects(brickSprite[i].getGlobalBounds()))
		{
			//start a falling from hitted brick
			obj->hittedBrick = true;
			obj->jumpHeight = obj->prev_y - obj->sprite.getPosition().y; // resize jumpHeight for  mario can't go up anymore

			//corner of bricks can cause uncertainty so clipped from corners a little bit
			FloatRect rectBrick(brickSprite[i].getPosition().x +35,
				brickSprite[i].getPosition().y,
				brickSprite[i].getGlobalBounds().width-70,
				brickSprite[i].getGlobalBounds().height);

			if (rectBrick.intersects(rect_top)) // check new clipped brick
			{
				hitSprite->setPosition(obj->getPosition().x - 30, obj->getPosition().y - 140);
				window->draw(*hitSprite);
			}

		}

	}

}



bool Game::checkBoundary(Object* obj)
{
	
	if (obj->sprite.getGlobalBounds().intersects(pipeSprite[0].getGlobalBounds()) or obj->sprite.getGlobalBounds().intersects(pipeSprite[1].getGlobalBounds()) or obj->sprite.getGlobalBounds().intersects(pipeSprite[2].getGlobalBounds()) or  obj->sprite.getGlobalBounds().intersects(pipeSprite[3].getGlobalBounds()))
	{
		return true;
	}

	if (obj->sprite.getPosition().x > window->getSize().x  or obj->sprite.getPosition().x< 0.0f )
	{
		return true;
	}
		
	return false; 
}

void Game::checkTurtlesCollusion(Object* obj)
{
	Object* cur = objects;
	FloatRect rect_turtle_cur;
	FloatRect rect_turtle_obj;

	if (obj->heading)
		rect_turtle_obj=FloatRect(obj->sprite.getPosition().x - obj->sprite.getGlobalBounds().width / 2,
			obj->sprite.getPosition().y - obj->sprite.getGlobalBounds().height,
			obj->textures->getSize().x / 4,
			(obj->sprite.getGlobalBounds().height));
	else
		rect_turtle_obj=FloatRect(obj->sprite.getPosition().x + obj->sprite.getGlobalBounds().width / 4,
			obj->sprite.getPosition().y - obj->sprite.getGlobalBounds().height,
			obj->textures->getSize().x / 4,
			(obj->sprite.getGlobalBounds().height));

	

	while (cur)
	{
		if (dynamic_cast<Turtle*> (cur))
		{ 
			// define a hitBox  for heading direction
			if (cur->heading)
				rect_turtle_cur = FloatRect(cur->sprite.getPosition().x - cur->sprite.getGlobalBounds().width / 2,
					cur->sprite.getPosition().y - cur->sprite.getGlobalBounds().height,
					cur->textures->getSize().x / 4,
					(cur->sprite.getGlobalBounds().height));
			else
				rect_turtle_cur= FloatRect(cur->sprite.getPosition().x + cur->sprite.getGlobalBounds().width / 4,
					cur->sprite.getPosition().y - cur->sprite.getGlobalBounds().height,
					cur->textures->getSize().x / 4,
					(cur->sprite.getGlobalBounds().height));


			if (cur != obj and rect_turtle_obj.intersects(rect_turtle_cur)) // check collison
			{
				if (onFloor(cur)) // check are they on floor
				{
					if (cur->checkTurtleCollusionable and obj->checkTurtleCollusionable) // when they  at state 4 (bonus 4) can not tochable for turtles
					{ 
						//set turtles for state 3 which is head to head position
						obj->isMeetTurtle = true; 
						cur->isMeetTurtle = true;
						obj->setSpeed(0, 0);
						cur->setSpeed(0, 0);
						cur->checkTurtleCollusionable = false;				
					}
				}
				
			}


		}
		cur = cur->next;
	}
	
	
}


void Game::marioColsWithTurtle(Mario* mario)
{
	Object* cur = objects;

	while (cur)
	{
		if (Turtle* turtle = dynamic_cast<Turtle*>(cur))
		{
		
			if (turtle->sprite.getGlobalBounds().intersects(mario->sprite.getGlobalBounds()))
			{
				if(checkCollusion(turtle, mario, turtle->heading) or turtle->state==4)
				{
					turtle->state = 4;
					turtle->deathFall = true;
				}
				else
				{
					mario->state = 6;
				}
			}

		}

		cur = cur->next;

	}

}



bool Game::checkCollusion(Turtle* turtle, Mario* mario, int& side)
{
	FloatRect rect_p(mario->sprite.getPosition().x - mario->sprite.getGlobalBounds().width / 2,
		mario->sprite.getPosition().y - mario->sprite.getGlobalBounds().height / 4,
		mario->textures->getSize().x,
		(mario->sprite.getGlobalBounds().height / 4));
	FloatRect rect_turtle = FloatRect(turtle->sprite.getPosition().x - turtle->sprite.getGlobalBounds().width / 2,
		turtle->sprite.getPosition().y - turtle->sprite.getGlobalBounds().height,
		turtle->textures->getSize().x,
		(turtle->sprite.getGlobalBounds().height) / 4); // (x, y, width, height)

	return rect_p.intersects(rect_turtle);
		
}


void Game::checkTurtleHittedFromBottom() // check for bonus 3
{		
	Object* obj= objects; // turtles and mario

	while (obj)
	{
		if (Turtle* turtle = dynamic_cast<Turtle*>(obj))
		{
			// check  bottom of turtle (turtle bottom hitbox)
			FloatRect rect(turtle->sprite.getPosition().x - turtle->sprite.getGlobalBounds().width / 2,
				turtle->sprite.getPosition().y - turtle->sprite.getGlobalBounds().height / 2,
				turtle->textures->getSize().x,
				(turtle->sprite.getGlobalBounds().height / 2)); // (x, y, width, height) 

			if (hitSprite and turtle->sprite.getGlobalBounds().intersects(hitSprite->getGlobalBounds())) // check any turtle intersects with new created hitSprite
			{
				//for state 4 determines this is for bonus 4 not for death falling 
				turtle->deathFall = false;
				turtle->state = 4;
				
				delete hitSprite; // for not collusion anymore
				hitSprite = new Sprite(newBrick); //  create new brick without location

				return;  // finish the void

			}
		}
		obj = obj->next;
	}

	delete hitSprite; // if not touched delete  hitsprite
	hitSprite = new Sprite(newBrick); //  create new brick without location
		
}

void Game::checkTheScore()
{
	Object* cur = objects;
	while(cur)
	{

		if (Turtle* turtle = dynamic_cast<Turtle*>(cur)) 
		{
			if (cur->getPosition().y > window->getSize().y)
			{

				mario->setScore(100);
				removeObjects(cur);

				return; 
			}
		}
		else 
		{
			if (cur->getPosition().y > window->getSize().y+100)
			{
				mario->DirJ = mario->STABLE;
				mario->setPosition(Vector2f(
					float(Pipe[0].getSize().x + 55),
					float(window->getSize().y - (floor.getSize().y + Pipe[0].getSize().y + 45))));

				mario->state = 0;
				mario->setLives(1);

				int del_index = (mario->getLives());
				delete liveSprite[del_index];
			}
		}
		cur=cur->next;
	}
}