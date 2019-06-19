#ifndef SHIELD_H
#define SHIELD_H

#include <SFML/Graphics.hpp>
#include "Textures.hpp"
#include "PlayerLaser.hpp"
#include "InvaderFormation.hpp"

/* The barriers protection the player from incoming fire. */

class Barrier
{
private:
    // Individual barriers have unique texture because they are destructable.
    sf::Texture texture;
    sf::Sprite sprite;

    // Image made from texture for pixel collision
    sf::Image img;
    Textures &textures;

public:
    Barrier(Textures &textures, const int xpos, const int ypos);
    sf::Sprite& getSprite(){ return this->sprite; }

    void reset();

    // Handles for collisions with lasers
    void handleCollide(PlayerLaser &player_laser, Lasers &invader_lasers, Explosions &explosions);

    // Invaders destroy the barrier as they pass over it.
    void handleCollideInvaders(InvaderFormation &invaders);

    // Add splash damage to barrier
    void damageBarrier(int x, int y, const int dmg);

};

typedef std::vector<Barrier*> BarrierVector;

class BarrierWall
{
private:
	static constexpr unsigned Y = 520;

	// Where the first barrier starts and the gap between subsequent barriers
	static constexpr unsigned STARTX = 97;
	static constexpr unsigned GAP = 175;

	BarrierVector barriers;

	sf::RenderWindow &window;

public:
	BarrierWall(sf::RenderWindow &window, Textures &textures, const unsigned screenw);
	~BarrierWall();

	void reset();

	unsigned getY() const { return this->Y; }

	void handleCollisions(PlayerLaser &laser, Lasers &invader_lasers, InvaderFormation &invaders, Explosions &explosions);

	void draw();

};

#endif
