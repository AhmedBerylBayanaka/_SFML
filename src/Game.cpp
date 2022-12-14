#include "Game.hpp"

void Game::initVariables()
{
    this->window = nullptr; //to initiation

}

void Game::initWindow()
{
    this->VideoMode.height = 800;
    this->VideoMode.width  = 600;

    this->window = new sf::RenderWindow(this->VideoMode, "Star Plasma", sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(60);
}


void Game::initEnemies()
{
    this->enemy.setPosition(0,0);
    this->enemy.setSize(sf::Vector2f(100.f,100.f));
    this->enemy.setFillColor(sf::Color::Cyan);
    this->enemy.setOutlineColor(sf::Color::Green);
    this->enemy.setOutlineThickness(1.f);
}

// Constructor
Game::Game()
{
   this->initVariables();
   this->initWindow();
}

//Deconstructor
Game::~Game()
{
    /*
    so every time I start the program, the previous one got destroyed first.
    */
    delete this->window;
}

//Accessors
const bool Game::getWindowIsOpen() const
{
    return this->window->isOpen();
}

void Game::pollEvents()
{
    //Event polling
		while(this->window->pollEvent(this->ev))
		{
			switch(this->ev.type)
			{
			case sf::Event::Closed:
				this->window->close();
				break;
			case sf::Event::KeyPressed:
				if (this->ev.key.code == sf::Keyboard::Escape)
				    this->window->close();
				break;
			}
		}
}

// Functions
void Game::update()
{
    this->pollEvents();
}

void Game::render()
{
    this->window->clear();

    //game drawing
    this->window->draw(this->enemy);

    this->window->display();
}
