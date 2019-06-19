
#include "stdafx.h"
#include "GameSetter.h"
#include "toString.h"
#include <SFML/Window/Event.hpp>
#include "StateManager.h"

#include <iostream>
namespace edy{
	namespace state{
		GameState::GameState():currentMap(0),mScore(0),pointerPack(0x0)
		{
			pacframe=0;
			spriteFile.loadFromFile("testpac2.tga");
			//mAtlas.setSmooth(true);
			for(int i=0;i<=4;++i)
			{
				guys[i].setTexture(spriteFile);
				guys[i].setOrigin(12.5f,12.5f);
				guys[i].setTextureRect(sf::IntRect(25,26,25,25));
			}
			leftEye.setTexture(spriteFile);
			rightEye.setTexture(spriteFile);
			leftEye.setTextureRect(sf::IntRect(0,26,4,4));
			rightEye.setTextureRect(sf::IntRect(0,26,4,4));
			leftEye.setOrigin(2.f,2.f);
			rightEye.setOrigin(2.f,2.f);
			guys[0].setTextureRect(sf::IntRect(0,0,25,25));
			guys[1].setColor(sf::Color::Red);
			guys[2].setColor(sf::Color::Magenta);
			guys[3].setColor(sf::Color::Yellow);
			guys[4].setColor(sf::Color::Cyan);
			mapFile[0]="Level2.txt";
			mapFile[1]="Level2.txt";


		}
		bool GameState::loadMap()
		{
			if(!pacEngine.loadMap(mapFile[currentMap++]))
			{
				std::cout << "Couldn't load map";
				//mPack->Manager->pushTop(new ErrState("Failed Map Loading"));
				return false;
			}
			return true;
		}
		void GameState::run(core::PointerPack& pack)
		{
			if(!pointerPack)//first time run() call inits:
			{
				pointerPack=&pack;
				mapOk=loadMap();
				score.setFont(*pack.Font);
				score.setCharacterSize(32);
				score.setPosition(80.f,500.f);
			}
			sf::Time delta(sf::seconds(1.f/60.f)),stock;
			sf::Clock clock;
			sf::Event seve;
			pac::PacEvent peve;
			timerClock.restart();
			while(mapOk)
			{
				while(pack.Window->pollEvent(seve))
				{
					if(seve.type==sf::Event::Closed)
					{
						pack.Manager->popTop(100);
						return;
					}
					if(seve.type==sf::Event::KeyPressed)
					{
						switch(seve.key.code)
						{
						case sf::Keyboard::W:
						case sf::Keyboard::Up:
							pacEngine.setPacDirection(pac::PacEntity::Up);
							break;
						case sf::Keyboard::S:
						case sf::Keyboard::Down:
							pacEngine.setPacDirection(pac::PacEntity::Down);
							break;
						case sf::Keyboard::A:
						case sf::Keyboard::Left:
							pacEngine.setPacDirection(pac::PacEntity::Left);
							break;
						case sf::Keyboard::D:
						case sf::Keyboard::Right:
							pacEngine.setPacDirection(pac::PacEntity::Right);
							break;
						case sf::Keyboard::M:
							pacEngine.skipMap();
							break;
						}
					}
				}//seve
				while(pacEngine.getEvent(peve))
				{
					switch(peve.type)
					{
					case pac::EventType::PillsExhausted: {	//Player succeeds
						return;
					}
					case pac::EventType::ScoreChange:
						mScore+=peve.data;
						score.setString("Score:"+sup::toString(mScore));
						break;
					}
				}//peve
				pack.Window->clear();
				stock+=clock.restart();

				while(stock>=delta)
				{
					stock-=delta;
					pacEngine.update();
				}
				drawAll();

				//pack.Window->draw(score);
				//pack.Window->draw(lives);

				pack.Window->display();
			}
		}
		void GameState::drawCherry(int x,int y)
		{
			sf::Sprite spr(spriteFile);
			spr.setPosition(x*16.f,y*16.f);
			spr.setTextureRect(sf::IntRect(75,26,25,25));
			pointerPack->Window->draw(spr);
		}
		void GameState::drawBooster(int x,int y)
		{
			sf::Vertex arr[4];
			arr[0].position=sf::Vector2f(16*x+1.f,y*16+1.f);
			arr[1].position=sf::Vector2f(16*x+1.f,y*16+10.f);
			arr[2].position=sf::Vector2f(16*x+10.f,y*16+10.f);
			arr[3].position=sf::Vector2f(16*x+10.f,y*16+1.f);
			pointerPack->Window->draw(arr,4,sf::Quads);
		}
		void GameState::drawPill(int x,int y)
		{
			sf::Vertex arr[4];
			arr[0].position=sf::Vector2f(16*x+3.f,y*16+3.f);
			arr[1].position=sf::Vector2f(16*x+3.f,y*16+7.f);
			arr[2].position=sf::Vector2f(16*x+7.f,y*16+7.f);
			arr[3].position=sf::Vector2f(16*x+7.f,y*16+3.f);
			pointerPack->Window->draw(arr,4,sf::Quads);
		}
		void GameState::drawGhosts()
		{
			if(timerClock.getElapsedTime()>sf::seconds(0.2f))
			{
				timerClock.restart();
				++pacframe;
				pacframe%=4;
				guys[0].setTextureRect(sf::IntRect(25*(3-pacframe),0,25,25));

				//scared/nonscared color switches,
				guys[1].setColor(pacEngine.getScareStatus(1)==pac::PacEngine::Brave?sf::Color::Red:sf::Color::Blue);
				guys[2].setColor(pacEngine.getScareStatus(2)==pac::PacEngine::Brave?sf::Color::Magenta:sf::Color::Blue);
				guys[3].setColor(pacEngine.getScareStatus(3)==pac::PacEngine::Brave?sf::Color::Yellow:sf::Color::Blue);
				guys[4].setColor(pacEngine.getScareStatus(4)==pac::PacEngine::Brave?sf::Color::Cyan:sf::Color::Blue);
				for(int i=1;i<=4;++i)
				{
					guys[i].setTextureRect(sf::IntRect(25+(pacframe%2)*25,26,25,25));
					if(pacEngine.getScareStatus(i)==pac::PacEngine::Blinking)//blinking color switches
					{
						guys[i].setColor(pacframe%2?sf::Color::White:sf::Color::Blue);
					}
				}
			}
		}
		void GameState::drawAll()	//*****************************************************************Map stuff here
		{
			drawGhosts();
			pacEngine.makeWallsMap(*pointerPack->Window);
			for(int i=0;i<=4;++i)
			{
				guys[i].setPosition(pacEngine.getPosition(i));
			}
			guys[0].setRotation(pacEngine.getRotation(0));
			for(int x=0;x<27;++x)for(int y=0;y<31;++y)
			{
				switch(pacEngine.mapArray[x][y])
				{
				case pac::PacEngine::Cherry:
					drawCherry(x,y);
					break;
				case pac::PacEngine::Booster:
					drawBooster(x,y);
					break;
				case pac::PacEngine::Pill:
					drawPill(x,y);
					break;
				}
			}
			pointerPack->Window->draw(guys[0]);
			for(int i=1;i<=4;++i)
			{
				if(pacEngine.getScareStatus(i)!=pac::PacEngine::Dead) pointerPack->Window->draw(guys[i]);
				leftEye.setPosition(guys[i].getPosition());
				rightEye.setPosition(guys[i].getPosition());
				leftEye.move(-4.f,-3.f);
				rightEye.move(4.f,-3.f);
				if(pacEngine.getScareStatus(i)==pac::PacEngine::Brave)
				{
					leftEye.setRotation(pacEngine.getRotation(i));
					rightEye.setRotation(pacEngine.getRotation(i));
				}
				else
				{
					leftEye.setRotation(90);//90 is down in 2d coord system with reversed y axis
					rightEye.setRotation(90);
				}
				pointerPack->Window->draw(leftEye);
				pointerPack->Window->draw(rightEye);
			}
		}
	}
}