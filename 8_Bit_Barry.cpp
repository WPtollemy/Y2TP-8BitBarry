// 8_Bit_Barry.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Snake.h"
#include "PongGame.h"	//Pong
#include "PacmanGame.h"
#include "SpaceInvadersClone.h"
#include "Helicopter.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <vector>

#include "MainMenu.h"
#include "ArcadeMenu.h"

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

float scrollSpeed = 75.f;
sf::Time timePerFrame = sf::seconds(1.f / 60.f);

/* Variables */
sf::RenderWindow window(sf::VideoMode(800, 750), "8 Bit Barry");
sf::Font font;
sf::Text text;

bool isRunning = true;

/* Methods */
void setCountdown();
void countdown();
void centreText(sf::Text&);

/* Cutscene Methods */
void splash();

void cutOne();
void cutTwo();
void cutThree();
void cutFour();
void cutFive();
void cutSix();
void cutSeven();
void cutEight();
void cutNine();
void cutTen();
void cutEleven();
void cutTwelve();
void cutThirteen();
void cutFourteen();
void credits(bool = false);

void story();
void arcade();

void fadeIn(std::vector<sf::Sprite>, int = 0);
void fadeOut(std::vector<sf::Sprite>, int = 0);

void fadeSoundIn(sf::Music*);
void fadeSoundOut(sf::Music*);
void fadeSoundInTwo(sf::Music*, sf::Music*);
void fadeSoundOutTwo(sf::Music*, sf::Music*);
void threadSoundIn(sf::Music*);
void threadSoundOut(sf::Music*);
void threadSoundInTwo(sf::Music*, sf::Music*);
void threadSoundOutTwo(sf::Music*, sf::Music*);

SnakeGame snake(&window);
PongGame pong(&window);
PacmanGame pacman(&window);
SpaceInvadersClone spaceInvadersGame(window);
Helicopter helicopter(&window);

sf::Music* mainMenuSong = new sf::Music();
sf::Music* morning = new sf::Music();
sf::Music* creditsSong = new sf::Music();
sf::Music* helicopterSong = new sf::Music();
sf::Music* winSong = new sf::Music();
sf::Music* newWorld = new sf::Music();
sf::Music* war = new sf::Music();

bool notAlready = true;
bool hasSplashed = false;

int main()
{
	std::srand(std::time(0));	//Current time as seed for random generator
	sf::Event event;
	
	setCountdown();

	MainMenu menu(window);
	ArcadeMenu arMenu(window);

	mainMenuSong->openFromFile("res/music/mainMenu.ogg");
	morning->openFromFile("res/music/morning.ogg");
	creditsSong->openFromFile("res/music/credits.ogg");
	helicopterSong->openFromFile("res/music/helicopter.ogg");
	winSong->openFromFile("res/music/win.ogg");
	newWorld->openFromFile("res/music/newWorld.ogg");
	war->openFromFile("res/music/war.ogg");
	
	mainMenuSong->setVolume(100);
	mainMenuSong->setLoop(true);

	morning->setVolume(100);
	morning->setLoop(true);

	creditsSong->setVolume(100);
	creditsSong->setLoop(true);

	helicopterSong->setVolume(100);
	helicopterSong->setLoop(true);

	winSong->setVolume(100);
	winSong->setLoop(true);

	newWorld->setVolume(100);
	newWorld->setLoop(true);

	war->setVolume(100);
	war->setLoop(true);

	while (window.isOpen() && isRunning) {

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				mainMenuSong->stop();
			}
		}

		mainMenuSong->setVolume(100);

		if(!hasSplashed)
			splash();
		hasSplashed = true;
		
		if (notAlready) {
			mainMenuSong->play();
			notAlready = false;
		}

		switch (menu.run())
		{
		case MainMenu::GameStates::Story :
			story(); break;
		case MainMenu::GameStates::Arcade :
			arcade(); break;
		case MainMenu::GameStates::Credits:
			credits(); break;
		}
		
		
		/**/

		//isRunning = false;
	}

    return 0;
}


void setCountdown() {

	font.loadFromFile("res/Pixellari.ttf");
	text.setFont(font);
	text.setCharacterSize(100);
	
}

void centreText(sf::Text& text) {

	sf::Vector2f size(text.getLocalBounds().width + text.getLocalBounds().left, text.getLocalBounds().height + text.getLocalBounds().top);
	text.setOrigin(size.x/2, size.y/2);
	text.setPosition(window.getSize().x/2, window.getSize().y/2);
}

void countdown() {

	for (int i = 3; i > 0; i--) {
		window.clear();
		text.setString(std::to_string(i));
		centreText(text);
		window.draw(text);
		window.display();
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}





/*

		//Cutscenes start here

*/

void splash() {

	sf::Texture textBG;

	sf::Sprite background;

	textBG.loadFromFile("res/other/splash.png");

	background.setTexture(textBG);

	background.setPosition(0, 0);

	window.clear(sf::Color::White);
	window.display();

	std::this_thread::sleep_for(std::chrono::seconds(1));

	std::vector<sf::Sprite> toDraw;
	toDraw.push_back(background);

	fadeIn(toDraw, 255);

	window.clear(sf::Color::White);
	window.draw(background);
	window.display();

	std::this_thread::sleep_for(std::chrono::seconds(4));

	std::vector<sf::Sprite> toDrawTwo;
	toDrawTwo.push_back(background);

	fadeOut(toDraw, 255);
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

void cutOne() {

	sf::Texture textBG;
	sf::Texture textText;

	sf::Sprite background;
	sf::Sprite textImage;

	textBG.loadFromFile("res/cuts/1 Image.png");
	textText.loadFromFile("res/cuts/1 Text.png");

	background.setTexture(textBG);
	textImage.setTexture(textText);

	background.setPosition(0, 0);
	textImage.setPosition(455, 110);

	std::vector<sf::Sprite> toDraw;
	toDraw.push_back(background);

	fadeIn(toDraw);

	float fade = 0;
	textImage.setColor(sf::Color(255, 255, 255, 0));

	//Smooth running stuff
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Event event;

	//window.clear();
	//window.draw(background);
	//window.display();

	//std::this_thread::sleep_for(std::chrono::seconds(3));


	while (fade < 255) {

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		timeSinceLastUpdate += clock.restart();

		window.clear();
		window.draw(background);
		window.draw(textImage);
		window.display();

		while (timeSinceLastUpdate > timePerFrame) {

			timeSinceLastUpdate -= timePerFrame;

			fade += (scrollSpeed * timePerFrame.asSeconds());

			textImage.setColor(sf::Color(255,255,255,fade));
		}

	}

	std::this_thread::sleep_for(std::chrono::seconds(6));

	std::vector<sf::Sprite> toDrawTwo;
	toDrawTwo.push_back(background);
	toDrawTwo.push_back(textImage);
	
	fadeOut(toDrawTwo);
}

void cutTwo() {

	sf::Texture textBG;
	sf::Texture textText;

	sf::Sprite background;
	sf::Sprite textImage;

	textBG.loadFromFile("res/cuts/2 Image.png");
	textText.loadFromFile("res/cuts/2 Text.png");

	background.setTexture(textBG);
	textImage.setTexture(textText);

	background.setPosition(0, 0);
	textImage.setOrigin(textText.getSize().x / 2, textText.getSize().y / 2);
	textImage.setPosition(window.getSize().x / 2, 600);
	textImage.setColor(sf::Color(255, 255, 255, 0));

	std::vector<sf::Sprite> toDraw;
	toDraw.push_back(background);
	float fade = 0;
	fadeIn(toDraw);

	//Smooth running stuff
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Event event;

	while (fade < 255) {

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		timeSinceLastUpdate += clock.restart();

		window.clear();
		window.draw(background);
		window.draw(textImage);
		window.display();

		while (timeSinceLastUpdate > timePerFrame) {

			timeSinceLastUpdate -= timePerFrame;

			fade += (scrollSpeed * timePerFrame.asSeconds());

			textImage.setColor(sf::Color(255, 255, 255, fade));
		}

	}

	std::this_thread::sleep_for(std::chrono::seconds(6));

	std::vector<sf::Sprite> toDrawTwo;
	toDrawTwo.push_back(background);
	toDrawTwo.push_back(background);

	fadeOut(toDrawTwo);
}

void cutThree() {

	sf::Texture textBG;
	sf::Texture textText;

	sf::Sprite background;
	sf::Sprite textImage;

	textBG.loadFromFile("res/cuts/3 Image.png");
	textText.loadFromFile("res/cuts/3 Text.png");

	background.setTexture(textBG);
	textImage.setTexture(textText);

	background.setPosition(0, 0);
	textImage.setOrigin(textText.getSize().x / 2, textText.getSize().y / 2);
	textImage.setPosition(window.getSize().x / 2, 150);
	textImage.setColor(sf::Color(255, 255, 255, 0));

	std::vector<sf::Sprite> toDraw;
	toDraw.push_back(background);
	float fade = 0;
	fadeIn(toDraw);

	//Smooth running stuff
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Event event;

	while (fade < 255) {

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		timeSinceLastUpdate += clock.restart();

		window.clear();
		window.draw(background);
		window.draw(textImage);
		window.display();

		while (timeSinceLastUpdate > timePerFrame) {

			timeSinceLastUpdate -= timePerFrame;

			fade += (scrollSpeed * timePerFrame.asSeconds());

			textImage.setColor(sf::Color(255, 255, 255, fade));
		}

	}

	std::this_thread::sleep_for(std::chrono::seconds(6));

	std::vector<sf::Sprite> toDrawTwo;
	toDrawTwo.push_back(background);
	toDrawTwo.push_back(background);

	fadeOut(toDrawTwo);
}

void cutFour() {

	sf::Texture textText;
	sf::Texture textBG;

	sf::Sprite text;
	sf::Sprite background;

	textText.loadFromFile("res/cuts/4 Text.png");
	textBG.loadFromFile("res/cuts/4 Image.png");

	text.setTexture(textText);
	background.setTexture(textBG);

	background.setPosition(0,0);
	text.setOrigin(textText.getSize().x/2, 0);
	text.setPosition(window.getSize().x / 2, 0);
	
	std::vector<sf::Sprite> toDraw;
	toDraw.push_back(background);
	toDraw.push_back(text);
	

	fadeIn(toDraw);

	//Smooth running stuff
	sf::Clock clock;	
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Event event;

	while (text.getPosition().y + textText.getSize().y > window.getSize().y) {

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		timeSinceLastUpdate += clock.restart();

		window.clear();
		window.draw(background);
		window.draw(text);
		window.display();

		while (timeSinceLastUpdate > timePerFrame) {

			timeSinceLastUpdate -= timePerFrame;
			sf::Vector2f movement(0,0);
			movement.y -= scrollSpeed;

			text.move(movement * timePerFrame.asSeconds());
			//calculateCloseDirection(timePerFrame);
		}


	}

	std::vector<sf::Sprite> toDrawTwo;
	toDrawTwo.push_back(background);
	toDrawTwo.push_back(text);
	

	fadeOut(toDraw);

}

void cutFive() {

	sf::Texture textText;
	sf::Texture textBG;

	sf::Sprite text;
	sf::Sprite background;

	textText.loadFromFile("res/cuts/5 Text.png");
	textBG.loadFromFile("res/cuts/5 Image.png");

	text.setTexture(textText);
	background.setTexture(textBG);

	background.setPosition(0, 0);
	text.setOrigin(textText.getSize().x / 2, 0);
	text.setPosition(window.getSize().x / 2, 0);

	std::vector<sf::Sprite> toDraw;
	toDraw.push_back(background);
	toDraw.push_back(text);
	

	fadeIn(toDraw);

	//Smooth running stuff
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	sf::Event event;

	while (text.getPosition().y + textText.getSize().y > window.getSize().y) {

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		timeSinceLastUpdate += clock.restart();

		window.clear();
		window.draw(background);
		window.draw(text);
		window.display();

		while (timeSinceLastUpdate > timePerFrame) {

			timeSinceLastUpdate -= timePerFrame;
			sf::Vector2f movement(0, 0);
			movement.y -= scrollSpeed;

			text.move(movement * timePerFrame.asSeconds());
			//calculateCloseDirection(timePerFrame);
		}


	}

	std::vector<sf::Sprite> toDrawTwo;
	toDrawTwo.push_back(background);
	toDrawTwo.push_back(text);

	fadeOut(toDraw);

}

void cutSix() {

	sf::Texture textText;
	sf::Texture textBG;

	sf::Sprite text;
	sf::Sprite background;

	textText.loadFromFile("res/cuts/6 Text.png");
	textBG.loadFromFile("res/cuts/6 Image.png");

	text.setTexture(textText);
	background.setTexture(textBG);

	background.setPosition(0, 0);
	text.setOrigin(textText.getSize().x / 2, 0);
	text.setPosition(window.getSize().x / 2, 0);

	std::vector<sf::Sprite> toDraw;
	toDraw.push_back(background);
	toDraw.push_back(text);

	fadeIn(toDraw);

	//Smooth running stuff
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	sf::Event event;

	while (text.getPosition().y + textText.getSize().y > window.getSize().y) {

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		timeSinceLastUpdate += clock.restart();

		window.clear();
		window.draw(background);
		window.draw(text);
		window.display();

		while (timeSinceLastUpdate > timePerFrame) {

			timeSinceLastUpdate -= timePerFrame;
			sf::Vector2f movement(0, 0);
			movement.y -= scrollSpeed;

			text.move(movement * timePerFrame.asSeconds());
			//calculateCloseDirection(timePerFrame);
		}


	}

	std::vector<sf::Sprite> toDrawTwo;
	toDrawTwo.push_back(background);
	toDrawTwo.push_back(text);

	fadeOut(toDraw);

}

void cutSeven() {

	sf::Texture textBG;

	sf::Sprite background;

	textBG.loadFromFile("res/cuts/7 Image.png");

	background.setTexture(textBG);

	background.setPosition(0, 0);

	std::vector<sf::Sprite> toDraw;
	toDraw.push_back(background);

	fadeIn(toDraw);

	window.clear();
	window.draw(background);
	window.display();

	std::this_thread::sleep_for(std::chrono::seconds(4));

	std::vector<sf::Sprite> toDrawTwo;
	toDrawTwo.push_back(background);

	fadeOut(toDraw);
}

void cutEight() {

	sf::Texture textText;
	sf::Texture textBG;

	sf::Sprite text;
	sf::Sprite background;

	textText.loadFromFile("res/cuts/8 Text.png");
	textBG.loadFromFile("res/cuts/8 Image.png");

	text.setTexture(textText);
	background.setTexture(textBG);

	background.setPosition(0, 0);
	text.setOrigin(textText.getSize().x / 2, 0);
	text.setPosition(window.getSize().x / 2, 0);

	std::vector<sf::Sprite> toDraw;
	toDraw.push_back(background);
	toDraw.push_back(text);

	fadeIn(toDraw);

	//Smooth running stuff
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	sf::Event event;

	while (text.getPosition().y + textText.getSize().y > window.getSize().y) {

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		timeSinceLastUpdate += clock.restart();

		window.clear();
		window.draw(background);
		window.draw(text);
		window.display();

		while (timeSinceLastUpdate > timePerFrame) {

			timeSinceLastUpdate -= timePerFrame;
			sf::Vector2f movement(0, 0);
			movement.y -= scrollSpeed;

			text.move(movement * timePerFrame.asSeconds());
			//calculateCloseDirection(timePerFrame);
		}


	}

	std::vector<sf::Sprite> toDrawTwo;
	toDrawTwo.push_back(background);
	toDrawTwo.push_back(text);


	fadeOut(toDraw);

}

void cutNine() {

	sf::Texture textText;
	sf::Texture textBG;

	sf::Sprite text;
	sf::Sprite background;

	textText.loadFromFile("res/cuts/9 Text.png");
	textBG.loadFromFile("res/cuts/9 Image.png");

	text.setTexture(textText);
	background.setTexture(textBG);

	background.setPosition(0, 0);
	text.setOrigin(textText.getSize().x / 2, 0);
	text.setPosition(window.getSize().x / 2, 0);

	std::vector<sf::Sprite> toDraw;
	toDraw.push_back(background);
	toDraw.push_back(text);
	

	fadeIn(toDraw);

	//Smooth running stuff
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	sf::Event event;

	while (text.getPosition().y + textText.getSize().y > window.getSize().y) {

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		timeSinceLastUpdate += clock.restart();

		window.clear();
		window.draw(background);
		window.draw(text);
		window.display();

		while (timeSinceLastUpdate > timePerFrame) {

			timeSinceLastUpdate -= timePerFrame;
			sf::Vector2f movement(0, 0);
			movement.y -= scrollSpeed;

			text.move(movement * timePerFrame.asSeconds());
			//calculateCloseDirection(timePerFrame);
		}
	}

	std::vector<sf::Sprite> toDrawTwo;
	toDrawTwo.push_back(background);
	toDrawTwo.push_back(text);


	fadeOut(toDraw);

}

void cutTen() {

	sf::Texture textText;
	sf::Texture textBG;

	sf::Sprite text;
	sf::Sprite background;

	textText.loadFromFile("res/cuts/10 Text.png");
	textBG.loadFromFile("res/cuts/10 Image.png");

	text.setTexture(textText);
	background.setTexture(textBG);

	background.setPosition(0, 0);
	text.setOrigin(textText.getSize().x / 2, 0);
	text.setPosition(window.getSize().x / 2, 0);

	std::vector<sf::Sprite> toDraw;
	toDraw.push_back(background);
	toDraw.push_back(text);


	fadeIn(toDraw);

	//Smooth running stuff
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	sf::Event event;

	while (text.getPosition().y + textText.getSize().y > window.getSize().y) {

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		timeSinceLastUpdate += clock.restart();

		window.clear();
		window.draw(background);
		window.draw(text);
		window.display();

		while (timeSinceLastUpdate > timePerFrame) {

			timeSinceLastUpdate -= timePerFrame;
			sf::Vector2f movement(0, 0);
			movement.y -= scrollSpeed;

			text.move(movement * timePerFrame.asSeconds());
			//calculateCloseDirection(timePerFrame);
		}
	}

	std::vector<sf::Sprite> toDrawTwo;
	toDrawTwo.push_back(background);
	toDrawTwo.push_back(text);


	fadeOut(toDraw);

}

void cutEleven() {

	sf::Texture textText;
	sf::Texture textBG;

	sf::Sprite text;
	sf::Sprite background;

	textText.loadFromFile("res/cuts/11 Text.png");
	textBG.loadFromFile("res/cuts/11 Image.png");

	text.setTexture(textText);
	background.setTexture(textBG);

	background.setPosition(0, 0);
	text.setOrigin(textText.getSize().x / 2, 0);
	text.setPosition(window.getSize().x / 2, 0);

	std::vector<sf::Sprite> toDraw;
	toDraw.push_back(background);
	toDraw.push_back(text);


	fadeIn(toDraw);

	//Smooth running stuff
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	sf::Event event;

	while (text.getPosition().y + textText.getSize().y > window.getSize().y) {

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		timeSinceLastUpdate += clock.restart();

		window.clear();
		window.draw(background);
		window.draw(text);
		window.display();

		while (timeSinceLastUpdate > timePerFrame) {

			timeSinceLastUpdate -= timePerFrame;
			sf::Vector2f movement(0, 0);
			movement.y -= scrollSpeed;

			text.move(movement * timePerFrame.asSeconds());
			//calculateCloseDirection(timePerFrame);
		}
	}

	std::vector<sf::Sprite> toDrawTwo;
	toDrawTwo.push_back(background);
	toDrawTwo.push_back(text);


	fadeOut(toDraw);

}

void cutTwelve() {

	sf::Texture textBG;

	sf::Sprite background;

	textBG.loadFromFile("res/cuts/12 Image.png");

	background.setTexture(textBG);

	background.setPosition(0, 0);

	std::vector<sf::Sprite> toDraw;
	toDraw.push_back(background);

	fadeIn(toDraw);

	window.clear();
	window.draw(background);
	window.display();

	std::this_thread::sleep_for(std::chrono::seconds(4));

	std::vector<sf::Sprite> toDrawTwo;
	toDrawTwo.push_back(background);

	fadeOut(toDraw);
}

void cutThirteen() {

	sf::Texture textBG;

	sf::Sprite background;

	textBG.loadFromFile("res/cuts/13 Image.png");

	background.setTexture(textBG);

	background.setPosition(0, 0);

	std::vector<sf::Sprite> toDraw;
	toDraw.push_back(background);

	fadeIn(toDraw);

	window.clear();
	window.draw(background);
	window.display();

	std::this_thread::sleep_for(std::chrono::seconds(4));

	std::vector<sf::Sprite> toDrawTwo;
	toDrawTwo.push_back(background);

	fadeOut(toDraw);
}

void cutFourteen() {

	sf::Texture textBG;
	sf::Texture textText;

	sf::Sprite background;
	sf::Sprite textImage;

	textBG.loadFromFile("res/cuts/14 Image.png");
	textText.loadFromFile("res/cuts/14 Text.png");

	background.setTexture(textBG);
	textImage.setTexture(textText);

	background.setPosition(0, 0);
	textImage.setOrigin(textText.getSize().x / 2, textText.getSize().y / 2);
	textImage.setPosition(window.getSize().x / 2, 150);
	textImage.setColor(sf::Color(255, 255, 255, 0));

	std::vector<sf::Sprite> toDraw;
	toDraw.push_back(background);
	float fade = 0;
	fadeIn(toDraw);

	//Smooth running stuff
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Event event;

	while (fade < 255) {

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		timeSinceLastUpdate += clock.restart();

		window.clear();
		window.draw(background);
		window.draw(textImage);
		window.display();

		while (timeSinceLastUpdate > timePerFrame) {

			timeSinceLastUpdate -= timePerFrame;

			fade += (scrollSpeed * timePerFrame.asSeconds());

			textImage.setColor(sf::Color(255, 255, 255, fade));
		}

	}

	std::this_thread::sleep_for(std::chrono::seconds(6));

	std::vector<sf::Sprite> toDrawTwo;
	toDrawTwo.push_back(background);
	toDrawTwo.push_back(background);

	fadeOut(toDrawTwo);
}


void fadeOut(std::vector<sf::Sprite> toDraw, int colour) {

	//Smooth running stuff
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	window.clear();
	for (int i = 0; i < toDraw.size(); i++) {
		window.draw(toDraw.at(i));
	}
	window.display();

	float fade = 0;
	sf::Color colourScreen = sf::Color(0, 0, 0, 0);
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));

	sf::Event event;

	while (fade < 255) {

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		timeSinceLastUpdate += clock.restart();

		window.clear(sf::Color::Blue); // Won't need to clear

		for (int i = 0; i < toDraw.size(); i++) {
			window.draw(toDraw.at(i));
		}

		window.draw(rect);
		window.display();

		while (timeSinceLastUpdate > timePerFrame) {

			timeSinceLastUpdate -= timePerFrame;
			//sf::Vector2f movement(0, 0);
			fade += (scrollSpeed * timePerFrame.asSeconds());

			rect.setFillColor(sf::Color(colour, colour, colour, fade));
		}


	}

}

void fadeIn(std::vector<sf::Sprite> toDraw, int colour) {

	//Smooth running stuff
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	float fade = 255;
	sf::Color colourScreen = sf::Color(0, 0, 0, 255);
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));

	sf::Event event;

	while (fade > 0) {

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		timeSinceLastUpdate += clock.restart();

		window.clear(); // Won't need to clear

		for(int i = 0; i < toDraw.size(); i++){
			window.draw(toDraw.at(i));
		}

		window.draw(rect);
		window.display();

		while (timeSinceLastUpdate > timePerFrame) {

			timeSinceLastUpdate -= timePerFrame;
			//sf::Vector2f movement(0, 0);
			fade -= (scrollSpeed * timePerFrame.asSeconds());

			rect.setFillColor(sf::Color(colour, colour, colour, fade));
		}


	}
}

void story() {

	notAlready = true;
	//mainMenuSong->stop();
	threadSoundOutTwo(mainMenuSong, morning);

	cutOne();
	cutTwo();
	countdown();
	pong.run();
	threadSoundOutTwo(morning, newWorld);
	cutThree();
	cutFour();
	countdown();
	pacman.run();
	cutFive();
	cutSix();
	countdown();
	snake.run(7, true);	//Set run for story
	cutSeven();
	cutEight();
	threadSoundOutTwo(newWorld, war);
	cutNine();
	countdown();
	spaceInvadersGame.run();
	cutTen();
	threadSoundOutTwo(war, helicopterSong);
	helicopter.run();
	threadSoundOutTwo(helicopterSong, winSong);
	cutEleven();
	cutTwelve();
	cutThirteen();
	cutFourteen();
	credits(true);
}

void credits(bool fromStory) {

	if (fromStory)
		threadSoundOutTwo(winSong, creditsSong);
	else
		threadSoundOutTwo(mainMenuSong, creditsSong);
	

	sf::Texture frontText;
	sf::Texture backText;
	sf::Texture backbackText;

	sf::Sprite front;
	sf::Sprite back;
	sf::Sprite backback;

	frontText.loadFromFile("res/cuts/credits/front.png");
	backText.loadFromFile("res/cuts/credits/back.png");
	backbackText.loadFromFile("res/cuts/credits/backback.png");

	front.setTexture(frontText);
	back.setTexture(backText);
	backback.setTexture(backbackText);

	front.setOrigin(frontText.getSize().x / 2, 0);
	front.setPosition(window.getSize().x / 2, 0);

	std::vector<sf::Sprite> toDraw;
	toDraw.push_back(backback);
	toDraw.push_back(back);
	toDraw.push_back(front);

	
	fadeIn(toDraw);

	//Smooth running stuff
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	sf::Event event;

	while (front.getPosition().y + frontText.getSize().y > window.getSize().y) {

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		timeSinceLastUpdate += clock.restart();

		window.clear();
		window.draw(backback);
		window.draw(back);
		window.draw(front);
		window.display();

		while (timeSinceLastUpdate > timePerFrame) {

			timeSinceLastUpdate -= timePerFrame;
			sf::Vector2f movement(0, 0);
			sf::Vector2f movementBack(0, 0);
			movement.y -= scrollSpeed;
			movementBack.y -= scrollSpeed * 0.15;

			front.move(movement * timePerFrame.asSeconds());
			backback.move(movementBack * timePerFrame.asSeconds());
		}
	}

	std::vector<sf::Sprite> toDrawTwo;
	toDrawTwo.push_back(backback);
	toDrawTwo.push_back(back);
	toDrawTwo.push_back(front);

	fadeOut(toDrawTwo);
	fadeSoundOutTwo(creditsSong, mainMenuSong);
}

void arcade() {
	bool isRunning = true;
	
	while (isRunning) {
		ArcadeMenu arMenu(window);

		switch (arMenu.run())
		{
		case ArcadeMenu::Pong:
			pong.run(); break;
		case ArcadeMenu::Pacman:
			pacman.run(); break;
		case ArcadeMenu::Snake:
			snake.run(20); break;
		case ArcadeMenu::Space:
			spaceInvadersGame.run(); break;
		case ArcadeMenu::Helicopter:
			helicopter.run(); break;
		case ArcadeMenu::Main:
			isRunning = false; break;
		default:
			break;
		}
	}
}

void fadeSoundIn(sf::Music* music) {

	//Smooth running stuff
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	float fade = 0;
	music->play();
	music->setVolume(0);

	while (fade < 100) {

		timeSinceLastUpdate += clock.restart();

		while (timeSinceLastUpdate > timePerFrame) {

			timeSinceLastUpdate -= timePerFrame;

			fade += (scrollSpeed * timePerFrame.asSeconds());
			if (fade > 100)
				music->setVolume(100);
			else
				music->setVolume(fade);
		}
	}
}

void fadeSoundOut(sf::Music* music) {

	//Smooth running stuff
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	float fade = 100;

	while (fade > 0) {

		timeSinceLastUpdate += clock.restart();

		while (timeSinceLastUpdate > timePerFrame) {

			timeSinceLastUpdate -= timePerFrame;

			fade -= (scrollSpeed * timePerFrame.asSeconds());
			if (fade < 0)
				music->setVolume(0);
			else
				music->setVolume(fade);
		}
	}

	music->stop();
}

void fadeSoundInTwo(sf::Music* music, sf::Music* musicTwo) {

	//Smooth running stuff
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	fadeSoundOut(music);

	float fade = 0;
	musicTwo->play();
	musicTwo->setVolume(0);

	while (fade < 100) {

		timeSinceLastUpdate += clock.restart();

		while (timeSinceLastUpdate > timePerFrame) {

			timeSinceLastUpdate -= timePerFrame;

			fade += (scrollSpeed * timePerFrame.asSeconds());
			if (fade > 100)
				musicTwo->setVolume(100);
			else
				musicTwo->setVolume(fade);
		}
	}
	
}

void fadeSoundOutTwo(sf::Music* music, sf::Music* musicTwo) {

	//Smooth running stuff
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	float fade = 100;

	while (fade > 0) {

		timeSinceLastUpdate += clock.restart();

		while (timeSinceLastUpdate > timePerFrame) {

			timeSinceLastUpdate -= timePerFrame;

			fade -= (scrollSpeed * timePerFrame.asSeconds());
			if (fade < 0)
				music->setVolume(0);
			else
				music->setVolume(fade);
		}
	}

	fadeSoundIn(musicTwo);
}

void threadSoundIn(sf::Music* music) {

	std::thread fade(fadeSoundIn, music);
	fade.detach();

}

void threadSoundOut(sf::Music* music) {

	std::thread fade(fadeSoundOut, music);
	fade.detach();

}

void threadSoundInTwo(sf::Music* music, sf::Music* musicTwo) {

	std::thread fade(fadeSoundInTwo, music, musicTwo);
	fade.detach();

}

void threadSoundOutTwo(sf::Music* music, sf::Music* musicTwo) {

	std::thread fade(fadeSoundOutTwo, music, musicTwo);
	fade.detach();

}
