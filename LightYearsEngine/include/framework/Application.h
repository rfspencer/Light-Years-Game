#pragma once

#include <SFML/Graphics.hpp>
#include "framework/Core.h"
#include "framework/World.h"

namespace ly
{

    class Application
    {
    public:
        Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title, sf::Uint32  style);
        void Run();

        template<typename WorldType>
        weak<WorldType> LoadWorld();

        sf::Vector2u GetWindowSize() const;
        sf::RenderWindow& GetWindow() { return mWindow; }
        const sf::RenderWindow& GetWindow() const { return mWindow; }
        void QuitApplication();

    private:
        bool DispatchEvent(const sf::Event& event);
        void TickInternal(float deltaTime);
        void RenderInternal();

        virtual void Render();
        virtual void Tick(float deltaTime);

        sf::RenderWindow mWindow;
        float mTargetFrameRate;
        sf::Clock mTickClock;

        shared<World> mCurrentWorld;
        shared<World> mPendingWorld;

        sf::Clock mCleanCycleClock;
        float mCleanCycleInterval;
    };

    template<typename WorldType>
    weak<WorldType> Application::LoadWorld()
    {
        shared<WorldType> newWorld{new WorldType{this}};
        mPendingWorld = newWorld;
        return  newWorld;
    }
}




