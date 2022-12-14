#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

//the game engine B-)

class Game
{
    private:
        //Variables
        //Window
        sf::RenderWindow* window; //for outputing window
        sf::VideoMode VideoMode; //for window conf
        sf::Event ev; //for the event(s) that happens

        //objects
        sf::RectangleShape enemy;

        //Private Func.
        void initVariables();
        void initWindow();
        void initEnemies();

    public:
        //constructor / destructors
        Game();
        virtual ~Game();

        //accessors
        const bool getWindowIsOpen() const; //so the engine knows if they should start working

        //functions
        void pollEvents();
        void update();
        void render();
};