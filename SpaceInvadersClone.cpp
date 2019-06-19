#include "stdafx.h"
#include <ctime>
#include <SFML/Graphics.hpp>
#include "globals.hpp"
#include "game.hpp"
#include "Textures.hpp"
#include "SpaceInvadersClone.h"


SpaceInvadersClone::SpaceInvadersClone(sf::RenderWindow &window)
	:window(window)
{
	//Blank Constructor
}

void SpaceInvadersClone::run()
{
	unsigned game_score = 0;
	unsigned wave_on = 0;

	/*sf::Clock fps_clock;
	float fps_timer = fps_clock.getElapsedTime().asSeconds();*/

	//sf::RenderWindow window(sf::VideoMode(Globals::SCREEN_WIDTH, Globals::SCREEN_HEIGHT), Globals::SCREEN_TITLE);
	window.setFramerateLimit(Globals::FRAME_RATE);

	/*sf::Image icon;
	icon.loadFromFile("images/icon.png");
	window.setIcon(32, 32, icon.getPixelsPtr());*/

	// This loads all textures.
	Textures textures;

	Pacman pacman(textures);

	InvaderFormation invaders(window, textures);

	BarrierWall barriers(window, textures, Globals::SCREEN_WIDTH);
	invaders.setBarrierLine(barriers.getY() - 20);

	Player player(textures, 100);

	PlayerLaser player_laser;// = PlayerLaser();// = new PlayerLaser();

	LivesDisplay lives_disp(textures);

	Explosions explosions(textures);


	/* Begin game loop */
	while (true)
	{
		Game::handle_events(window, pacman);
		if (Game::update_objects(player, player_laser, pacman, invaders, barriers, lives_disp, explosions, game_score, wave_on))
			return;
		Game::draw_objects(window, lives_disp, pacman, invaders, barriers, player, player_laser, explosions, wave_on);
		//Game::updateFPS(window, fps_clock, fps_timer);
	}
}