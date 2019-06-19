#ifndef SETTINGS_MENU_H
#define SETTINGS_MENU_H

#include <SFML\Graphics.hpp>

class ArcadeMenu {

	public:
		enum Games {
			Pong, Pacman, Snake, Helicopter, Space, Main
		};


	private:
		struct Button {
			sf::RectangleShape buttonShape;
			sf::Text buttonText;
			bool isOver = false;
		};

		const sf::Color ORANGE = sf::Color(255, 166, 0);
		const sf::Color BROWN = sf::Color(106, 47, 1);
		const sf::Color WILL = sf::Color(140, 127, 87);

		sf::RenderWindow& window;
		sf::Texture textBackground;
		sf::Sprite background;

		sf::Text title;
		sf::Font font;

		std::vector<Button> buttons;

	private:
		/* Private methods */
		void initialise();
		void initialiseButtons();
		void initialiseTitle();
		void initialiseText();

		int handleMouseOver();
		void render();
		void update();

	public:
		/* Constructor -- Detsructor */
		ArcadeMenu(sf::RenderWindow&);
		~ArcadeMenu();

		Games run();
};

#endif // !SETTINGS_MENU_H
