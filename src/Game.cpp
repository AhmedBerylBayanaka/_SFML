#include <iostream>
#include "Game.hpp"

void Game::initVariables()
{
    this->window = nullptr; //to initiation

        this->endgame = false;
        this->point = 0;
        this->enemySpawnTimerMax = 20.f;
        this->enemySpawnTimer = this->enemySpawnTimerMax;
        this->maxEnemies = 10;
        this->mouseHeld = false;
        this->HP = 1;

}

void Game::initWindow()
{
    this->VideoMode.height = 600;
    this->VideoMode.width  = 800;

    this->window = new sf::RenderWindow(this->VideoMode, "Deutronopia", sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(60);
}

void Game::initFonts()
{
    if(this->font.loadFromFile("Font/HighlandGothicFLF.ttf"))
    {
        std::cout << "Failed to Load font" << "\n";
    }
}

void Game::initTexts()
{
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(24);
    this->uiText.setFillColor(sf::Color::White);
    this->uiText.setString("NONE");
}

void Game::initEnemies()
{

    this->enemy1.setSize(sf::Vector2f(100.f,100.f));
    this->enemy1.setScale(sf::Vector2f(0.5f, 0.5f));
    this->enemy1.setFillColor(sf::Color::Yellow);

}

// Constructor
Game::Game()
{
   this->initVariables();
   this->initWindow();
   this->initFonts();
   this->initTexts();
   this->initEnemies();
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

const bool Game::getEndgame() const
{
    return this->endgame;
}

// Functions
void Game::spawnEnemies()
{
    this->enemy1.setPosition(
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy1.getSize().x)),
        0.f
    );

    //Randomize Type
    int type = rand() % 6;

    switch(type)
    {
        case 0:
            this->enemy1.setSize(sf::Vector2f(40.f,40.f));
            this->enemy1.setFillColor(sf::Color(195,70,70));
            break;
        case 1:
            this->enemy1.setSize(sf::Vector2f(80.f,80.f));
            this->enemy1.setFillColor(sf::Color(79,195,70));
            break;
        case 3:
            this->enemy1.setSize(sf::Vector2f(50.f,50.f));
            this->enemy1.setFillColor(sf::Color::Blue);
            break;
        case 4:
            this->enemy1.setSize(sf::Vector2f(20.f,20.f));
            this->enemy1.setFillColor(sf::Color::Yellow);
            break;
        case 5:
            this->enemy1.setSize(sf::Vector2f(80.f,80.f));
            this->enemy1.setFillColor(sf::Color::Cyan);
            break;
        default:
            this->enemy1.setSize(sf::Vector2f(100.f,100.f));
            this->enemy1.setFillColor(sf::Color::White);
            break;
    }

    this->enemies.push_back(this->enemy1);

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
            default :
                break;
			}
		}
}

void Game::updateMousePos()
{
    this->mousePos = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePos);
}

void Game::updateText()
{
    std::stringstream ss;

    ss << "Points : " << this->point;
        //<< "Health of Green: " << this->HP

    this->uiText.setString(ss.str());
}

void Game::updateEnemies()
{
    if(this->enemies.size() < this->maxEnemies )
    {
        if(this->enemySpawnTimer >= this->enemySpawnTimerMax)
        {
            this->spawnEnemies();
            this->enemySpawnTimer = 0.f;
        }
        else
            this->enemySpawnTimer += 1.f;
    }


    bool deleted = false;
    for(int i = 0; i < this->enemies.size(); i++)
    {

        this->enemies[i].move(0.f,3.f);

        if(this->enemies[i].getPosition().y > this->window->getSize().y)
        {
            this->enemies.erase(this->enemies.begin() + i);
                //std:: cout << "Enemies Health = " << this->HP << "\n";
        }

    }

    //delete if clicked
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(this->mouseHeld == false)
        {
            this->mouseHeld = true;
            for(int i = 0; i < this->enemies.size(); i++)
            {
                if(this->enemies[i].getGlobalBounds().contains(this->mousePosView))
                {
                    if(this->enemies[i].getFillColor() == sf::Color(195,70,70))
                        this->point += 10;
                    else if (this->enemies[i].getFillColor() == sf::Color(79,195,70))
                        this->point += 5;
                    else if (this->enemies[i].getFillColor() == sf::Color::Blue)
                        this->point -= 5;
                    else if (this->enemies[i].getFillColor() == sf::Color::Yellow)
                        this->point -= 6;
                    else if (this->enemies[i].getFillColor() == sf::Color::Cyan)
                        this->point -= 7;
                        
                    std:: cout << "Score = " << this->point << "\n";

                    deleted =  true;
                    this->enemies.erase(this->enemies.begin() + i);

                }
            }
        }
        else 
        {
            this->mouseHeld = false;
        }
    }

}

void Game::update()
{
    this->pollEvents();

    if(!this->endgame)
    {
        this->updateMousePos();

        this->updateText();

        this->updateEnemies();
    }

    if(this->point >= 100)
    {
        this->endgame = true;
    }
    
}

void Game::renderText(sf::RenderTarget& target)
{
    target.draw(this->uiText);
}

void Game::renderEnemies(sf::RenderTarget& target)
{
    for(auto &e : this->enemies)
    {
        this->window->draw(e);
    }

}

void Game::render()
{
    this->window->clear(sf::Color(195, 141, 70));

    //game drawing
    this->renderEnemies(*this->window);

    this->renderText(*this->window);

    this->window->display();
}
