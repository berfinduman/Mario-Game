#include "Game.h"
#include "Turtle.h"
#include "Menu.h"
using namespace std;


Game::Game(RenderWindow* window)
{
	this->window = window;
	srand(time(NULL));  //gives a different seed every time the program runs to get random value
	appear_turtle = rand() % 50 + 10; //Gets the first value that the turtle will exit during the while loop
	mario = addMario(); //Mario object created
	drawBackground(*window); //the function is called to draw the background
	

	//bricks must be checked so that mario does not go inside the bricks or pipes in case of jumping.
	for (int i = 0; i < size(brickSprite); i++) {
		mario->brickSprite[i] = brickSprite[i];
	}
	for (int i = 0; i < size(pipeSprite); i++) {
		mario->pipeSprite[i] = pipeSprite[i];
	}
	//positions of bricks and pipes are assigned within the Mario object to provide control

	mario->setPosition(Vector2f(float(Pipe[0].getSize().x + 55), float(window->getSize().y - (floor.getSize().y + Pipe[0].getSize().y + 45))));
	//the first position where the mario object will appear in the game is assigned
	
} 

Mario* Game::addMario(void)
{
	Mario* mario = new Mario(window);  //a new Mario object is created.
	mario->next = objects; //It is added to the beginning of the linked list connected to the Mario Object class.
	objects = mario;
	return mario;
}

Turtle* Game::addTurtle(int heading)
{
	Turtle* turtle = new Turtle(window); //The turtle object is created.

	if (heading)
	{
		turtle->sprite.setScale(-1.f, 1.f); //scaled according to turtle in heading
	}

	turtle->heading = heading; //the turtle object is assigned a heading method
	turtle->next = objects; ////turtle object is added to the beginning of the linked list connected to the Mario Object class.
	objects = turtle;

	return turtle;
}

void Game::drawBackground(RenderWindow& window) {

	//the textures and fonts that should be on the game screen were added with the loadFromFile() function
	//an error message is thrown if there is a problem uploading the files
	if (floor.loadFromFile("../assets/floor.png") ==false) 
	{
		throw("Textures files could not be opened!");
	}
	if (Pipe[0].loadFromFile("../assets/pipe.png") == false)
	{
		throw("Textures files could not be opened!");

	}
	if (Pipe[1].loadFromFile("../assets/pipeS.png") == false)
	{
		throw("Textures files could not be opened!");

	}
	if (Brick.loadFromFile("../assets/brick.png") == false)
	{
		throw("Textures files could not be opened!");

	}
	if (LiveMario.loadFromFile("../assets/mariohead.png") == false)
	{
		throw("Textures files could not be opened!");

	}
	if (font.loadFromFile("../assets/font.ttf") == false)
	{
		throw("Font files could not be opened!");

	}
	//the new brick we created for the bonus part
	if (newBrick.loadFromFile("../assets/yenibrick2.png") == false)
	{
		throw("Textures files could not be opened!");

	}


	floor.setRepeated(true); //enable repeating of the text
	floorSprite.setTexture(floor); // assign texture to floorSprite
	floorSprite.setTextureRect(IntRect(0, 0, window.getSize().x, floor.getSize().y)); // set the size of the floorSprite
	floorSprite.setPosition(0.0f, float(window.getSize().y - (floor.getSize().y + 100))); // set the position of the floorSprite
	
	
	text.setFont(font); 
	text.setString(mario->getScore());
	text.setCharacterSize(36);
	text.setPosition(10 , 5);


	textfinish.setFont(font); //assign font to textFinish Text. 
	textfinish.setCharacterSize(75); 
	textfinish.setPosition(270,450 );
	text.setString(""); //
	textfinish.setFillColor(sf::Color::Red); //initially sets the content of the text to blank.

	
	for (int i = 0; i < size(liveSprite); i++)
	{
		//To express each life of Mario, textures are assigned to the relevant sprite, position is determined
		liveSprite[i]= new Sprite(LiveMario);
		liveSprite[i]->setPosition(initial_live_s, 60);
		initial_live_s += LiveMario.getSize().x;
	}

	//In the same way, all pipelar headings are determined and assigned to the relevant Sprites and their positions are determined.
	pipeSprite[0].setTexture(Pipe[0]);
	pipeSprite[0].setPosition(float(window.getSize().x - (Pipe[0].getSize().x)), float(window.getSize().y - (floor.getSize().y + Pipe[0].getSize().y + 100)));
	
	pipeSprite[1].setTexture(Pipe[0]);
	pipeSprite[1].setScale(-1.f, 1.f); //heading is reversed
	pipeSprite[1].setPosition(float(Pipe[0].getSize().x), float(window.getSize().y - (floor.getSize().y + Pipe[0].getSize().y + 100)));
	
	pipeSprite[2].setTexture(Pipe[1]);
	pipeSprite[2].setPosition(0, float(Pipe[1].getSize().y));

	pipeSprite[3].setTexture(Pipe[1]);
	pipeSprite[3].setScale(-1.f, 1.f);//heading is reversed
	pipeSprite[3].setPosition(float(window.getSize().x), float(Pipe[1].getSize().y));

	Brick.setRepeated(true); //enable repeating of the text

	for (int i = 0; i < size(brickSprite); i++){
		brickSprite[i].setTexture(Brick);
	}
	//position given by setting the bricks to the desired length in the project

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

	// for bonus 3 creates HitSprite using newBrick texture
	hitSprite = new Sprite(newBrick); 

}

void Game::update(void)
{
	while (window->isOpen())
	{
		if (elapsedTime % 1200 == 0) // increase turtles speed after every 30 sec 1200 loop -> 30 sec
			increaseTurtlesSpeed();

		elapsedTime++;

		Event event;
		bool isKeyPressedActive = false; // solution for first input delay - for keys which are not released


		if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::Left)) {
			isKeyPressedActive = true;
		}


		while (window->pollEvent(event) || isKeyPressedActive)
		{
			if (event.type == Event::Closed or event.key.code == Keyboard::Escape) 
				window->close(); //the game closes when the close button or ESC is pressed.
			
			if(!(mario->state == 6))
			{ 
				if ((event.type == Event::KeyPressed || isKeyPressedActive) and !mario->atSlidingState) // sliding state untouchable
				{
				
					if(!mario->atJumpingState) //if not in flight
					{
						Vector2f prevPos = mario->getPosition(); //keeps the previous position as the new while loop starts

						 if (Keyboard::isKeyPressed(Keyboard::Up))
						{
							mario->state = 5; //jumping state
							mario->prev_y = prevPos.y; //defines to check the flight distance afterwards

							// reset sliding state , can not slide
							mario->consecutiveEventCount = 1;
							mario->atSlidingState = 0;
						}
						else if (Keyboard::isKeyPressed(Keyboard::Right))
						 {
							 mario->consecutiveControl(Keyboard::Right); // control consecutive event for slide effect

							 if (Keyboard::isKeyPressed(Keyboard::Up))
							 {
								 mario->state = 5; //jumping state
								 mario->prev_y = mario->sprite.getPosition().y;
								 mario->DirJ = Object::Directions::RIGHT; //for flight direction adjustment

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
							mario->setSpeed(0, 0); //speed will be reset.
							mario->setPosition(prevPos); //returns to its former position
						}
						prevKeyCode = event.key.code; //the previous pressed key is held
					}

					else  //while already jumping state 
					{
						if (Keyboard::isKeyPressed(Keyboard::Left))
						{ 
							mario->DirJ = Object::Directions::LEFT; //for flight direction adjustment
						}
						else if (Keyboard::isKeyPressed(Keyboard::Right))
						{
							mario->DirJ = Object::Directions::RIGHT; //for flight direction adjustment
						}else 
							mario->DirJ = Object::Directions::STABLE; //flies straight without any interference
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


		if (temp_appear == appear_turtle and n_turtle!=NUM_TURTLES) //turtle in random checks the exit time and number
		{
			heading = rand() % 2; //sets which straw the turtle will spawn
			turtle = addTurtle(heading); // created Turtle object
			if (!heading) 
				turtle->setPosition(
					Vector2f(Pipe[1].getSize().x+40,
						Pipe[1].getSize().y+60));
			else
				turtle->setPosition(Vector2f(float(window->getSize().x-Pipe[1].getSize().x)-40,
					Pipe[1].getSize().y +60));

			appear_turtle+= rand() % 40 + 20; //Randomly assigns the exit time of the other turtle somewhere between the next 20-40 cycles
			n_turtle += 1; //increases the number of turtles entering the game
		}

		temp_appear += 1;

		window->clear(); //remaining drawings from the previous cycle are deleted


		//draw() function draws the sprite it contains at the position set to the window.
		window->draw(floorSprite);

		for (int i = 0; i < size(pipeSprite); i++)
			window->draw(pipeSprite[i]);
		
		drawObjects(); //mario and turtle are drawn in this function

		for (int i = 0; i < size(brickSprite); i++)
			window->draw(brickSprite[i]);
		

		for (int i = 0; i < mario->getLives(); i++) 
		{ 
			if (liveSprite[i])
			{
				window->draw(*liveSprite[i]); 
			} 
		}

		checkTheScore(); //checks if turtle or mario is dead
		//getScore() function keeps marion's instant score
		text.setString(mario->getScore()); //This score is printed on the text
		window->draw(text);
		
		window->display();
		sleep(milliseconds(1000 / speed)); // speed = fps

		//GAME ENDING STATES
		if (!mario->getLives() or mario->getScore() == "500") //if all of mario's lives are gone or all turtles are dead
		{
			
			if (!mario->getLives()) 
				textfinish.setString("GAME OVER");
			else
				textfinish.setString("YOU WIN!");
			
			window->draw(textfinish); //relevant text is printed on the screen
			window->display();
			sleep(milliseconds(1800)); //screen waits for 3 seconds and turns off
			window->close();

			//return to menu
			RenderWindow* menuWindow; 
			menuWindow = new RenderWindow(VideoMode(1920, WINDOW_HEIGHT), "Menu");
			menuWindow->create(sf::VideoMode::getFullscreenModes()[0], "SFML Pencere", sf::Style::Fullscreen);
			Menu menu(menuWindow);
			menu.update();

		}
	}
}
Game::~Game() //deconstructor
{
	window->close();
}

void Game::increaseTurtlesSpeed() {
	Object* cur = objects;

	while (cur) 
	{
		if (Turtle* cur_turtle = dynamic_cast<Turtle*> (cur)) 
		{
			cur_turtle->turtleSpeed = cur_turtle->turtleSpeed + 3.0f;
		}

		cur = cur->next;
	}


}


void Game::drawObjects(void)
{
	Object* cur = objects; //The objects object that mario turtles are connected to with linked list is assigned to a new cur object
	Vector2f prevPosdraw; 

	if (mario->getScore() == "500" or !mario->getLives())
		cur = NULL;  //does not draw anything when the game end condition is met

	while (cur) //in this way, it travels all the objects on the linked list.
	{
		if (Turtle* cur_turtle = dynamic_cast<Turtle*> (cur)) //in case the related object is turtle, assigns this object as cur_turtle to the Turtle object
		{
			
			if (cur_turtle->state != 4) //unless the turtle is in a state of inversion
			{
				if (onFloor(cur_turtle)) //if turtle touches the surface
				{
					checkTurtlesCollusion(cur_turtle); // check turtle collusion for bonus 2 and take action
		
					cur_turtle->fallTurtle = false; //set turtle drop status false

					if (!cur_turtle->isMeetTurtle)  //does not conflict with another turtle
						cur_turtle->setSpeed(cur_turtle->turtleSpeed, 0.0f);
				
				}
				else
				{
					cur_turtle->setSpeed(0.0f, 10.0f);
					cur_turtle->fallTurtle = true; //turtle is set to fall
				}

				//boundary control
				//at the end of the screen, it turns over and sets the heading accordingly.
				if (cur_turtle->getPosition().x < 10.0f and cur_turtle->heading == 1) 
				{
					cur_turtle->sprite.setScale(1.f, 1.f);
					cur_turtle->heading = 0;
				}
				//setscale (1.f,1.f) when heading=0
				//when heading = 1, setscale will be at (-1.f,1.f) for the picture to be reversed
				
				else if (cur_turtle->getPosition().x > 950 and cur_turtle->heading == 0)
				{
					cur_turtle->sprite.setScale(-1.f, 1.f);
					cur_turtle->heading = 1;

				}

				//when it reaches the pipes at the bottom, it goes back to the beginning
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
		else if (Mario* cur_mario = dynamic_cast<Mario*>(cur)) //in case the related object is mario, assigns this object as cur_mario to the Mario object
		{
			if (cur_mario->state == 5) //unless the turtle is in a state of jumping
			{
				if (checkBoundary(cur_mario)) //if the window has exceeded its limits
				{
					
					if (cur_mario->DirJ== Object::Directions::RIGHT) 
					{
						cur_mario->sprite.setPosition(
							cur->sprite.getPosition().x - 50,
							cur_mario->sprite.getPosition().y);
						//if mario leans to the right and crosses the limit, he moves the position to the left by 50 units
					}
					else 
					{
						cur_mario->sprite.setPosition(
							cur_mario->sprite.getPosition().x + 50,
							cur_mario->sprite.getPosition().y);
						//if mario leans to the left and crosses the limit, he moves the position to the right by 50 units
					}
					
					cur_mario->jump(true); //cancels the jump function
					cur_mario->state = 0;
					cur_mario->atJumpingState = false; //cancels the jumping state and set mario state 0.
					
				}
			}


			if(cur_mario->state!=6) //state=6 is the case where mario was killed by the turtle
			{ 

				if (checkCollusionwBrick(cur_mario))
				{
					cur_mario->atFallingState = false; // free fall without jump from up brickes to down

					if (onFloor(cur_mario)) //if mario's feet touch the surface
					{ 
						if (cur_mario->atJumpingState) //if mario is in a jump state
						{
							cur_mario->DirJ = Mario::STABLE; //resets the flight direction
							cur_mario->state = 0; //reset mario state 
							cur_mario->sprite.setTexture(cur_mario->textures[cur_mario->state]); //according to state mario's sprite draws windows
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

				marioColsWithTurtle(cur_mario); //Checks if mario and turtle intersect and arranges accordingly in this function

			}
		}
		 
		cur->draw(*window); //draws cur  object to the window
		cur = cur->next; //past the next object
		 
 	}
}
void Game::removeObjects(Object* obj)
{
	//linked list deletes obj object
	Object* cur = objects;  // Creates a pointer to track the current node.
	Object* prev = NULL;   // Creates a pointer to track the previous node.
	while (cur)
	{
		if (cur == obj)
		{
			if (prev) // If the previous node exists, update the reference to the deleted node.
				prev->next = cur->next;
			else  // If there is no previous node, it means the deleted node is the first node, so update the start node.
				objects = cur->next;

			delete cur; // Deletes the object to prevent memory leaks.

			return;
		}
	
		prev = cur;
		cur = cur->next;  // Move to the next node.
	}
}

bool Game::checkCollusionwBrick(Object* obj)
{
	//checks whether the obj object taken as a parameter in the function hits the bricks or the floor.

	if (floorSprite.getGlobalBounds().intersects(obj->sprite.getGlobalBounds()))
		return true;

	for (int i = 0; i < size(brickSprite); i++)
	{
		if (obj->sprite.getGlobalBounds().intersects(brickSprite[i].getGlobalBounds()))
		{
			return true;
		}

	}
	return false; 
}
bool Game::onFloor(Object* obj)
{
	//Confirms whether the object intersects the brick or floor from below.
	FloatRect rect;
	//new FloatRect object is created by taking the coordinates of the lower parts of the objects
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

	//It is checked whether the surfaces intersect with the created rect object.
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
	//returns true if the object is outside the boundary.
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
	//intersection status of the turtles with the mario object, which we take as a parameter to the function, is checked
	Object* cur = objects;

	while (cur) //The object link list is taken to the cur object and returns it to the end in while
	{

		
		if (Turtle* turtle = dynamic_cast<Turtle*>(cur))
		{
		
			if (turtle->sprite.getGlobalBounds().intersects(mario->sprite.getGlobalBounds())) //if mario and cur intersect
			{
				if(checkCollusion(turtle, mario, turtle->heading) or turtle->state==4) //If mario turtle is shooting from the top or turtle test is back (for bonus part)
				{
					turtle->state = 4; //if turtles die, set state 4
					turtle->deathFall = true; //turtle fall state returns true
				}
				else
				{
					mario->state = 6; //if mario is not hit the turtle on top, mario will die so set stete 6.
				}
			}

		}

		cur = cur->next;

	}

}



bool Game::checkCollusion(Turtle* turtle, Mario* mario, int& side)
{
	//returns true if turtle's head and Mario's feet collide, that is, if Mario kills the turtle
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
			
			if (cur->getPosition().y > window->getSize().y) //If the turtle in the linked list is outside the window, it has fallen into a falling state and died.
			{

				mario->setScore(100); //mario earns 100 points for killing the turtle.
				removeObjects(cur); //remove from turtle in linked list.

				return; 
			}
		}
		else 
		{
			if (cur->getPosition().y > window->getSize().y+100)
			{
				//if mario loses health, he dies and if he hasn't lost all 3 health he is put in a position to respawn
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