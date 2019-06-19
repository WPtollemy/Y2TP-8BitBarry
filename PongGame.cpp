#include "stdafx.h"

#include "PongGame.h"
#include "Pong.h"
#include <iostream>
#include <thread>
#include <chrono>

PongGame::PongGame(sf::RenderWindow* window)
	: window(window)
{
	//Set text
	font.loadFromFile("res/Pong/eight_bit.ttf");
	text.setFont(font);
	text.setString("You Win");
	text.setColor(sf::Color::Green);
	text.setCharacterSize(50);
	text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
	text.setPosition(window->getSize().x / 2, window->getSize().y / 2);
}

PongGame::~PongGame()
{

}

void PongGame::run()
{
	/*
	while (window->isOpen())
	{
		pong = new Pong(getWindow());
		pong->run();

		//Crashes because i don't have event handler for close

	}*/

	int bestOf, firstTo;

	//std::cout << "Best of: ";
	//std::cin >> bestOf;

	//firstTo = (bestOf / 2) + 1;
	firstTo = 3;
	//std::cout << "Input read as: " << firstTo << std::endl;
		
	pong = new Pong(getWindow(), firstTo);
		
	if (!pong->run())	//Run Pong
	{
		text.setString("You Lose");
		text.setColor(sf::Color::Red);
		text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
		text.setPosition(window->getSize().x / 2, window->getSize().y / 2);
	}
	
	processEvents();
	window->clear();
	window->draw(text);
	window->display();
	
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}


sf::RenderWindow* PongGame::getWindow()
{
	return window;
}

void PongGame::processEvents()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		switch(event.type)
		{
		case sf::Event::Closed:
			window->close();
		}
	}
}
