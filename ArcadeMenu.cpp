#include "stdafx.h"
#include "ArcadeMenu.h"

/*
	Constructor -- Destructor
*/

ArcadeMenu::ArcadeMenu(sf::RenderWindow& window)
: window(window){

	initialise();
}

ArcadeMenu::~ArcadeMenu() {

}


/*
	Other methods
*/

void ArcadeMenu::initialise() {

	font.loadFromFile("res/Pixellari.ttf");
	initialiseButtons();
	initialiseTitle();
	initialiseText();
}

void ArcadeMenu::initialiseTitle() {
	/* Set up title */
	title.setFont(font);
	title.setString("Arcade");
	title.setCharacterSize(100);
	sf::FloatRect bounds = title.getLocalBounds();
	title.setOrigin((bounds.left + bounds.width) / 2, (bounds.top + bounds.height) / 2);
	title.setPosition(window.getSize().x / 2, 125);
	title.setColor(ORANGE);

	//Background
	textBackground.loadFromFile("res/menus/arcadeMenu.png");
	background.setTexture(textBackground);

}

void ArcadeMenu::initialiseText() {

	float charSize = 30;

	sf::Text pong;
	sf::Text pacman;
	sf::Text snake;
	sf::Text space;
	sf::Text helicopter;
	sf::Text home;

	pong.setString("Pong");
	pacman.setString("PacMan");
	snake.setString("Snake");
	space.setString("Space Invaders");
	helicopter.setString("Helicopter");
	home.setString("Home");

	buttons[0].buttonText = pong;
	buttons[1].buttonText = pacman;
	buttons[2].buttonText = snake;
	buttons[3].buttonText = space;
	buttons[4].buttonText = helicopter;
	buttons[5].buttonText = home;

	sf::FloatRect bounds;

	for (int i = 0; i < 6; i++) {

		buttons[i].buttonText.setFont(font);
		buttons[i].buttonText.setColor(ORANGE);
		bounds = buttons[i].buttonText.getLocalBounds();
		buttons[i].buttonText.setOrigin((bounds.left + bounds.width) / 2, (bounds.top + bounds.height) / 2);
		buttons[i].buttonText.setPosition(buttons[i].buttonShape.getPosition());
	}


}

void ArcadeMenu::initialiseButtons() {

	sf::Vector2f buttonSize(250, 50);
	sf::Vector2f buttonOrigin(125, 25);
	sf::Vector2f buttonPos(window.getSize().x / 2, 0);
	sf::Color buttonColour(BROWN);

	Button pong;
	Button pacman;
	Button snake;
	Button space;
	Button helicopter;
	Button home;

	buttons.push_back(pong);
	buttons.push_back(pacman);
	buttons.push_back(snake);
	buttons.push_back(space);
	buttons.push_back(helicopter);
	buttons.push_back(home);

	for (int i = 0; i < 6; i++) {
		buttons[i].buttonShape.setSize(buttonSize);
		buttons[i].buttonShape.setOrigin(buttonOrigin);
		buttons[i].buttonShape.setPosition(buttonPos.x, (buttonPos.y + (i * 85) + 275));
		buttons[i].buttonShape.setFillColor(buttonColour);
		buttons[i].buttonShape.setOutlineColor(sf::Color::White);
	}

	buttons[5].buttonShape.setSize(sf::Vector2f(150, 50));
	buttons[5].buttonShape.setOrigin(75,25);
	buttons[5].buttonShape.setPosition(100, 700);	//Bottom left

}

ArcadeMenu::Games ArcadeMenu::run() {

	sf::Event event;

	while (true) {

		while (window.pollEvent(event)) {

			switch (event.type)
			{
			case sf::Event::Closed: {
				window.close();
				break;
			}
			case sf::Event::MouseMoved: {
				int buttonNum = handleMouseOver();
				if (buttonNum != 99)
					buttons[buttonNum].isOver = true;
				else {
					for (int i = 0; i < 6; i++)
						buttons[i].isOver = false;
				}
				break;
			}
			case sf::Event::MouseButtonReleased: {
				if (buttons[0].isOver)
					return Pong;
				if (buttons[1].isOver)
					return Pacman;
				if (buttons[2].isOver)
					return Snake;
				if (buttons[3].isOver)
					return Space;
				if (buttons[4].isOver)
					return Helicopter;
				if (buttons[5].isOver)
					return Main;

			}
			}

		}
		update();
		render();
	}

}

void ArcadeMenu::render() {

	window.clear();

	window.draw(background);

	for (Button b : buttons)
		window.draw(b.buttonShape);

	for (Button b : buttons)
		window.draw(b.buttonText);

	window.draw(title);

	window.display();
}


int ArcadeMenu::handleMouseOver() {

	sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
	
	for (int i = 0; i < 6; i++) {
		if (buttons[i].buttonShape.getGlobalBounds().contains(mousePos))
			return i;
	}

	return 99;

}

void ArcadeMenu::update() {

	for (int i = 0; i < 6; i++) {

		if (buttons[i].isOver)
			buttons[i].buttonShape.setOutlineThickness(3);
		else
			buttons[i].buttonShape.setOutlineThickness(0);
	}
}

