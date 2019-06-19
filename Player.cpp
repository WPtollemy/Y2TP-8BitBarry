#include "stdafx.h"
#include "globals.hpp"
#include "game.hpp"
#include "Player.hpp"

void Player::flipFrame()
{
    if (this->frame_on == 1)
    {
        this->frame_on = 2;
        this->sprite.setTexture(this->textures.COREplayer_DEATH_2, true);
    }
    else
    {
        this->frame_on = 1;
        this->sprite.setTexture(this->textures.COREplayer_DEATH_1, true);
    }
}

void Player::reset()
{
    this->death_tick = this->DEATH_TICK_MAX;
    this->frame_tick = this->FRAME_TICK_MAX;
    this->frame_on = 1;
    this->hit = false;

    this->sprite.setTexture(this->textures.COREplayer, true);
    this->sprite.setPosition(this->Initial_X, this->Y);

    // Put the point of origin in center of player.
    this->sprite.setOrigin(this->sprite.getTexture()->getSize().x / 2, this->sprite.getTexture()->getSize().y / 2);

    if (Globals::GAME_STATE != Globals::States::WAVE_SETUP && Globals::GAME_STATE != Globals::States::GAME_OVER)
        Globals::GAME_STATE = Globals::States::PLAY;
}

Player::Player(Textures &textures, const int startx): Initial_X(startx), textures(textures), frame_on(1), hit(false), death_tick(DEATH_TICK_MAX), frame_tick(FRAME_TICK_MAX)
{
    this->reset(); 
}

void Player::move(const int dir)
{
    // +/- 10 because it stops the player from going slightly off screen
    if (!this->hit && ((dir == 1 && (this->sprite.getPosition().x < (Globals::SCREEN_WIDTH - (this->sprite.getGlobalBounds().width / 2) - 10)))
        || (dir == -1 && (this->sprite.getPosition().x > (0 + (this->sprite.getGlobalBounds().width / 2) + 10)))))
        this->sprite.move(this->SPEED * dir, 0);
}

void Player::die(InvaderFormation &invaders, PlayerLaser &player_laser, Pacman &pacman, Explosions &explosions)
{
    this->hit = true;
    this->sprite.setTexture(this->textures.COREplayer_DEATH_1, true);

    Game::handle_player_kill(invaders, player_laser, pacman, explosions);
}

void Player::handleHit(InvaderFormation &invaders, PlayerLaser &player_laser, Pacman &pacman, Explosions &explosions)
{
    for (auto& laser : invaders.getLasers())
    {
        if (!this->hit && laser->willHurt() && (laser->checkCollide(this->sprite.getGlobalBounds())))
        {
            this->die(invaders, player_laser, pacman, explosions);
            return;
        }
    }
}

void Player::update(InvaderFormation &invaders, PlayerLaser &player_laser, Pacman &pacman, LivesDisplay &lives_disp, Explosions &explosions)
{
    this->handleHit(invaders, player_laser, pacman, explosions);
    if (this->hit)
    {
        --this->death_tick;
        if (this->death_tick <= 0)
        {
            lives_disp.removeLife();
            pacman.pause(); // Unpauses the UFO... (yeah I know)
            this->reset();
        }

        --this->frame_tick;
        if (this->frame_tick <= 0)
        {
            this->flipFrame();
            this->frame_tick = this->FRAME_TICK_MAX;
        }
    }
}
