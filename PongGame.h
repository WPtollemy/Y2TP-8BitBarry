//This class strings together the individual games

#ifndef GAME_H
#define GAME_H

#include <SFML\Graphics.hpp>
#include "Pong.h"

class PongGame
{
	private:
		sf::RenderWindow* window;

		//Below are instances of games...
		Pong* pong;

		sf::Font font;
		sf::Text text;

		void processEvents();

	public:
		//Constructor -- destructor
		PongGame(sf::RenderWindow* = nullptr);
		~PongGame();

		void run();

		sf::RenderWindow* getWindow();

};

#endif // !GAME_H

