#pragma once
#include "stdafx.h"
#include <ctime>
#include <SFML/Graphics.hpp>
#include "globals.hpp"
#include "game.hpp"
#include "Textures.hpp"

class SpaceInvadersClone
{
public:
	sf::RenderWindow &window;

	SpaceInvadersClone(sf::RenderWindow&);
	void run();
};