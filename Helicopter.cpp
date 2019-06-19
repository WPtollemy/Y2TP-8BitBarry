// Helicopter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Helicopter.h"
#include <SFML\Graphics.hpp>
#include <iostream>
#include <ctime>

float speed = 0.0f;
int wallSpeed = 0;
int acceleration = 2, wallMovingUp = 0, pathHeightStreak;
const float MAX_Y = 0.5f;
sf::Vector2f gravity(0.0f, 0.0f);
sf::Vector2f velocity(0.0f, 0.0f);
sf::Vector2f movement(0.0f, 0.0f);

bool isMovingUp = false, isMovingDown = true, isAlive = true, finished = false, pacGoingUp = false;
const sf::Time timePerFrame = sf::seconds(1.f / 60.f);
std::clock_t begin;


Helicopter::Helicopter(sf::RenderWindow* window)
	: pathRectSize(sf::Vector2f(window->getSize().x / 14, 600))
	, wallRectSize(sf::Vector2f(window->getSize().x / 14, 200))
{
	/**/
	sf::Image spriteImage;
	if (!playerText.loadFromFile("HelicopterClone/res/playerSprite.png")) {
		std::cout << "Fail!" << std::endl;
	}
	//barryTexture.loadFromImage(spriteImage);
	this->player.setTexture(playerText);
	this->player.setScale(0.18, 0.18);
	this->player.setPosition(125, window->getSize().y*0.5);

	if (!spriteImage.loadFromFile("HelicopterClone/res/pacmanheli.png")) {
		//ERROR
	}
	pacmanTexture.loadFromImage(spriteImage);
	pacMan.setTexture(pacmanTexture);
	pacMan.setScale(0.18, 0.18);
	pacMan.setPosition(720, window->getSize().y*0.2);

	this->window = window;
	initialisePath();
	initialiseWalls();
}

void Helicopter::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	finished = false;
	resetEverything();

	while (this->determineElapsedTime(begin) && !finished)
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			update(timePerFrame);
			updatePath(timePerFrame);

			for (int i = 0; i < 18; i++) {
				if (rectangles.at(i).getPosition().x + pathRectSize.x < 0) {
					if (wallMovingUp == 1)
						rectangles.at(i).setPosition(rectangles.at((i + 17) % 18).getPosition().x + pathRectSize.x, rectangles.at((i + 17) % 18).getPosition().y - 10);
					else if (wallMovingUp == 0)
						rectangles.at(i).setPosition(rectangles.at((i + 17) % 18).getPosition().x + pathRectSize.x, rectangles.at((i + 17) % 18).getPosition().y + 10);
				}

				if (rectangles.at(i).getPosition().y < 41)
					wallMovingUp = 0;
				else if (rectangles.at(i).getPosition().y + rectangles.at(i).getSize().y > 701)
					wallMovingUp = 1;
				else if (pathHeightStreak % 3 == 0)
					wallMovingUp = std::rand() % 2;

				pathHeightStreak++;
			}

			for (int i = 0; i < 2; i++) {
				if (walls.at(i).getPosition().x + wallRectSize.x < 0)
					walls.at(i).setPosition(walls.at((i + 1) % 2).getPosition().x + (window->getSize().x / 2) + 150, createRandomHeight());
			}
		}

		render();

		if (!isAlive)
			resetEverything();
	}
}

void Helicopter::update(sf::Time deltaTime)
{
	if (isMovingUp)
		velocity.y -= (speed);
	else if (isMovingDown)
		velocity.y += speed;

	player.move(velocity * deltaTime.asSeconds());

	if (velocity.y < MAX_Y)
		velocity += gravity;
}

void Helicopter::render()
{
	window->clear(sf::Color::Green);
	for (sf::RectangleShape rectangle : rectangles) {
		window->draw(rectangle);
	}
	for (sf::RectangleShape wall : walls) {
		window->draw(wall);
	}

	window->draw(player);
	window->draw(pacMan);
	window->display();
}

void Helicopter::processEvents()
{
	sf::Event event;

	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;
		case sf::Event::MouseButtonPressed:
			handlePlayerInput(event.mouseButton.button, true);
			break;
		case sf::Event::MouseButtonReleased:
			handlePlayerInput(event.mouseButton.button, false);
			isMovingDown = true;
			break;
		case sf::Event::Closed: std::cout << "Processing";
			window->close();
		}
	}
}

void Helicopter::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	switch (key) {
	case sf::Keyboard::W:
	case sf::Keyboard::Up:
	{
		isMovingUp = isPressed;
		break;
	}
	case sf::Keyboard::S:
	case sf::Keyboard::Down:
	{
		isMovingDown = isPressed;
		break;
	}
	case sf::Keyboard::M:
		finished = true;
	}
}

void Helicopter::handlePlayerInput(sf::Mouse::Button button, bool isPressed)
{
	switch (button) {
	case sf::Mouse::Left:
	{
		isMovingUp = isPressed;
		if (speed == 0.0f) {
			startEverything();
		}
	}
	}
}

void Helicopter::initialisePath()
{
	int startHeight = ((std::rand() % 10) + 2) * 10;
	startHeight = 20;

	for (int i = 0; i < 18; i++) {
		rectangles.push_back(sf::RectangleShape(pathRectSize));
	}

	//Old height determing by: window->getSize().y / 2 - ((rectangles.at(i).getSize().y) / 2)
	for (int i = 0; i < 18; i++) {
		rectangles.at(i).setFillColor(sf::Color::Black);
		rectangles.at(i).setPosition(i * pathRectSize.x, startHeight);

		if (i == 0 || i == 1)
			rectangles.at(i).setPosition(i * pathRectSize.x, startHeight);
		else if (wallMovingUp == 1)
			rectangles.at(i).setPosition(i * pathRectSize.x, rectangles.at((i + 17) % 18).getPosition().y - 10);
		else if (wallMovingUp == 0)
			rectangles.at(i).setPosition(i * pathRectSize.x, rectangles.at((i + 17) % 18).getPosition().y + 10);

		if (rectangles.at(i).getPosition().y < 51)
			wallMovingUp = 0;
		else if (rectangles.at(i).getPosition().y + rectangles.at(i).getSize().y > 751)
			wallMovingUp = 1;
		else
			wallMovingUp = std::rand() % 2;
	}
}

void Helicopter::initialiseWalls()
{
	for (int i = 0; i < 2; i++) {
		walls.push_back(sf::RectangleShape(wallRectSize));
	}

	for (int i = 0; i < 2; i++) {
		walls.at(i).setFillColor(sf::Color::Green);
		walls.at(i).setPosition(walls.at((i + 1) % 2).getPosition().x + (window->getSize().x / 2) + 150, createRandomHeight());
	}
}

void Helicopter::updatePath(sf::Time deltaTime)
{
	movement = sf::Vector2f(0.0f, 0.0f);
	movement.x -= (speed + wallSpeed) * acceleration;

	for (int i = 0; i < 18; i++) {
		if (player.getGlobalBounds().intersects(rectangles.at(i).getGlobalBounds())) {
			if (player.getPosition().y - (rectangles.at(i).getPosition().y) < (player.getOrigin().y) ||
				player.getPosition().y - (rectangles.at(i).getPosition().y + pathRectSize.y) > (5 - player.getGlobalBounds().height))
				//player.getPosition().y + ((window->getSize().y - pathRectSize.y - rectangles.at(i).getPosition().y)) > (window->getSize().y - player.getOrigin().y - 2))
				isAlive = false;
		}
	}

	for (int i = 0; i < 2; i++) {
		walls.at(i).move(movement * deltaTime.asSeconds());

		if (walls.at(i).getGlobalBounds().intersects(player.getGlobalBounds()))
			isAlive = false;
	}

	for (int i = 0; i < 18; i++) {
		rectangles.at(i).move(movement * deltaTime.asSeconds());
	}

	if (pacMan.getPosition().y > window->getSize().y*0.15 && pacGoingUp == true)
		pacMan.setPosition(pacMan.getPosition().x, pacMan.getPosition().y - 3);
	else if (pacMan.getPosition().y <= window->getSize().y*0.15 && pacGoingUp == true)
		pacGoingUp = false;
	else if (pacMan.getPosition().y < window->getSize().y*0.75 && pacGoingUp == false)
		pacMan.setPosition(pacMan.getPosition().x, pacMan.getPosition().y + 3);
	else if (pacMan.getPosition().y >= window->getSize().y*0.75 && pacGoingUp == false)
		pacGoingUp = true;
}

int Helicopter::createRandomHeight()
{
	int heightToAdd = window->getSize().y / 2 - (pathRectSize.y / 2);
	int newHeight = std::rand() % 375 + heightToAdd;

	return newHeight;
}

bool Helicopter::determineElapsedTime(std::clock_t start)
{
	std::clock_t currentTime = std::clock();
	int timeElapsed = double(currentTime - start) / CLOCKS_PER_SEC;

	switch (timeElapsed) {
	case 0:
		return true;
	case 10:
		acceleration = 3;
		return true;
	case 20:
		acceleration = 4;
		return true;
	case 30:
		acceleration = 5;
		return true;
	case 40:
		acceleration = 6;
		return true;
	case 45:
		speed = 0.f;
		wallSpeed = 0;
		velocity.y = 0.f;
		return false;
	}
}

void Helicopter::resetEverything()
{
	rectangles.clear();
	initialisePath();
	walls.clear();
	initialiseWalls();
	acceleration = 3;
	isAlive = true;
	begin = std::clock();
	player.setPosition(125, window->getSize().y*0.5);
	speed = 0.0f;
	wallSpeed = 0;
	velocity = sf::Vector2f(0.f, 0.0f);
	gravity = sf::Vector2f(0.0f, 0.0f);
	movement = sf::Vector2f(0.0f, 0.0f);
}

void Helicopter::startEverything()
{
	speed = 20.f;
	wallSpeed = 100;
	velocity = sf::Vector2f(0.f, 0.8f);
	gravity = sf::Vector2f(0.f, 0.8f);
	movement = sf::Vector2f(0.5f, 0.0f);
	begin = std::clock();
}

Helicopter::~Helicopter()
{

}
