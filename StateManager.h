#ifndef EE_STATEMANAGER_H_INCLUDED
#define EE_STATEMANAGER_H_INCLUDED
#include <stack>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
namespace edy{
	namespace core{
		class StateManager;
		class State;
		class PointerPack
		{
		public:
			sf::RenderWindow * Window;
			StateManager * Manager;
			sf::Font * Font;

		};
		class StateManager
		{
		public:
			StateManager();
			StateManager(sf::RenderWindow*);// = nullptr);// new sf::RenderWindow(sf::VideoMode(800, 750), "Man"));
			~StateManager();
			void popTop(int amount);
			void leaveBottom(int amount);
			void pushTop(State * state);
			void gameRun();
			void clearStates();
		private:
			void clearStacks();
			
			sf::Font mFont;
			PointerPack mPack;
			sf::RenderWindow* window;
			std::stack<State*> mStates,mClear;

		};

	}
}
#endif