#ifndef SNAKE_H
#define SNAKE_H

#include <SFML\Graphics.hpp>

class SnakeGame {

	struct Snake
	{
		int x, y;
	}  snake[100];

	struct Fruct
	{
		int x, y;
	} food;

	private:
		sf::RenderWindow* window;
		
		//int N = 30, M = 20;
		//int N = 37, M = 28;
		int N = 40, M = 43;
		int size = 16;
		int w = size*N;
		int h = size*M;
		int score = 0;

		int dir, num = 4;

		int offset = 16;

		bool running;
		bool isStory = false;

		sf::Texture t1, t2;
		sf::Sprite sprite1, sprite2;
		sf::RectangleShape boundary;

		//Text
		sf::Font font;
		sf::Text keyFragments, scoreText;

	private:
		void initialise();
		void tick();
		void render();

	public:
		/* Constructor -- Destructor */
		SnakeGame(sf::RenderWindow* = nullptr);
		~SnakeGame();


		void run(int = 7, bool = false);

};

#endif // !SNAKE_H
