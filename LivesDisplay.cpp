#include "stdafx.h"
#include <sstream>
#include "LivesDisplay.hpp"
#include "game.hpp"

sf::Vector2f screenSize(1000, 2);
sf::RectangleShape bottomBar;

void LivesDisplay::reset()
{
    // First clear
    for (auto& player : this->players)
        delete player;
    this->players.clear();

    this->lives = this->LIVES_START;

    // Subtract 1 from lives because the last life is the player's player.
    for (unsigned i = 0; i < (this->lives - 1); ++i)
    {
        sf::Sprite *sprite = new sf::Sprite;
        sprite->setTexture(this->textures.COREplayer);
        sprite->setPosition(this->X + 75 + (i * 55), this->Y);
        this->players.push_back(sprite);
    }
}

LivesDisplay::LivesDisplay(Textures &textures): lives(LIVES_START), textures(textures)
{
    this->reset(); 
}

LivesDisplay::~LivesDisplay()
{
    for (auto& player : this->players)
        delete player;
    this->players.clear();
}

void LivesDisplay::removeLife()
{
    // Removes the last player from the vector.
    if (this->lives > 1)
    {
        delete this->players[this->lives - 2];
        this->players.pop_back();
    }

    // If player is out of lives it's game over!
    if (this->lives > 0)
        --this->lives;

    if (lives == 0)
        Globals::GAME_STATE = Globals::States::GAME_OVER;
}

void LivesDisplay::addLife()
{
    sf::Sprite *sprite = new sf::Sprite;
    sprite->setTexture(this->textures.COREplayer);
    sprite->setPosition(this->X + 75 + ((this->lives - 1) * 55), this->Y);
    this->players.push_back(sprite);

    ++this->lives;
}

void LivesDisplay::setLives(const unsigned num)
{
    while (this->lives > num)
        this->removeLife();
}

void LivesDisplay::draw(sf::RenderWindow &window)
{
	bottomBar.setSize(screenSize);
	bottomBar.setFillColor(sf::Color::Green);
	bottomBar.setPosition(0, window.getSize().y - 70);
	window.draw(bottomBar);

    std::ostringstream lives_left;
    lives_left << this->lives;

    // Draw number of lives left.
    Game::draw_text(window, lives_left.str(), this->X + 30, this->Y + 2); 

    Game::draw_text(window, "C R E D I T    0 0", this->X + 550, this->Y + 2); 

    // Draw player representing each life.
    for (auto& player : this->players)
        window.draw(*player);
}
