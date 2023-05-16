#include "Game.h"
#include "Turtle.h"
Game::Game(RenderWindow* window)
{
	this->window = window;
	drawBackground(*window);
	//for (int i = 0; i < NUM_TURTLES; i++)
	//{
	//	turtle = addTurtle();
	//	turtle->setPosition(Vector2f(Pipe[1].getSize().x + sira, Pipe[1].getSize().y));
		
	//}

	srand(time(0));
	appear_turtle = rand() % 20 + 5;

	mario = addMario();
	mario->setPosition(Vector2f(float(Pipe[0].getSize().x +55), float(window->getSize().y - (floor.getSize().y + Pipe[0].getSize().y +27))));
} 


void Game::drawBackground(RenderWindow& window) {
	if (!floor.loadFromFile("../assets/floor.png")) //We added exception later on
	{
		cout << "File could not be found" << endl;
	}
	if (!Pipe[0].loadFromFile("../assets/pipe.png")) //We added exception later on
	{
		cout << "File could not be found" << endl;
	}

	if (!Pipe[1].loadFromFile("../assets/pipeS.png")) //We added exception later on
	{
		cout << "File could not be found" << endl;
	}

	if (!Brick.loadFromFile("../assets/brick.png")) //We added exception later on
	{
		cout << "File could not be found" << endl;
	}

	if (!LiveMario.loadFromFile("../assets/mariohead.png")) //We added exception later on
	{
		cout << "File could not be found" << endl;
	}

	
	if (!font.loadFromFile("../assets/font.ttf"))
	{
		cout << "Font could not be found" << endl; 
	}

	floor.setRepeated(true);
	floorSprite.setTexture(floor);
	floorSprite.setTextureRect(IntRect(0, 0, window.getSize().x, floor.getSize().y));
	floorSprite.setPosition(0.0f, float(window.getSize().y - (floor.getSize().y + 100)));
	
	

	// select the font
	text.setFont(font); // font is a sf::Font
	// set the string to display
	text.setString(scoreboard.getScore());
	// set the character size
	text.setCharacterSize(36); // in pixels, not points!
	text.setPosition(10 , 5);
	// set the color
	//text.setFillColor(sf::Color::Red);

	
	for (int i = 0; i < size(liveSprite); i++)
	{
		liveSprite[i].setTexture(LiveMario);
		liveSprite[i].setPosition(initial_live_s, 60);
		initial_live_s += LiveMario.getSize().x;
	}

	pipeSprite[0].setTexture(Pipe[0]);
	//pipeSprite[0].setOrigin(pipeSprite[0].getTextureRect().width / 2.0f, pipeSprite[0].getTextureRect().height);
	pipeSprite[0].setPosition(float(window.getSize().x - (Pipe[0].getSize().x)), float(window.getSize().y - (floor.getSize().y + Pipe[0].getSize().y + 100)));
	
	pipeSprite[1].setTexture(Pipe[0]);
	//pipeSprite[1].setOrigin(pipeSprite[1].getTextureRect().width / 2.0f, pipeSprite[1].getTextureRect().height);
	pipeSprite[1].setScale(-1.f, 1.f);
	pipeSprite[1].setPosition(float(Pipe[0].getSize().x), float(window.getSize().y - (floor.getSize().y + Pipe[0].getSize().y + 100)));
	
	pipeSprite[2].setTexture(Pipe[1]);
	//pipeSprite[2].setOrigin(pipeSprite[2].getTextureRect().width / 2.0f, pipeSprite[2].getTextureRect().height);
	pipeSprite[2].setPosition(0, float(Pipe[1].getSize().y));


	pipeSprite[3].setTexture(Pipe[1]);
	//pipeSprite[3].setOrigin(pipeSprite[3].getTextureRect().width / 2.0f, pipeSprite[3].getTextureRect().height);
	pipeSprite[3].setScale(-1.f, 1.f);
	pipeSprite[3].setPosition(float(window.getSize().x), float(Pipe[1].getSize().y));

	//cout << "Settling pipes: 0, " << float(Pipe[1].getSize().y);
	//cout<<"right" << float(window.getSize().x) << ", " << float(Pipe[1].getSize().y) << endl;
	//cout << pipeSprite[2].getGlobalBounds().height << "  " << pipeSprite[2].getGlobalBounds().width;
	
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

	//mario.setPosition(Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));
/**/
}

void Game::update(void)
{
	while (window->isOpen())
	{

		Event event;
		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
				window->close();
			if (event.type == Event::KeyPressed)
			{
				if(!mario->atJumpingState) {
					Vector2f prevPos = mario->getPosition();
					//cout << "PrevPos " << prevPos.x<<" " << prevPos.y << endl;
					 if (event.key.code == Keyboard::Up)
					{
						//cout << "Selam" << endl; 
						//mario->move(Object::Directions::UP);
						mario->state = 5;
						mario->prev_y = mario->sprite.getPosition().y;
	
					}
					else if (event.key.code == Keyboard::Right)
					 {
						 
						 if (Keyboard::isKeyPressed(Keyboard::Up))
						 {
							 mario->state = 5;
							 mario->prev_y = mario->sprite.getPosition().y;
							 mario->DirJ = Object::Directions::RIGHT;
						 }
						 else
							mario->move(Object::Directions::RIGHT);
					}
					else if (event.key.code == Keyboard::Left)
					{
						 if (Keyboard::isKeyPressed(Keyboard::Up))
						 {
							 mario->state = 5;
							 mario->prev_y = mario->sprite.getPosition().y;
							 mario->DirJ = Object::Directions::LEFT;
						 }
						 else
							 mario->move(Object::Directions::LEFT);
					}
					if (checkBoundary(mario))
					{
						cout << "Fonksiyona girdi" << mario->getPosition().x << "   " << mario->getPosition().y;
						mario->setSpeed(0, 0);
						mario->setPosition(prevPos);
					}
					prevKeyCode = event.key.code;
					//Object::Directions prevkeyDir = event.key.code;
					cout << "Event" << event.key.code << endl;
				}
				else {
					if (event.key.code == Keyboard::Left)
					{
						mario->DirJ = Object::Directions::LEFT;
					}
					else if (event.key.code == Keyboard::Right)
					{
						mario->DirJ = Object::Directions::RIGHT;
					}
				}
			}
			
			else 
				//if (event.type != Event::KeyPressed and prevKeyCode != 723)
			{
				cout << "YOK Event" << prevKeyCode<<endl;
				if(prevKeyCode != Keyboard::Up){
				mario->state = 0;
				mario->sprite.setTexture(mario->textures[mario->state]);}
				//mario->move(Object::Directions::STABLE);
				//cout << "!" << event.key.code << endl;
			}

		}
		if (temp_appear == appear_turtle and n_turtle!=NUM_TURTLES)
		{
			//cout << "Appear turtle num: " <<appear_turtle<<endl;
			heading = rand() % 2;
			turtle = addTurtle(heading);
			if (!heading)
			turtle->setPosition(Vector2f(Pipe[1].getSize().x, Pipe[1].getSize().y-10)); //+28
			else turtle->setPosition(Vector2f(float(window->getSize().x-Pipe[1].getSize().x), Pipe[1].getSize().y - 10));
			cout << Pipe[1].getSize().x << endl;
			appear_turtle+= rand() % 30 + 5;
			n_turtle += 1;
		}
		temp_appear += 1;
		window->clear();
		window->draw(floorSprite);
		for (int i = 0; i < size(pipeSprite); i++) window->draw(pipeSprite[i]);
		
		for (int i = 0; i < size(brickSprite); i++) window->draw(brickSprite[i]);
		
		for (int i = 0; i < size(liveSprite); i++) window->draw(liveSprite[i]);

		drawObjects(); 
		
		window->draw(text);
		window->display();
		sleep(milliseconds(1000/speed));

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
Mario* Game::addMario(void)
{
	Mario* mario = new Mario(window);
	mario->next = objects;
	objects = mario;
	return mario;
}
 
void Game::drawObjects(void)
{
	Object* cur = objects;
	while (cur)
	{
		if (dynamic_cast<Turtle*> (cur))
		{
			if (onFloor(cur))
			{
				cur->setSpeed(10.0f, 0.0f);
				//cur->sprite.move(10, 0);
			}
			else
			{
				cur->setSpeed(0.0f, 5.0f);
				//cur->sprite.move(0, 20);
			};
			//cout <<"Turtle pos x: "<< cur->getPosition().x <<"  y:" << cur->getPosition().y <<"Headin"<<cur->heading << endl;
			if (cur->getPosition().x < 10.0f and cur->heading == 1)
			{
				//cout << "************************" << endl;
				cur->sprite.setScale(1.f, 1.f);
				cur->heading = 0;
			}
			else if (cur->getPosition().x > 950 and cur->heading == 0)
			{
				cur->sprite.setScale(-1.f, 1.f);
				cur->heading = 1;

				//cur->setPosition(Vector2f(1.0f, cur->getPosition().y));
			};

			if (pipeSprite[0].getGlobalBounds().intersects(cur->sprite.getGlobalBounds()))
			{
				//cout << "Pipe ile kesiþti+++++++++++++++++++++++++++++++++" << endl;
				cur->setPosition(Vector2f(float(window->getSize().x - Pipe[1].getSize().x), Pipe[1].getSize().y - 10));
				cur->sprite.setScale(-1.f, 1.f);
				cur->heading = 1;
			}

			if (pipeSprite[1].getGlobalBounds().intersects(cur->sprite.getGlobalBounds()))
			{
				cout << "Pipe ile kesiþti////////////////"<<cur->heading<<endl;
				cur->setPosition(Vector2f(Pipe[1].getSize().x, Pipe[1].getSize().y - 10)); //+28
				cur->sprite.setScale(1.f, 1.f);
				cur->heading = 0;
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
			if (prev)	prev->next = cur->next;

			else objects = cur->next;

			delete cur;
			return;
		}
	
	prev = cur;
	cur = cur->next; 
	}


}
bool Game::onFloor(Object* obj)
{
	for (int i = 0; i < size(brickSprite); i++)
	{
		if (obj->sprite.getGlobalBounds().intersects(brickSprite[i].getGlobalBounds()) or floorSprite.getGlobalBounds().intersects(obj->sprite.getGlobalBounds()))
		{
			//cout << " Height, " << obj->sprite.getGlobalBounds().height << " Width " << obj->sprite.getGlobalBounds().width << " Top " << obj->sprite.getGlobalBounds().top << " Left " << obj->sprite.getGlobalBounds().left << endl;
			//cout << "Intercept point i think  " << obj->sprite.getGlobalBounds().top + obj->sprite.getGlobalBounds().height << endl; 
			//cout<< "BRICK Sprite Height "<< brickSprite[i].getGlobalBounds().height << " Width " << brickSprite[i].getGlobalBounds().width << " Top " << brickSprite[i].getGlobalBounds().top << " Left " << brickSprite[i].getGlobalBounds().left << endl;
			FloatRect rect(obj->sprite.getPosition().x, obj->sprite.getPosition().y+ obj->sprite.getGlobalBounds().height / 2, obj->textures->getSize().x, (obj->sprite.getGlobalBounds().height / 2)); // (x, y, width, height)
			//cout << " RECT Height, " << rect.height << " Width " << rect.width << " Top " << rect.top << " Left " << rect.left << endl;

			if (rect.intersects(brickSprite[i].getGlobalBounds()) or rect.intersects(floorSprite.getGlobalBounds())) return true;
			
		}
	}
	return false;


}

bool Game::checkBoundary(Object* obj)
{
	
	FloatRect rect_mar(obj->sprite.getPosition().x - obj->sprite.getGlobalBounds().width / 2, obj->sprite.getPosition().y - (obj->textures->getSize().y / 2), (obj->sprite.getGlobalBounds().width), obj->textures->getSize().y/2); // (x, y, width, height)
	FloatRect rect_mar2(obj->sprite.getPosition().x , obj->sprite.getPosition().y- (obj->textures->getSize().y / 2), (obj->sprite.getGlobalBounds().width / 2), obj->textures->getSize().y); // (x, y, width, height)

	if (rect_mar2.intersects(pipeSprite[0].getGlobalBounds()) or rect_mar.intersects(pipeSprite[1].getGlobalBounds()))
		//or  obj->getPosition().x< 0 )
		//or obj->getPosition().x> WINDOW_WIDTH)
	{
		cout << "checkboundary e girdi" << endl;
		cout <<obj->getPosition().x << endl;
		
		return true;
	}

	else if (obj->sprite.getPosition().x > window->getSize().x  or obj->sprite.getPosition().x< 0.0f )
	{
		//cout << "True" << obj->sprite.getPosition().x << window->getSize().x ;
		return true;
	}

	else { 
		//cout << obj->sprite.getPosition().x <<"   " << window->getSize().x << "   " << (obj->sprite.getPosition().x > window->getSize().x);
		
		return false; }
}

