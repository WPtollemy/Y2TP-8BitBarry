#ifndef INVADERLASER_H
#define INVADERLASER_H

#include <SFML/Graphics.hpp>
#include "globals.hpp"
#include "Invader.hpp"


/* The laser shot by Space Invaders. */

class InvaderLaser
{
// The powered laser looks like a lightning bolt and does more damage to barriers
public: enum LaserType { NORMAL, POWERED };

protected:
    const LaserType TYPE;

    const int SPEED; // How fast the laser moves.
    const unsigned SHIELD_DMG; // How much damage it does to barriers

    const unsigned SHIELD_LINE;

    bool hit; // Whether or not hit something and about to be removed.

    bool will_hurt; // Whether or not the laser will actually hurt the player.

    // The Invader that shot this bullet.
    Invader &owner;

    // Make constructor protected because InvaderLasers should never be instantiated directly.
    InvaderLaser(const LaserType type, const int speed, const unsigned barrier_dmg, const unsigned barrier_line, const bool will_hurt, Invader &owner): TYPE(type), SPEED(speed), SHIELD_DMG(barrier_dmg), SHIELD_LINE(barrier_line), hit(false), will_hurt(will_hurt), owner(owner)
    {
        owner.incLasersOnScreen();
    }

public:
    /* Note to future self: 
     * Always declare virtual destructor if class will be derived from.
     * This ensures derived destructor is called first.
     * Though in this case subclasses don't implement their own destructors.
     * Compiler still complains without it. */
    virtual ~InvaderLaser()
    {
        this->owner.decLasersOnScreen();
    }

    /* Methods whose behavior are the same for both types of lasers. */
    bool isHit() const { return this->hit; }
    bool willHurt() const { return this->will_hurt; }
    void setHit() { this->hit = true; }
    unsigned getDmg() const { return this->SHIELD_DMG; }
    LaserType getType() const { return this->TYPE; }
    void remove(){ this->hit = true; }

    /* The below are all pure virtual methods and MUST be implemented by subclasses.
     * Their behavior differs depending on the type of laser. */
    virtual unsigned getX() const = 0;
    virtual unsigned getY() const = 0;
    virtual void move() = 0;
    virtual void draw(sf::RenderWindow &window) = 0;

    // Overload checkCollide method to allow check against rect or point.
    virtual bool checkCollide(const sf::FloatRect rect) const = 0;
    virtual bool checkCollide(const unsigned x, const unsigned y) const = 0;

};

class NormalInvaderLaser : public InvaderLaser
{
private:
	static constexpr unsigned HEIGHT = 15;
	static constexpr unsigned WIDTH = 12;
	static constexpr unsigned THICKNESS = 2;
	static constexpr double h_part_moverate = 1.3; // Speed the horz part moves relative to the vert part.

												   // Shapes that make up a normal laser.
	sf::RectangleShape v_part;
	sf::RectangleShape h_part;

	int h_part_movedir; // Direction the horz part is moving.

						// Used to animate the horizontal part moving up and down.
	void moveHPart();

public:
	NormalInvaderLaser(const unsigned x, const unsigned y, const unsigned barrier_line, const bool will_hurt, Invader &owner);
	virtual ~NormalInvaderLaser() {}

	virtual unsigned getX() const;
	virtual unsigned getY() const;
	virtual void move();
	virtual void draw(sf::RenderWindow &window);

	// Overload checkCollide method to allow rect or point
	virtual bool checkCollide(const unsigned x, const unsigned y) const;
	virtual bool checkCollide(const sf::FloatRect rect) const;

};

#endif
