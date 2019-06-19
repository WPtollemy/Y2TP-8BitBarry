#include "stdafx.h"
#include "PacmanGame.h"

#include <iostream>

/*
	Constructor -- Destructor
*/
PacmanGame::PacmanGame(sf::RenderWindow* window)
	: window(window) {
	//game = edy::core::StateManager(window);
}

PacmanGame::~PacmanGame() {

}

/*
	Rest of methods
*/

void PacmanGame::run() {

	game = edy::core::StateManager(window);
	game.pushTop(new edy::state::GameState);
	game.gameRun();
}