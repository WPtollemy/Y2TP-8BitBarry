#ifndef EE_GAMESTATE_H_INCLUDED
#define EE_GAMESTATE_H_INCLUDED
#include "State.h"
#include "GameControl.h"
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Text.hpp>
namespace edy{
	namespace core{
		class PointerPack;
	}
	namespace state{
		class GameState : public core::State
		{
		public:
			GameState();
			virtual void run(core::PointerPack& pack);
			bool loadMap();

		private:
			//methods:
			void drawAll();
			void drawCherry(int x,int y);
			void drawBooster(int x,int y);
			void drawPill(int x,int y);
			void drawGhosts();
			//vars:
			sf::Text score;
			bool mapOk;
			sf::Texture spriteFile;
			sf::Sprite guys[5],leftEye,rightEye;
			core::PointerPack * pointerPack;
			int currentMap,mScore,pacframe;
			std::string mapFile[3];
			pac::PacEngine pacEngine;
			sf::Clock timerClock;
		};
	}
}
#endif