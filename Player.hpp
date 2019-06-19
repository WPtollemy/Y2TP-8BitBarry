#ifndef PLAYERplayer_H
#define PLAYERplayer_H

#include <SFML/Graphics.hpp>
#include "Textures.hpp"
#include "InvaderFormation.hpp"
#include "Explosions.hpp"

/* The player's ship. */

class Player
{
private:

    const unsigned Initial_X;
    static constexpr unsigned Y = 623;

    static constexpr int SPEED = 5; // Movement speed of player
    static constexpr unsigned DEATH_TICK_MAX = 50;
    static constexpr unsigned FRAME_TICK_MAX = 3;

    Textures &textures;
    sf::Sprite sprite;

    unsigned frame_on;
    bool hit;
    unsigned death_tick;
    unsigned frame_tick;

    void flipFrame();

public:
    Player(Textures &textures, const int startx);
    bool isHit() const { return this->hit; }

    void reset();
    void move(const int dir);
    const sf::Sprite& getSprite() const { return this->sprite; }
    void die(InvaderFormation &invaders, PlayerLaser &player_laser, Pacman &pacman, Explosions &explosions);
    void handleHit(InvaderFormation &invaders, PlayerLaser &player_laser, Pacman &pacman, Explosions &explosions);
    void update(InvaderFormation &invaders, PlayerLaser &player_laser, Pacman &pacman, LivesDisplay &lives_disp, Explosions &explosions);

};

#endif
