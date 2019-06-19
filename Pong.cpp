#include "stdafx.h"
#include "Pong.h"

#include <cmath>
#include <iostream>

const float playerSpeed = 200.f;
const sf::Time timePerFrame = sf::seconds(1.f / 60.f);
//onst sf::Time Game::timePerFrame = sf::seconds(1.f / 60.f);

Pong::Pong(sf::RenderWindow* window, int noRounds)
	: window(window)
	, windowSize(window->getSize())
	, noRounds(noRounds)
{
	//Set bounds
	sf::Vector2f boundsVect(windowSize.x - 30, windowSize.y - 30);
	bounds.setSize(boundsVect);
	bounds.setPosition(15, 15);
	bounds.setOutlineThickness(3);
	bounds.setOutlineColor(sf::Color::White);
	bounds.setFillColor(sf::Color::Black);

	//Set ball
	sf::Vector2f ballSize(20.f, 20.f);
	ball.setSize(ballSize);
	ball.setOrigin(10, 10);
	ball.setPosition(windowSize.x / 2, windowSize.y / 2);

	//Set rectangles
	sf::Vector2f rectSize(20.0f, 140.0f);
	playerComp.setSize(rectSize);
	playerPerson.setSize(rectSize);

	playerComp.setFillColor(sf::Color::White);
	playerPerson.setFillColor(sf::Color::White);

	//Comp top left, player bottom right
	playerComp.setPosition(20,20);
	playerPerson.setPosition(windowSize.x - 40, windowSize.y - 160);

	//Generate centreLine
	generateCentreLine();

	//Ball direction
	float angle = std::rand() % 4 + 20;
	angle *= 90;
	
	sf::Vector2f temp(cos(angle), sin(angle));
	ballDirection = temp;

	//std::cout << ballDirection.x << std::endl;
}

Pong::~Pong()
{

}

bool Pong::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	quit = false;

	while (true)
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			update(timePerFrame);
		}
		render();

		if (quit)
			return true;

		//Check scores
		for (int i = 0; i < sizeof(scores) / sizeof(int); i++)
		{
			if (scores[i] == noRounds)
			{
				if (i == 0)
					return false;
				else
					return true;
			}
		}
	}
	
}

void Pong::render()
{
	window->clear();
	window->draw(bounds);
	window->draw(playerComp);
	window->draw(playerPerson);

	for (int i = 0; i < centreLine.size(); i++)
		window->draw(centreLine.at(i));

	window->draw(ball);
	
	window->display();
}

void Pong::processEvents()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed :
			//if (!playerPerson.getPosition().y - 5 <= bounds.getPosition().y && !playerPerson.getPosition().y + 145 >= bounds.getPosition().y + bounds.getSize().y)
			if (event.key.code == sf::Keyboard::M)
				quit = true;
			else
				handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased :
			handlePlayerInput(event.key.code, false);
			break;
		case sf::Event::Closed :
			window->close();
		}
	}
}

void Pong::update(sf::Time deltaTime)
{
	//Move player
	sf::Vector2f movement(0.f, 0.f);
	if (isMovingUp)
		movement.y -= playerSpeed;
	else if (isMovingDown)
		movement.y += playerSpeed;

	//Move computer
	sf::Vector2f movementComp(0.f, 0.f);
	if (compUp)
		movementComp.y -= playerSpeed;
	else
		movementComp.y += playerSpeed;

	updateBall(deltaTime);

	playerPerson.move(movement * deltaTime.asSeconds());
	playerComp.move(movementComp * deltaTime.asSeconds());

	if (ball.getPosition().x <= windowSize.x * 0.25) {
		if (ball.getPosition().y < playerComp.getPosition().y)
			compUp = true;
		else if (ball.getPosition().y > playerComp.getPosition().y + 140)
			compUp = false;
	}

	//Check whether comp to change direction
	if (playerComp.getPosition().y <= bounds.getPosition().y)
		compUp = false;
	else if ((playerComp.getPosition().y + 140) >= (bounds.getSize().y + bounds.getPosition().y))
		compUp = true;

	if (playerPerson.getPosition().y - 5 <= bounds.getPosition().y)
		isMovingUp = false;
	if (playerPerson.getPosition().y + 145 >= bounds.getPosition().y + bounds.getSize().y)
		isMovingDown = false;
}

void Pong::generateCentreLine()
{
	sf::Vector2f rectSize(4.0f, 40.0f);
	sf::Vector2f rectLocation(((windowSize.x / 2) - 2), 25);
	
	sf::RectangleShape first(rectSize);
	first.setPosition(rectLocation);
	first.setFillColor(sf::Color(75, 75, 75, 255));	//Grey

	centreLine.push_back(first);

	int i = 0;

	while ((centreLine.at(i).getPosition().y + 60) < windowSize.y - 25)	//While line hasn't reached bottom
	{
		first.setPosition((windowSize.x / 2 - 3), (first.getPosition().y + 60));
		centreLine.push_back(first);
		i++;
	}

}

void Pong::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	switch (key)
	{
	case sf::Keyboard::W :
	case sf::Keyboard::Up :		//if 'W' or 'Up' isPressed
	{
		if (playerPerson.getPosition().y - 5 <= bounds.getPosition().y)
			isPressed = false;

		isMovingUp = isPressed;
		break;
	}
	case sf::Keyboard::S :
	case sf::Keyboard::Down :
	{
		if (playerPerson.getPosition().y + 145 >= bounds.getPosition().y + bounds.getSize().y)
			isPressed = false;

		isMovingDown = isPressed;
		break;
	}
	}
}

void Pong::updateBall(sf::Time deltaTime)
{
	sf::Vector2f movement(0.f, 0.f);
	
	//Collision detection
	if (ball.getPosition().x - 10 <= playerComp.getPosition().x + 20)	//If collides with computer paddle
	{
		if ((ball.getPosition().y >= playerComp.getPosition().y) && (ball.getPosition().y <= playerComp.getPosition().y + 140))
		{
			//std::cout << "Bouncing left" << std::endl;
			bounce(Left);
		}
		else
		{
			//stillGoing = false;
			//didWin = true;
			scores[1]++;
			resetBall();
			//std::cout << "Score added: " << scores[1] << std::endl;
		}
	}
	else if (ball.getPosition().x + 10 >= playerPerson.getPosition().x)	//If collides with player paddle
	{
		if ((ball.getPosition().y >= playerPerson.getPosition().y) && (ball.getPosition().y <= playerPerson.getPosition().y + 140))
		{
			//std::cout << "Bouncing right" << std::endl;
			bounce(Right);
		}
		else
		{
			//stillGoing = false;
			//didWin = false;
			scores[0]++;
			resetBall();
			//std::cout << "Comp Score added: " << scores[0] << std::endl;
		}
	}

	if (ball.getPosition().y - 10 <= bounds.getPosition().y)
	{
		bounce(Upper);
		//std::cout << "Bouncing upper" << std::endl;
	}
	else if (ball.getPosition().y + 10 >= bounds.getSize().y + bounds.getPosition().y)
	{
		bounce(Lower);
		//std::cout << "Bouncing lower" << std::endl;
	}
	
	movement.x += ballDirection.x * playerSpeed;
	movement.y += ballDirection.y * playerSpeed;

	ball.move(movement * deltaTime.asSeconds());
}

void Pong::bounce(Walls bounceOff)
{
	sf::Vector2f normal;

	switch (bounceOff)
	{
	case Upper:
	case Lower:
		ballDirection.y *= -1;
		break;
		
	case Left:
	case Right:
		ballDirection.x *= -1;
		break;
	}
}

void Pong::resetBall()
{
	ball.setPosition(windowSize.x / 2, windowSize.y / 2);

	//Ball direction
	float angle = std::rand() % 4 + 20;
	angle *= 90;

	sf::Vector2f temp(cos(angle), sin(angle));
	ballDirection = temp;
}
