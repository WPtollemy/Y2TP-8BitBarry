#include "stdafx.h"
#include "StateManager.h"
#include "State.h"
namespace edy{
	namespace core{
		StateManager::StateManager(sf::RenderWindow* Window)
			//: window(window)
		{
			//window.create(sf::VideoMode(800, 750), "Man");// , sf::Style::Close | sf::Style::Titlebar);//448,576
			//mWindow.setFramerateLimit(60);//60 fps max
			//window = new sf::RenderWindow(sf::VideoMode(800, 750), "Man");
			window = Window;
			mFont.loadFromFile("bin/DejaVuSans.ttf");
			mPack.Font=&mFont;
			mPack.Manager=this;
			mPack.Window=window;
		}
		StateManager::~StateManager()
		{
			popTop(mStates.size());
			clearStacks();
		}
		void StateManager::popTop(int amount)
		{
			amount=std::min(amount,static_cast<int>(mStates.size()));
			for(int i=0;i<amount;++i)
			{
				mClear.push(mStates.top());
				mStates.pop();
			}
		}
		void StateManager::leaveBottom(int amount)
		{
			popTop(mStates.size()-amount);
		}
		void StateManager::pushTop(State * state)
		{
			mStates.push(state);
		}
		void StateManager::gameRun()
		{
			while(!mStates.empty())
			{
				mStates.top()->run(mPack);
				clearStacks();
			}
		}
		void StateManager::clearStacks()
		{
			while(!mClear.empty())
			{
				delete mClear.top();
				mClear.pop();
			}
		}

		void StateManager::clearStates() {
			while (!mStates.empty())
			{
				delete mStates.top();
				mStates.pop();
			}
		}
	}
}