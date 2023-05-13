#include "Game.h"
#include "Turtle.h"
Game::Game(RenderWindow* window): mario(window),turtle(window) //Game(int speed) {this->speead;...}
{
	this->window = window;
	drawBackground(*window);
	
	
	// turtles = new Turtle[NUM_TURTLES];
	/*
	for (int=0 ; i< NUM_TURTLES; i++)
		{
		turtles[i].setPosition(...);
		}
	
	*/
	
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
		liveSprite[i].setPosition(initial, 60);
		initial += LiveMario.getSize().x;
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
	
	turtle.setPosition(Vector2f(Pipe[1].getSize().x, Pipe[1].getSize().y));
	mario.setPosition(Vector2f(float(Pipe[0].getSize().x+65) , float(window.getSize().y - (floor.getSize().y + Pipe[0].getSize().y + 115 ))));


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
				if (event.key.code == Keyboard::Up)
				{
					mario.move(Object::Directions::UP);
				}
				else if (event.key.code == Keyboard::Down)
				{
					mario.move(Object::Directions::DOWN);
				}
				else if (event.key.code == Keyboard::Right)
				{
					mario.move(Object::Directions::RIGHT);
				}
				else if (event.key.code == Keyboard::Left)
				{
					mario.move(Object::Directions::LEFT);
				}
			}
			else mario.move(Object::Directions::STABLE);

		}

		window->clear();
		window->draw(floorSprite);
		for (int i = 0; i < size(pipeSprite); i++) window->draw(pipeSprite[i]);
		
		for (int i = 0; i < size(brickSprite); i++) window->draw(brickSprite[i]);
		
		for (int i = 0; i < size(liveSprite); i++) window->draw(liveSprite[i]);

		turtle.draw(*window);
		mario.draw(*window);
		
		window->draw(text);
		window->display();
		sleep(milliseconds(1000/speed));

	}
}
Game::~Game()
{
	//delete window ;
}