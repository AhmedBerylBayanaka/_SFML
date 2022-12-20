#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <vector>
#include <sstream>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"

//the game engine B-)


class Game
{
    private:
        //Variables
        //Window
        sf::RenderWindow* window; //for outputing window
        sf::VideoMode VideoMode; //for window conf
        sf::Event ev; //for the event(s) that happens

        //Mouse Positions
        sf::Vector2i mousePos;
        sf::Vector2f mousePosView;

        //cout
        sf::Font font;
        sf::Text uiText;

        bool endgame;
        signed point;
        unsigned HP;
        float enemySpawnTimer;
        float enemySpawnTimerMax;
        int maxEnemies;
        bool mouseHeld;
    //objects

        //enemy
        std::vector<sf::RectangleShape> enemies;
        sf::RectangleShape enemy1;

        //Private Func.
        void initVariables();
        void initWindow();
        void initFonts();
        void initTexts();
        void initEnemies();

    public:
        //constructor / destructors
        Game();
        virtual ~Game();

        //accessors
        const bool getWindowIsOpen() const; //so the engine knows if they should start working
        const bool getEndgame() const;

        //functions
        void spawnEnemies();

        void pollEvents();
        void updateMousePos();
        void updateText();
        void updateEnemies();
        void update();


        void renderText(sf::RenderTarget& target);
        void renderEnemies(sf::RenderTarget& target);
        void render();
};

#endif