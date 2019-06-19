#include "stdafx.h"
#include "MainMenu.h"

/*
	Constructor -- Destructor
*/

MainMenu::MainMenu(sf::RenderWindow& window)
	: window(window) {

	initialise();
}

MainMenu::~MainMenu() {

}


/*
	Other methods
*/

void MainMenu::initialise() {

	font.loadFromFile("res/Pixellari.ttf");
	initialiseButtons();
	initialiseTitle();
	initialiseText();

	//Background
	textBackground.loadFromFile("res/menus/mainMenu.png");
	background.setTexture(textBackground);
}

void MainMenu::initialiseButtons() {

	sf::Vector2f buttonSize(250, 50);
	sf::Vector2f buttonOrigin(125, 25);
	sf::Vector2f buttonPos(window.getSize().x / 2, 0);
	sf::Color buttonColour(BROWN);

	Button story;
	Button arcade;
	Button settings;
	Button credits;

	buttons.push_back(story);
	buttons.push_back(arcade);
	buttons.push_back(settings);
	buttons.push_back(credits);

	for (int i = 0; i < 4; i++) {
		buttons[i].buttonShape.setSize(buttonSize);
		buttons[i].buttonShape.setOrigin(buttonOrigin);
		buttons[i].buttonShape.setPosition(buttonPos.x, (buttonPos.y + (i * 85) + 350));
		buttons[i].buttonShape.setFillColor(buttonColour);
		buttons[i].buttonShape.setOutlineColor(sf::Color::White);
	}

	buttons[2].buttonShape.setFillColor(sf::Color(125, 125, 125));

	
}

void MainMenu::initialiseTitle() {
	/* Set up title */
	title.setFont(font);
	title.setString("8 Bit Barry");
	title.setCharacterSize(100);
	sf::FloatRect bounds = title.getLocalBounds();
	title.setOrigin((bounds.left + bounds.width) / 2, (bounds.top + bounds.height) / 2);
	title.setPosition(window.getSize().x / 2, 125);
	title.setColor(ORANGE);
}

void MainMenu::initialiseText() {

	float charSize = 30;

	sf::Text play;
	sf::Text arcade;
	sf::Text settings;
	sf::Text credits;

	play.setString("Play");
	arcade.setString("Arcade Mode");
	settings.setString("Settings");
	credits.setString("Credits");

	buttons[0].buttonText = play;
	buttons[1].buttonText = arcade;
	buttons[2].buttonText = settings;
	buttons[3].buttonText = credits;

	sf::FloatRect bounds;

	for (int i = 0; i < 4; i++) {

		buttons[i].buttonText.setFont(font);
		buttons[i].buttonText.setColor(ORANGE);
		bounds = buttons[i].buttonText.getLocalBounds();
		buttons[i].buttonText.setOrigin((bounds.left + bounds.width) / 2, (bounds.top + bounds.height) / 2);
		buttons[i].buttonText.setPosition(buttons[i].buttonShape.getPosition());
	}

	buttons[2].buttonText.setColor(sf::Color(200, 200, 200));



}

void MainMenu::render() {

	window.clear();
	
	window.draw(background);

	for (Button b : buttons)
		window.draw(b.buttonShape);

	for (Button b : buttons)
		window.draw(b.buttonText);

	window.draw(title);

	window.display();
}

MainMenu::GameStates MainMenu::run() {

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
					for (int i = 0; i < 4; i++)
						buttons[i].isOver = false;
				}
				break;
			}
			case sf::Event::MouseButtonReleased: {
				if (buttons[0].isOver)
					return Story;
				if (buttons[1].isOver)
					return Arcade;
				if (buttons[3].isOver)
					return Credits;

			}
			}

		}
		update();
		render();
	}
}


int MainMenu::handleMouseOver() {

	sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

	if (buttons[0].buttonShape.getGlobalBounds().contains(mousePos))
		return 0;
	if (buttons[1].buttonShape.getGlobalBounds().contains(mousePos)) {
		return 1;
	}
	if (buttons[3].buttonShape.getGlobalBounds().contains(mousePos)) {
		return 3;
	}

	return 99;

}

void MainMenu::update() {

	for (int i = 0; i < 4; i++) {

		if (buttons[i].isOver)
			buttons[i].buttonShape.setOutlineThickness(3);
		else
			buttons[i].buttonShape.setOutlineThickness(0);
	}
}
