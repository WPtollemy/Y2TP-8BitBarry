#ifndef PLAYERLASER_H
#define PLAYERLASER_H

#include <SFML/Graphics.hpp>
#include "Explosions.hpp"

class Pacman;

/* The laser shot by the player.
 * Only 1 on screen at a time. */

class PlayerLaser
{
private:
    static constexpr unsigned WIDTH = 3;
    static constexpr unsigned HEIGHT = 15;
    static constexpr unsigned SHIELD_DMG = 10;

    static constexpr int SPEED = 10;
    sf::RectangleShape laser;
    bool is_shooting;

public:
    PlayerLaser();
    sf::RectangleShape& getShape(){ return this->laser; }
    bool isShooting() const { return this->is_shooting; }
    unsigned getDmg() const { return this->SHIELD_DMG; }

    // Begins the shooting movement
    void shoot(const unsigned startx, const unsigned starty, Pacman &pacman);

    // Laser moves upwards after shot
    void move(Explosions &explosions);

    // Called to make the laser stop shooting
    void stop();

};

#endif
