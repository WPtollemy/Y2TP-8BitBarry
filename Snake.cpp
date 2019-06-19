// Snake2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Snake.h"
#include <string>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>

using namespace sf;

/*
	Constructor -- Destructor
*/
SnakeGame::SnakeGame(RenderWindow* window) 
: window(window) {

	initialise();
}

SnakeGame::~SnakeGame() {

}


void SnakeGame::initialise() {
	t1.loadFromFile("res/Snake/images/black.png");
	t2.loadFromFile("res/Snake/images/fullwhite.png");

	sprite1 = sf::Sprite(t1);
	sprite2 = sf::Sprite(t2);

	boundary = sf::RectangleShape(sf::Vector2f(w + size, h + size));
	boundary.setFillColor(sf::Color::Black);
	boundary.setOutlineColor(sf::Color::White);
	boundary.setOutlineThickness(3);

	boundary.setPosition(offset, offset);

	font.loadFromFile("res/Snake/Pixellari.ttf");
	keyFragments.setFont(font);
	keyFragments.setPosition(685, 50);
	keyFragments.setCharacterSize(14);
	keyFragments.setString("Key Fragments:");

	scoreText.setFont(font);
	scoreText.setPosition(685, 75);
	scoreText.setCharacterSize(24);
	scoreText.setString(std::to_string(score));
}


void SnakeGame::tick() // deals with the animation/movement
{
	for (int i = num; i> 0; --i) // ensures the growing snake tail follows the head
	{
		snake[i].x = snake[i - 1].x;
		snake[i].y = snake[i - 1].y;
	}

	// handels direction - by adjusting head of snake (snake[0]) 
	if (dir == 0) { // down
		snake[0].y += 1;
	}
	if (dir == 1) { // left
		snake[0].x -= 1;
	}
	if (dir == 2) { // right
		snake[0].x += 1;
	}
	if (dir == 3) { // up
		snake[0].y -= 1;
	}

	if ((snake[0].x == food.x) && (snake[0].y == food.y)) { //if snake eats food
		num++;
		score++;
		scoreText.setString(std::to_string(score));

		food.x = rand() % N;
		food.y = rand() % M;
	}

	//Wraps snake around - so snake cant leave screen
	if (snake[0].x>N) snake[0].x = 0;
	if (snake[0].x<0) snake[0].x = N;
	if (snake[0].y>M) snake[0].y = 0;
	if (snake[0].y<0) snake[0].y = M;

	//If collision
	for (int i = 1; i< num; i++) {
		if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
			
			//num = -1
			num = 4;
			score = 0;
			scoreText.setString(std::to_string(score));
			
			if (!isStory) {
				running = false;	//If not story then game continues
			}
		}
	}
}

void SnakeGame::render() {

	window->clear();

	window->draw(boundary);
	window->draw(keyFragments);
	window->draw(scoreText);

	for (int i = 0; i< num; i++) //draw snake 
	{
		sprite2.setPosition(snake[i].x*size + offset, snake[i].y*size + offset);  // i = each block of the snake
		window->draw(sprite2);
	}

	sprite2.setPosition(food.x*size + offset, food.y*size + offset);
	window->draw(sprite2); // draw food 

	window->display();
}

void SnakeGame::run(int limit, bool isStory) {
	
	this->isStory = isStory;
	

	//Texture t1, t2;
	//initialise();
	score = 0;
	num = 4;

	scoreText.setString(std::to_string(score));

	Clock clock;
	float timer = 0, delay = 0.1;

	food.x = 10;
	food.y = 10;

	running = true;

	while (running)
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		Event e;
		while (window->pollEvent(e))
		{
			if (e.type == Event::Closed)
				window->close();
		}

		/*
		if (Keyboard::isKeyPressed(Keyboard::Left)) dir = 1;
		if (Keyboard::isKeyPressed(Keyboard::Right))  dir = 2;
		if (Keyboard::isKeyPressed(Keyboard::Up)) dir = 3;
		if (Keyboard::isKeyPressed(Keyboard::Down)) dir = 0;
		*/

		//Handles direction and prevents snake going back on itself
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			if(dir != 2)
				dir = 1;
		} if (Keyboard::isKeyPressed(Keyboard::Right)) {
			if (dir != 1)
				dir = 2;
		} if (Keyboard::isKeyPressed(Keyboard::Up)) {
			if (dir != 0)
				dir = 3;
		} if (Keyboard::isKeyPressed(Keyboard::Down)) {
			if (dir != 3)
				dir = 0;
		}if (Keyboard::isKeyPressed(Keyboard::M)) {
			running = false;
		}


		if (timer > delay) {
			timer = 0; tick();
		}
		
		if (score >= limit)
			running = false;

		render();

		
	}
}
