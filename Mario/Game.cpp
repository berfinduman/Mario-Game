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
	if (!floor.loadFromFile("../assets/floor.png")) //We added exception later on
	{
		//cout << "File could not be found" << endl;
	}
	if (!Pipe[0].loadFromFile("../assets/pipe.png")) //We added exception later on
	{
		//cout << "File could not be found" << endl;
	}

	if (!Pipe[1].loadFromFile("../assets/pipeS.png")) //We added exception later on
	{
		//cout << "File could not be found" << endl;
	}

	if (!Brick.loadFromFile("../assets/brick.png")) //We added exception later on
	{
		//cout << "File could not be found" << endl;
	}

	if (!LiveMario.loadFromFile("../assets/mariohead.png")) //We added exception later on
	{
		//cout << "File could not be found" << endl;
	}

	
	if (!font.loadFromFile("../assets/font.ttf"))
	{
		//cout << "Font could not be found" << endl; 
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
	brickSprite[0].setPosition(0, 300); //float(window.getSize().y - (floor.getSize().y - 50))

	
	brickSprite[1].setTextureRect(IntRect(0, 0, 14 * float(Brick.getSize().x), Brick.getSize().y));
	brickSprite[1].setPosition(float(window.getSize().x)- 14 * float(Brick.getSize().x), 300); //float(window.getSize().y - (floor.getSize().y - 50))
	
	
	brickSprite[2].setTextureRect(IntRect(0, 0, 4 * float(Brick.getSize().x), Brick.getSize().y));
	brickSprite[2].setPosition(0, 500); //float(window.getSize().y - (floor.getSize().y - 50))

	
	brickSprite[3].setTextureRect(IntRect(0, 0, 4 * float(Brick.getSize().x), Brick.getSize().y));
	brickSprite[3].setPosition(float(window.getSize().x) - 4 * float(Brick.getSize().x), 500); //float(window.getSize().y - (floor.getSize().y - 50))

	
	brickSprite[4].setTextureRect(IntRect(0, 0, 16 * float(Brick.getSize().x), Brick.getSize().y));
	brickSprite[4].setPosition(float(window.getSize().x/2 - 8 * float(Brick.getSize().x)), 450); //float(window.getSize().y - (floor.getSize().y - 50))

	
	brickSprite[5].setTextureRect(IntRect(0, 0, 12 * float(Brick.getSize().x), Brick.getSize().y));
	brickSprite[5].setPosition(0, 700); //float(window.getSize().y - (floor.getSize().y - 50))

	
	brickSprite[6].setTextureRect(IntRect(0, 0, 12 * float(Brick.getSize().x), Brick.getSize().y));
	brickSprite[6].setPosition(float(window.getSize().x) - 12 * float(Brick.getSize().x), 700); //float(window.getSize().y - (floor.getSize().y - 50))

	hitSprite = new Sprite(newBrick); 
	//mario.setPosition(Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));
/**/
}

void Game::update(void)
{
	while (window->isOpen())
	{

		Event event;

		bool isKeyPressedActive = false; // solution for first input delay


		if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::Left)) {
			isKeyPressedActive = true;
		}


		while (window->pollEvent(event) || isKeyPressedActive)
		{
			if (event.type == Event::Closed)
				window->close();

			if(!(mario->state == 6))
			{ 


			if ((event.type == Event::KeyPressed || isKeyPressedActive) and !mario->atScatingState)

			{
				
				if(!mario->atJumpingState) {
					Vector2f prevPos = mario->getPosition();
					//cout << "PrevPos " << prevPos.x<<" " << prevPos.y << endl;
					 if (Keyboard::isKeyPressed(Keyboard::Up))
					{
						//cout << "Selam" << endl; 
						//mario->move(Object::Directions::UP);

						 mario->consecutiveEventCount = 1;
						 mario->atScatingState = 0;
						mario->state = 5;
						mario->prev_y = mario->sprite.getPosition().y;
	
					}
					else if (Keyboard::isKeyPressed(Keyboard::Right))
					 {
						 mario->consecutiveControl(Keyboard::Right);

						 
						 if (Keyboard::isKeyPressed(Keyboard::Up))
						 {
							 mario->state = 5;
							 mario->atScatingState = 0;
							 mario->prev_y = mario->sprite.getPosition().y;
							 mario->DirJ = Object::Directions::RIGHT;
						 }
						 else if(!mario->atScatingState)
							mario->move(Object::Directions::RIGHT);

						 
					}
					else if (Keyboard::isKeyPressed(Keyboard::Left))
					{
						 mario->consecutiveControl(Keyboard::Left);
						 if (Keyboard::isKeyPressed(Keyboard::Up))
						 {
							 mario->state = 5;
							 mario->atScatingState = 0;
							 mario->prev_y = mario->sprite.getPosition().y;
							 mario->DirJ = Object::Directions::LEFT;
						 }
						 else if (!mario->atScatingState)
							 mario->move(Object::Directions::LEFT);

						 
					}
					if (checkBoundary(mario))
					{
						//cout << "Fonksiyona girdi" << mario->getPosition().x << "   " << mario->getPosition().y;
						mario->setSpeed(0, 0);
						mario->setPosition(prevPos);
					}
					prevKeyCode = event.key.code;
					//Object::Directions prevkeyDir = event.key.code;
					//cout << "Event" << event.key.code << endl;
				}
				else {
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
			
			else 
				//if (event.type != Event::KeyPressed and prevKeyCode != 723)
			{
		
				if(!mario->atScatingState) {
					mario->consecutiveControl(Keyboard::Down);
				}
				//cout << "YOK Event" << prevKeyCode<<endl;
				if(prevKeyCode != Keyboard::Up and !mario->atScatingState){
				mario->state = 0;
				mario->sprite.setTexture(mario->textures[mario->state]);}
				//mario->move(Object::Directions::STABLE);
				//cout << "!" << event.key.code << endl;
			}
			}
			isKeyPressedActive = false;
		}
		if (temp_appear == appear_turtle and n_turtle!=NUM_TURTLES)
		{
			//cout << "Appear turtle num: " <<appear_turtle<<endl;
			heading = rand() % 2;
			turtle = addTurtle(heading);
			if (!heading)
			turtle->setPosition(Vector2f(Pipe[1].getSize().x+40, Pipe[1].getSize().y+60)); //+28
			else turtle->setPosition(Vector2f(float(window->getSize().x-Pipe[1].getSize().x)-40, Pipe[1].getSize().y +60));
			//cout << Pipe[1].getSize().x << endl;
			appear_turtle+= rand() % 30 + 10;
			n_turtle += 1;
		}
		temp_appear += 1;
		window->clear();
		window->draw(floorSprite);
		for (int i = 0; i < size(pipeSprite); i++) window->draw(pipeSprite[i]);
		
		drawObjects();

		for (int i = 0; i < size(brickSprite); i++) window->draw(brickSprite[i]);
		

		for (int i = 0; i < mario->getLives(); i++) { if (liveSprite[i]) {   window->draw(*liveSprite[i]); } }
		checkTheScore();
		//cout << mario->atJumpingState << "before mario draw" << endl;
		



		//cout << "deneme" << endl;
		//cout << "Bittim" << mario->getScore() << endl;
		text.setString(mario->getScore());
		window->draw(text);
		
		 //17<=60 fps
		window->display();
		sleep(milliseconds(1000 / speed));
		if (!mario->getLives() or mario->getScore() == "500")
		{
			if (!mario->getLives()) textfinish.setString("YOU LOSE");
			
			else textfinish.setString("YOU WIN");
			
			window->draw(textfinish);
			window->display();
			sleep(milliseconds(1800));
			window->close();
			RenderWindow* menuWindow;
			menuWindow = new RenderWindow(VideoMode(1920, WINDOW_HEIGHT), "Menu");

			Menu menu(menuWindow);
			menu.update();
		}
		

	}
}
Game::~Game()
{
	//delete window ;
}
Turtle* Game::addTurtle(int heading)
{
	Turtle* turtle = new Turtle(window);
	if (heading) {
		turtle->sprite.setScale(-1.f, 1.f);
	}
	turtle->heading=heading;
	turtle->next = objects; 
	objects = turtle;
	return turtle;
}
void Game::drawObjects(void)
{
	Object* cur = objects;
	Vector2f prevPosdraw;
	if (mario->getScore() == "500" or !mario->getLives()) cur = NULL;
	while (cur)
	{
		if (Turtle* cur_turtle = dynamic_cast<Turtle*> (cur))
		{
			
			if (cur_turtle->state != 4)
			{
				if (onFloor(cur_turtle))
				{
					TurtlesCollusion(cur_turtle);
		
					cur_turtle->fallTurtle = false;
					if (!cur_turtle->headOnTurtle) cur_turtle->setSpeed(10.0f, 0.0f);
				
				}
				else
				{
					cur_turtle->setSpeed(0.0f, 10.0f);
					cur_turtle->fallTurtle = true;
				};

				if (cur_turtle->getPosition().x < 10.0f and cur_turtle->heading == 1)
				{
					cur_turtle->sprite.setScale(1.f, 1.f);
					cur_turtle->heading = 0;
				}
				else if (cur_turtle->getPosition().x > 950 and cur_turtle->heading == 0)
				{
					cur_turtle->sprite.setScale(-1.f, 1.f);
					cur_turtle->heading = 1;

				};

				if (pipeSprite[0].getGlobalBounds().intersects(cur_turtle->sprite.getGlobalBounds()))
				{

					cur_turtle->setPosition(Vector2f(float(window->getSize().x - Pipe[1].getSize().x) - 40, Pipe[1].getSize().y + 60));


					cur_turtle->sprite.setScale(-1.f, 1.f);
					cur_turtle->heading = 1;
				}

				if (pipeSprite[1].getGlobalBounds().intersects(cur_turtle->sprite.getGlobalBounds()))
				{
					cur_turtle->setPosition(Vector2f(Pipe[1].getSize().x + 40, Pipe[1].getSize().y + 60)); //+28

					cur_turtle->sprite.setScale(1.f, 1.f);
					cur_turtle->heading = 0;
				}

			checkTurtleHitTheBrick();

			}
			
		}
		else if (Mario* cur_mario = dynamic_cast<Mario*>(cur))
		{
			if (cur_mario->state == 5)
			{
				if (checkBoundary(cur_mario))  // boundry for window
				{
					
					if (cur_mario->DirJ== Object::Directions::RIGHT)
					{
						cur_mario->sprite.setPosition(cur->sprite.getPosition().x - 50, cur_mario->sprite.getPosition().y);
					}
					else 
					{
						cur_mario->sprite.setPosition(cur_mario->sprite.getPosition().x + 50, cur_mario->sprite.getPosition().y);
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
				cur_mario->atFallingState = false;
				cout << "Mario is colliding brick or floor." << endl;
				if (onFloor(cur_mario))
				{ 
					if (cur_mario->atJumpingState)
					{
						cur_mario->DirJ = Mario::STABLE;
						//cout << "while mario is jumping." << endl;
						cur_mario->state = 0;
						cur_mario->sprite.setTexture(cur_mario->textures[cur_mario->state]);
					}
				
				}
				else hitTheBrick(cur_mario);
				
			}
			else 
			{
				//cout << cur_mario->atJumpingState << "Mario jumping stateee  elsedeeee" << endl;
				//cout << "Mario is flying" << endl;
				if (!(cur_mario->atJumpingState)) { // falling state
					//cout << "Mario is falling" << endl;
					cur_mario->jump(true);
					cur_mario->atFallingState = true;
					
				}
				//else cout << "jumping too  "<< cur_mario->atJumpingState<<"  " << cur_mario->state << endl;
				
			}
			marioColsWithTurtle(cur_mario);

			
			
			}
			}
		/*sf::RectangleShape rectShapeSet;
		rectShapeSet.setFillColor(sf::Color::Green);
		rectShapeSet.setPosition(rect_turtle.left, rect_turtle.top);
		rectShapeSet.setSize(sf::Vector2f(rect_turtle.width, rect_turtle.height));
		window->draw(rectShapeSet);	*/	
		cur->draw(*window);
		cur = cur->next;
		
		//cout << "DrawObject fonksiyonunda cikiyor"<<endl;
 	}
}
void Game::removeObjects(Object* obj)
{
	Object* cur = objects;
	//cout << "enterthe func" << endl;
	Object* prev = NULL;
	while (cur)
	{
		if (cur == obj)
		{
			if (prev)	prev->next = cur->next;

			else objects = cur->next;

			delete cur;
			//cout << "delete etti ho" << endl;
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


	else rect = FloatRect(obj->sprite.getPosition().x - obj->sprite.getGlobalBounds().width / 2, obj->sprite.getPosition().y - obj->sprite.getGlobalBounds().height / 4, obj->textures->getSize().x, (obj->sprite.getGlobalBounds().height / 4));
	/**/
	/*
	FloatRect rect = obj->sprite.getGlobalBounds();
	FloatRect floorRect = floorSprite.getGlobalBounds();
	
	
	if (rect.intersects(floorRect) && (rect.top+rect.height <= floorRect.top+ floorRect.height))
	{
		return true;
	}
	*/
	for (int i = 0; i < size(brickSprite); i++)
	{
		if (rect.intersects(brickSprite[i].getGlobalBounds()) or rect.intersects(floorSprite.getGlobalBounds()))
		{
			return true;
		}
		/*FloatRect brickRect = brickSprite[i].getGlobalBounds();
		
		if (rect.intersects(brickRect) && (rect.top+rect.height <= brickRect.top + brickRect.height ))
		{
			return true; 
		}*/

		
	}
	return false;
}

void Game::hitTheBrick(Object* obj)
{	
	cout << "Hit the brickk" << endl;

	FloatRect rect_top(obj->sprite.getPosition().x - obj->sprite.getGlobalBounds().width / 2, obj->sprite.getPosition().y - obj->sprite.getGlobalBounds().height, obj->textures->getSize().x, (obj->sprite.getGlobalBounds().height / 4));
	
	for (int i = 0; i < size(brickSprite); i++)
	{
		if (rect_top.intersects(brickSprite[i].getGlobalBounds()))
		{
			obj->hittedBrick = true;
			//if (dynamic_cast<Mario*> (obj)) //cout << "Bricke ustten vurdu "<<endl;

			obj->jumpHeight = obj->prev_y - obj->sprite.getPosition().y;

			cout <<"Carefulll" << obj->jumpHeight << endl;
			cout << "X POS" << brickSprite[i].getPosition().x << "Y POS" << brickSprite[i].getPosition().y<<endl;
			FloatRect rectBrick(brickSprite[i].getPosition().x +35, brickSprite[i].getPosition().y, brickSprite[i].getGlobalBounds().width-70, brickSprite[i].getGlobalBounds().height);
			if (rectBrick.intersects(rect_top))
			{
			hitSprite->setPosition(obj->getPosition().x - 30, obj->getPosition().y - 140);
			window->draw(*hitSprite);}
			//Vector2f hitPos = Vector2f(obj->getPosition().x, obj->getPosition().y-100);
		


		}

	}
}



bool Game::checkBoundary(Object* obj)
{
	
	//FloatRect rect_mar(obj->sprite.getPosition().x - obj->sprite.getGlobalBounds().width / 2, obj->sprite.getPosition().y - (obj->textures->getSize().y / 2), (obj->sprite.getGlobalBounds().width), obj->textures->getSize().y/2); // (x, y, width, height)
	//FloatRect rect_mar2(obj->sprite.getPosition().x , obj->sprite.getPosition().y- (obj->textures->getSize().y / 2), (obj->sprite.getGlobalBounds().width / 2), obj->textures->getSize().y); // (x, y, width, height)

	if (obj->sprite.getGlobalBounds().intersects(pipeSprite[0].getGlobalBounds()) or obj->sprite.getGlobalBounds().intersects(pipeSprite[1].getGlobalBounds()) or obj->sprite.getGlobalBounds().intersects(pipeSprite[2].getGlobalBounds()) or  obj->sprite.getGlobalBounds().intersects(pipeSprite[3].getGlobalBounds()))
		//or  obj->getPosition().x< 0 )
		//or obj->getPosition().x> WINDOW_WIDTH)
	{
		//cout << "checkboundary e girdi" << endl;
		//cout <<obj->getPosition().x << endl;
		
		return true;
	}

	if (obj->sprite.getPosition().x > window->getSize().x  or obj->sprite.getPosition().x< 0.0f )
	{
		//cout << "True" << obj->sprite.getPosition().x << window->getSize().x ;
		return true;
	}

	
		//cout << obj->sprite.getPosition().x <<"   " << window->getSize().x << "   " << (obj->sprite.getPosition().x > window->getSize().x);
		
	return false; 
}

void Game::TurtlesCollusion(Object* obj)
{
	Object* cur = objects;
	FloatRect rect_turtle_cur;
	FloatRect rect_turtle_obj;

	if (obj->heading)
	rect_turtle_obj=FloatRect(obj->sprite.getPosition().x - obj->sprite.getGlobalBounds().width / 2, obj->sprite.getPosition().y - obj->sprite.getGlobalBounds().height, obj->textures->getSize().x / 4, (obj->sprite.getGlobalBounds().height));
	else
	rect_turtle_obj=FloatRect(obj->sprite.getPosition().x + obj->sprite.getGlobalBounds().width / 4, obj->sprite.getPosition().y - obj->sprite.getGlobalBounds().height, obj->textures->getSize().x / 4, (obj->sprite.getGlobalBounds().height));

	

	while (cur)
	{
	 if (dynamic_cast<Turtle*> (cur))
	 { 
		 if (cur->heading)
			 rect_turtle_cur = FloatRect(cur->sprite.getPosition().x - cur->sprite.getGlobalBounds().width / 2, cur->sprite.getPosition().y - cur->sprite.getGlobalBounds().height, cur->textures->getSize().x / 4, (cur->sprite.getGlobalBounds().height));
		 else
			 rect_turtle_cur= FloatRect(cur->sprite.getPosition().x + cur->sprite.getGlobalBounds().width / 4, cur->sprite.getPosition().y - cur->sprite.getGlobalBounds().height, cur->textures->getSize().x / 4, (cur->sprite.getGlobalBounds().height));

		if (cur != obj and rect_turtle_obj.intersects(rect_turtle_cur))
			{
				
				if (onFloor(cur)) {
					if (cur->checkTurtleCollusionable and obj->checkTurtleCollusionable)
					{ 
					obj->headOnTurtle = true; 
					cur->headOnTurtle = true;
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
					

					//turtle->setSpeed(0, 0);
					turtle->state = 4;

					turtle->fallFree = true;
					cout << "Bazý þeyler yaþandý";

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



bool Game::checkCollusion(Turtle* t, Mario* mario, int& side)
{
	FloatRect rect_p(mario->sprite.getPosition().x - mario->sprite.getGlobalBounds().width / 2, mario->sprite.getPosition().y - mario->sprite.getGlobalBounds().height / 4, mario->textures->getSize().x, (mario->sprite.getGlobalBounds().height / 4));
	FloatRect rect_turtle = FloatRect(t->sprite.getPosition().x - t->sprite.getGlobalBounds().width / 2, t->sprite.getPosition().y - t->sprite.getGlobalBounds().height, t->textures->getSize().x, (t->sprite.getGlobalBounds().height) / 4); // (x, y, width, height)


	if (rect_p.intersects(rect_turtle))
	{
		return true;
	}
		
}

/*
bool Game::checkCollusion(Turtle* t, Mario* mario, int& side)
{
	//FloatRect rect_p(mario->sprite.getPosition().x - mario->sprite.getGlobalBounds().width / 2, mario->sprite.getPosition().y - mario->sprite.getGlobalBounds().height / 4, mario->textures->getSize().x, (mario->sprite.getGlobalBounds().height / 4));
	//FloatRect rect_turtle = FloatRect(t->sprite.getPosition().x - t->sprite.getGlobalBounds().width / 2, t->sprite.getPosition().y - t->sprite.getGlobalBounds().height, t->textures->getSize().x, (t->sprite.getGlobalBounds().height) / 4); // (x, y, width, height)

	FloatRect rectTurtle = t->sprite.getGlobalBounds();
	FloatRect rectMario = mario->sprite.getGlobalBounds();


	if ((rectMario.top+ rectMario.height >= rectTurtle.top ))

		return true; 
}

*/

void Game::checkTurtleHitTheBrick()
{		
	Object* obj= objects;
	while (obj)
	{
		if (Turtle* turtle = dynamic_cast<Turtle*>(obj))
		{
			FloatRect rect(turtle->sprite.getPosition().x - turtle->sprite.getGlobalBounds().width / 2,
				turtle->sprite.getPosition().y - turtle->sprite.getGlobalBounds().height / 2,
				turtle->textures->getSize().x,
				(turtle->sprite.getGlobalBounds().height / 2)); // (x, y, width, height) 
			if (hitSprite and turtle->sprite.getGlobalBounds().intersects(hitSprite->getGlobalBounds()))
			{
				turtle->fallFree = false;
				turtle->state = 4;
				
				delete hitSprite;
				hitSprite = new Sprite(newBrick);
				return; 

			}
		}
		obj = obj->next;
	}

	delete hitSprite;
	hitSprite = new Sprite(newBrick);
		
	
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
				//cout << "Buraya geldi mi " << mario->getScore() << endl;
				removeObjects(cur);
				return; 


			}
		}
		else {

			if (cur->getPosition().y > window->getSize().y+100)
			{

				//cout << "buraya geldik"<<endl;
				mario->DirJ = mario->STABLE;
				mario->setPosition(Vector2f(float(Pipe[0].getSize().x + 55), float(window->getSize().y - (floor.getSize().y + Pipe[0].getSize().y + 45))));
				mario->state = 0;
				mario->setLives(1);
				int del_index = (mario->getLives());
				//cout << "Siliyor"<<del_index;
				delete liveSprite[del_index];
				


			}

		}
		cur=cur->next;
	}
}