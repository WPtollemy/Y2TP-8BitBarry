#include "stdafx.h"
#include "PacmanGame.h"

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

	edy::core::StateManager game(window);
	game.pushTop(new edy::state::GameState);
	game.gameRun();
}