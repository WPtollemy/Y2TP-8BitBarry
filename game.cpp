#include "stdafx.h"
#include <fstream>
#include <sstream>
#include "game.hpp"
#include "globals.hpp"

bool Game::life_awarded = false;
bool skip = false;

void Game::handle_events(sf::Window &window, Pacman &pacman)
{
	skip = false;

    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;

        case sf::Event::KeyReleased:
            switch (event.key.code)
            {
                case sf::Keyboard::P:
                    pause(pacman);
                    break;

                case sf::Keyboard::M:
					skip = true;
                    break;

                default:
                    break;
            }

            break;

        default:
            break;
        }
    }
}

void Game::real_time_key(PlayerLaser &player_laser, Player &player, Pacman &pacman)
{
    if (Globals::GAME_STATE == Globals::States::PAUSED || Globals::GAME_STATE == Globals::States::WAVE_SETUP || Globals::GAME_STATE == Globals::States::GAME_OVER)
        return;

    // Move Core player
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        player.move(1);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        player.move(-1);

    // Shoot laser
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !player.isHit() && !player_laser.isShooting())
    {
        sf::Vector2f playerpos = player.getSprite().getPosition();
        player_laser.shoot(playerpos.x, playerpos.y, pacman);
    }
}

void Game::draw_player_laser(sf::RenderWindow &window, PlayerLaser &laser)
{
    if (laser.isShooting())
        window.draw(laser.getShape());
}

bool Game::update_objects(Player &player, PlayerLaser &player_laser, Pacman &pacman, InvaderFormation &invaders, BarrierWall &barriers, LivesDisplay &lives_disp, Explosions &explosions, unsigned &game_score, unsigned &wave_on)
{
    // Don't do anything if paused, game over, or the wave is being setup (or menu!)
    if (Globals::GAME_STATE == Globals::States::PAUSED || Globals::GAME_STATE == Globals::States::WAVE_SETUP || Globals::GAME_STATE == Globals::States::GAME_OVER)
        return false;

    if (Globals::GAME_STATE != Globals::States::PLAYER_KILLED)
    {
        real_time_key(player_laser, player, pacman);
        player_laser.move(explosions);
        pacman.update(player_laser, game_score);
        invaders.update(player_laser, player, player_laser, pacman, lives_disp, explosions, game_score);
        barriers.handleCollisions(player_laser, invaders.getLasers(), invaders, explosions);
        explosions.update();
    }

    player.update(invaders, player_laser, pacman, lives_disp, explosions);

	if (invaders.getNumKilled() == invaders.getTotal())
		return true;
		//setup_wave(invaders, player_laser, player, barriers, earth, pacman, explosions, wave_on);

	if (skip)
		return true;

    if (game_score >= 1000 && !life_awarded)
    {
        life_awarded = true;
        lives_disp.addLife();
    }

    // Score can't go over 10,000
    if (game_score > 10000)
        game_score = 0;

	return false;
}

void Game::draw_text(sf::RenderWindow &window, const std::string msg, const unsigned x, const unsigned y, sf::Color color, unsigned size)
{
    sf::Font font;
    font.loadFromFile(Globals::FONTS_PATH + "space_invaders.ttf");

    sf::Text text;
    text.setFont(font);
    text.setString(msg);
    text.setCharacterSize(size);
    text.setColor(color);
    text.setPosition(x, y);

    window.draw(text);
}

void Game::draw_objects(sf::RenderWindow &window, LivesDisplay &lives_disp, Pacman &pacman, InvaderFormation &invaders, BarrierWall &barriers, Player &player, PlayerLaser &playerlaser, Explosions &explosions, unsigned &wave_on)
{
	window.clear(Globals::BG_COLOR);

	//score_disp.draw(window);
	pacman.draw(window);
	invaders.drawLasers();
	barriers.draw();
	Game::draw_player_laser(window, playerlaser);
	lives_disp.draw(window);
	explosions.draw(window);

	// If a wave is being setup, draw the invaders 1 at a time.
	if (Globals::GAME_STATE != Globals::States::WAVE_SETUP)
	{
		if (Globals::GAME_STATE != Globals::States::GAME_OVER)
			window.draw(player.getSprite());

		invaders.draw();
	}
	else
		draw_wave(invaders);

	if (Globals::GAME_STATE == Globals::States::GAME_OVER) {
		reset_game(lives_disp, pacman, invaders, barriers, player, playerlaser, explosions, wave_on);
		Globals::GAME_STATE = Globals::States::PLAY;
	}
		//handle_game_over(window, menu, score_disp, lives_disp, pacman, invaders, barriers, player, playerlaser, earth, explosions, wave_on);

    window.display();
}

void Game::updateFPS(sf::Window &window, const sf::Clock &fps_clock, float &fps_timer)
{
    float fps = 1.0f / (fps_clock.getElapsedTime().asSeconds() - fps_timer);
    std::ostringstream title;
    title << Globals::SCREEN_TITLE << " - " << round(fps) << "fps";
    window.setTitle(title.str());
    fps_timer = fps_clock.getElapsedTime().asSeconds();
}

void Game::pause(Pacman &pacman)
{
    // Don't attempt to pause game if player is in middle of death or wave is being setup.
    if (Globals::GAME_STATE == Globals::States::PLAYER_KILLED || Globals::GAME_STATE == Globals::States::WAVE_SETUP || Globals::GAME_STATE == Globals::States::GAME_OVER)
        return;

    if (Globals::GAME_STATE == Globals::States::PAUSED)
        Globals::GAME_STATE = Globals::States::PLAY;
    else
        Globals::GAME_STATE = Globals::States::PAUSED;

    pacman.pause();
}

void Game::handle_player_kill(InvaderFormation &invaders, PlayerLaser &player_laser, Pacman &pacman, Explosions &explosions)
{
    invaders.removeLasers();
    player_laser.stop();
    pacman.pause();
    explosions.reset();
    Globals::GAME_STATE = Globals::States::PLAYER_KILLED;
}

void Game::setup_wave(InvaderFormation &invaders, PlayerLaser &player_laser, Player &player, BarrierWall &barriers, Pacman &pacman, Explosions &explosions, unsigned &wave_on, bool start_game)
{
    Globals::GAME_STATE = Globals::States::WAVE_SETUP;

    // If the game just started, don't try to increase the wave number.
    if (!start_game)
        ++wave_on;

    // Reset the formation to the top if they get too far down.
    if (wave_on == 5)
        wave_on = 0;

    invaders.reset(wave_on);
    player_laser.stop();
    player.reset();
    barriers.reset();
    pacman.reset();
    explosions.reset();
}

void Game::draw_wave(InvaderFormation &invaders)
{
    // Bit of a kludge, but seems easiest method.
    static unsigned amount = 1;
    invaders.draw(amount);
    ++amount;

    // Sleep briefly before drawing the next Invader
    // Sleep is okay because nothing else is happening while they are being drawn
    sf::sleep(sf::milliseconds(10));

    if (amount == (invaders.getTotal() + 1))
    {
        amount = 1;
        Globals::GAME_STATE = Globals::States::PLAY;
    }
}

void Game::handle_game_over(sf::RenderWindow &window, Pacman &pacman)
{
    pacman.reset();
    std::string msg = "GAME OVER ";
    static unsigned char_on = 0;
    
    std::ostringstream ss;
    for (unsigned i = 0; i <= char_on; ++i)
    {
        ss << msg[i];
        ss << " ";
    }

    draw_text(window, ss.str(), 280, 100, sf::Color::Green, 32);

    if (char_on == msg.length() - 1)
    {
        sf::sleep(sf::seconds(2));
        char_on = 0;
        return;
    }
    else
        ++char_on;

    sf::sleep(sf::milliseconds(300));
}

void Game::reset_game(LivesDisplay &lives_disp, Pacman &pacman, InvaderFormation &invaders, BarrierWall &barriers, Player &player, PlayerLaser &playerlaser, Explosions &explosions, unsigned &wave_on)
{
	//return;
	skip = false;
	life_awarded = false;
    wave_on = 0;
    invaders.reset(wave_on);
    playerlaser.stop();
    player.reset();
    barriers.reset();
    pacman.reset();
    lives_disp.reset();
    explosions.reset();
}

unsigned Game::get_highscore()
{
    std::string highscore_txt;
    std::ifstream hs_file(Globals::HS_FILE);

    if (hs_file.is_open())
    {
        std::getline(hs_file, highscore_txt);
        hs_file.close();
    }
    // If file doesn't exist, set highscore to 0.
    else
        highscore_txt = "0";

    // If thereturned score is empty or contains an invalid score, set highscore to 0.
    if (highscore_txt.empty())
        highscore_txt = "0";
    else
    {
		std::locale loc;
        for (auto c : highscore_txt)
        {
            if (!std::isdigit(c, loc))
            {
                highscore_txt = "0";
                break;
            }
        }
    }

    unsigned highscore = std::stoi(highscore_txt);

    // A score of 10000 or above is invalid.
    return highscore < 10000 ? std::stoi(highscore_txt) : 0;

}

void Game::write_highscore(const unsigned score)
{
    std::ofstream hs_file(Globals::HS_FILE, std::ios::trunc);

    if (hs_file.is_open())
        hs_file << score;

    hs_file.close();
}
