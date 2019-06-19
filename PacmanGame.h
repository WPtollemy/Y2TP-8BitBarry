#ifndef PACMAN_GAME_H
#define PACMAN_GAME_H

#include "StateManager.h"
#include "GameSetter.h"
#include <SFML/Graphics.hpp>

class PacmanGame {

	private:
		sf::RenderWindow* window;

		edy::core::StateManager game;

	public:
		/* Constructor -- Destructor */
		PacmanGame(sf::RenderWindow*);// = nullptr);
		~PacmanGame();

		void run();
};

#endif // !PACMAN_GAME_H
