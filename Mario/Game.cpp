#include "Game.h"

Game::Game() //Game(int speed) {this->speead;...}
{
	window =new RenderWindow(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "MARIO GAME");
	
	if (!floor.loadFromFile("../assets/floor.png")) //We added exception later on
	{
		cout << "File could not be found" << endl;
	}
	if (!Pipe[0].loadFromFile("../assets/pipe.png")) //We added exception later on
	{
		cout << "File could not be found" << endl;
	}
	floor.setRepeated(true);
	floorSprite.setTexture(floor);
	floorSprite.setTextureRect(sf::IntRect(0,0, window->getSize().x, floor.getSize().y));
	floorSprite.setPosition(0, window->getSize().y - (floor.getSize().y+100));
	pipeSprite[0].setTexture(Pipe[0]);
	pipeSprite[0].setPosition(window->getSize().x-(Pipe[0].getSize().x), window->getSize().y - (floor.getSize().y + Pipe[0].getSize().y + 100));
	pipeSprite[1].setTexture(Pipe[0]);
	pipeSprite[1].setScale(-1.f, 1.f);
	pipeSprite[1].setPosition(Pipe[0].getSize().x, window->getSize().y - (floor.getSize().y + Pipe[0].getSize().y + 100));
	pipeSprite[2].setTexture(Pipe[1]);
	pipeSprite[3].setTexture(Pipe[1]);
	pipeSprite[3].setScale(-1.f, 1.f);
	pipeSprite[4].setTexture(Pipe[2]);
	pipeSprite[5].setTexture(Pipe[2]);
	pipeSprite[5].setScale(-1.f, 1.f);
	pipeSprite[6].setTexture(Pipe[3]);
	pipeSprite[7].setTexture(Pipe[3]);
	pipeSprite[7].setScale(-1.f, 1.f);
	Brick[0].setRepeated(true);
	brickSprite[0].setTexture(Brick[0]);
	brickSprite[0].setTextureRect(IntRect(100, 0, 150, 200));

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
		}

		window->clear();
		window->draw(floorSprite);
		window->draw(pipeSprite[0]);
		window->draw(pipeSprite[1]);
		window->draw(pipeSprite[2]);
		window->draw(pipeSprite[3]);
		window->display();
		sleep(milliseconds(1000/speed));

	}
}
