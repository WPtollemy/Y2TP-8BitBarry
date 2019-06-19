#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "LivesDisplay.hpp"
#include "PlayerLaser.hpp"
#include "PacmanSprite.hpp"
#include "InvaderFormation.hpp"
#include "Barrier.hpp"
#include "Player.hpp"
#include "Explosions.hpp"

/* Functions that deal with the game but don't belong in a class. */

namespace Game
{
    extern bool life_awarded;

    // Handles any events that pop up (mainly window close)
    void handle_events(sf::Window &window, Pacman &pacman);

    // Handles real-time keyboard input
    void real_time_key(PlayerLaser &player_laser, Player &player, Pacman &pacman);

    // Update all game objects
    bool update_objects(Player &player, PlayerLaser &player_laser, Pacman &pacman, InvaderFormation &invaders, BarrierWall &barriers, LivesDisplay &lives_disp, Explosions &explosions, unsigned &game_score, unsigned &wave_on);

    // A wrapper for drawing player laser to check if it is shooting
    void draw_player_laser(sf::RenderWindow &window, PlayerLaser &laser);

    // Draws text in space invaders font to the screen at given position
    void draw_text(sf::RenderWindow &window, const std::string msg, const unsigned x, const unsigned y, sf::Color color = sf::Color::White, unsigned size = 24);

    // Draw all objects
    void draw_objects(sf::RenderWindow &window, LivesDisplay &lives_disp, Pacman &pacman, InvaderFormation &invaders, BarrierWall &barriers, Player &player, PlayerLaser &playerlaser, Explosions &explosions, unsigned &wave_on);

    // Calculates the current FPS and updates the window title with it.
    void updateFPS(sf::Window &window, const sf::Clock &fps_clock, float &fps_timer);

    void pause(Pacman &pacman);

    void handle_player_kill(InvaderFormation &invaders, PlayerLaser &player_laser, Pacman &pacman, Explosions &explosions);

    void setup_wave(InvaderFormation &invaders, PlayerLaser &player_laser, Player &player, BarrierWall &barriers, Pacman &pacman, Explosions &explosions, unsigned &wave_on, bool start_game = false);

    void draw_wave(InvaderFormation &invaders);

    void handle_game_over(sf::RenderWindow &window, Pacman &pacman);

    void reset_game(LivesDisplay &lives_disp, Pacman &pacman, InvaderFormation &invaders, BarrierWall &barriers, Player &player, PlayerLaser &playerlaser, Explosions &explosions, unsigned &wave_on);

    unsigned get_highscore();
    void write_highscore(const unsigned score);

}

#endif
