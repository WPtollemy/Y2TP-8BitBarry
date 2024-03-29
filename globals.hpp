#ifndef GLOBALS_H
#define GLOBALS_H

#include <string>
#include <SFML/Graphics.hpp>

/* Globals that are useful for all classes. */


namespace Globals
{
    // The different states the game can be in.
    enum States
    {
        PLAY, // The player is actually playing the game
        PAUSED, // Player has paused the game
        WAVE_SETUP, // When a new wave begins, this draws the Invaders fancyily
        PLAYER_KILLED, // The player's player just got shot and is playing the death animation
        GAME_OVER // All lives are gone, or Invaders have touched down.
    };

    const std::string SCREEN_TITLE = "Space Invaders!";
    constexpr unsigned SCREEN_WIDTH = 800;
    constexpr unsigned SCREEN_HEIGHT = 730;
    constexpr unsigned FRAME_RATE = 60;
    const sf::Color BG_COLOR = sf::Color::Black;

    const std::string SOUNDS_PATH = "SpaceInvaders/sounds/";
    const std::string SPRITES_PATH = "SpaceInvaders/sprites/";
    const std::string FONTS_PATH = "SpaceInvaders/fonts/";

    const std::string HS_FILE = "misc/definitely_NOT_highscore.sav";

    extern States GAME_STATE;
}

#endif
