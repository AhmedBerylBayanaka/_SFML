#include <iostream>
#include "Game.hpp" //akses header class
#include <ctime>

using namespace sf;

int main() {

  //random number
  std::srand(static_cast<unsigned>(time(NULL)));

  //call the engine!
  Game game;

	//Game Loop!
	while (game.getWindowIsOpen() && !game.getEndgame())
	{
		//Update
    game.update();

		//Render
    game.render();

	}

	return 0;
}