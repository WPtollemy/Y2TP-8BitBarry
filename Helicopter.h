#ifndef HELICOPTER_H
#define HELICOPTER_H
#pragma once
#include <SFML\Graphics.hpp>
#include <vector>

class Helicopter
{
	private:
		sf::RenderWindow* window;

		sf::CircleShape playerTest;

		sf::Texture playerText;
		sf::Sprite player;

		sf::Texture pacmanTexture;
		sf::Sprite pacMan;

		float spriteMulitplier = 0.03;
		sf::Vector2f spriteVector;

		std::vector<sf::RectangleShape> rectangles;
		std::vector<sf::RectangleShape> walls;

	private:
		//Dimensions
		sf::Vector2f pathRectSize;
		sf::Vector2f wallRectSize;

	public:
		//Constructor -- destructor
		Helicopter(sf::RenderWindow*);
		~Helicopter();

		void handlePlayerInput(sf::Keyboard::Key, bool);
		void handlePlayerInput(sf::Mouse::Button, bool);

		void update(sf::Time);
		void processEvents();
		void run();
		void render();

		void initialisePath();
		void initialiseWalls();
		void updatePath(sf::Time);
		int createRandomHeight();
		bool determineElapsedTime(std::clock_t);
		void resetEverything();
		void startEverything();
};

#endif // !HELICOPTER_H
