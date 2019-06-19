#ifndef PONG_H
#define PONG_H

#include <SFML\Graphics.hpp>

class Pong
{
	private:
		enum Walls
		{
			Upper, Lower, Left, Right
		};

		sf::RenderWindow* window;
		sf::Vector2f windowSize;

		sf::RectangleShape bounds;

		sf::RectangleShape playerComp;
		sf::RectangleShape playerPerson;
		sf::RectangleShape ball;

		std::vector<sf::RectangleShape> centreLine;

		bool quit = false;
		bool stillGoing = true;
		bool didWin;

		void processEvents();
		void update(sf::Time);
		void render();

		void updateBall(sf::Time);
		void bounce(Walls);
		sf::Vector2f ballDirection;

		void generateCentreLine();

		void handlePlayerInput(sf::Keyboard::Key, bool);

		void resetBall();

	private:
		bool isMovingUp = false;
		bool isMovingDown = false;

		bool compUp = false;

		int scores[2] = {0,0};	//Comp score, player score
		int noRounds;

	public:
		//Constructor -- destructor
		Pong(sf::RenderWindow*, int);
		~Pong();

		bool run();
};

#endif // !GAME_H
