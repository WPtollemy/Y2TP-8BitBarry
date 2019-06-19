#include "stdafx.h"
#include "Barrier.hpp"

BarrierWall::BarrierWall(sf::RenderWindow &window, Textures &textures, const unsigned screenw): window(window)
{
    // This loop creates 4 barriers across the screen.
    // -5 is to stop part of 5th barrier from drawing at edge
    for (unsigned i = this->STARTX; i < screenw - 5; i += this->GAP)
        this->barriers.push_back(new Barrier(textures, i, this->Y));
}

BarrierWall::~BarrierWall()
{
    for (auto& barrier : barriers)
        delete barrier;
    this->barriers.clear();
}

void BarrierWall::reset()
{
    for (auto& barrier : barriers)
        barrier->reset();
}

void BarrierWall::handleCollisions(PlayerLaser &laser, Lasers &invader_lasers, InvaderFormation &invaders, Explosions &explosions)
{
    for (auto& barrier : barriers)
    {
        barrier->handleCollide(laser, invader_lasers, explosions);
        barrier->handleCollideInvaders(invaders);
    }
}

void BarrierWall::draw()
{
    for (auto& barrier : barriers)
        this->window.draw(barrier->getSprite());
}
