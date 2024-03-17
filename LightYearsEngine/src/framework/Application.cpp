#include "framework/Application.h"
#include "framework/World.h"

namespace ly
{
    Application::Application()
        : mWindow(sf::VideoMode(600, 800), "Light Years"),
        mTargetFrameRate{60.f},
        mTickClock{},
        currentWorld{nullptr}
    {

    }

    void Application::Run()
    {
        mTickClock.restart();
        float accumulatedTime = 0.f;
        float targetDeltaTime = 1.f / mTargetFrameRate;

        while(mWindow.isOpen())
        {
            sf::Event windowEvent;
            while(mWindow.pollEvent(windowEvent))
            {
                if(windowEvent.type == sf::Event::EventType::Closed)
                {
                    mWindow.close();
                }
            }

            float frameDeltaTime = mTickClock.restart().asSeconds();
            accumulatedTime += frameDeltaTime;
            while(accumulatedTime > targetDeltaTime)
            {
                accumulatedTime -= targetDeltaTime;
                TickInternal(targetDeltaTime);
                RenderInternal();
            }
        }
    }

    void Application::TickInternal(float deltaTime)
    {
        Tick(deltaTime);

        if (currentWorld)
        {
            currentWorld->TickInternal(deltaTime);
        }
    }

    void Application::RenderInternal()
    {
        mWindow.clear();

        Render();

        mWindow.display();
    }

    void Application::Render()
    {
        sf::RectangleShape rect{sf::Vector2f{100.f, 100.f}};
        rect.setFillColor(sf::Color::Green);
        rect.setOrigin(50.f, 50.f);
        rect.setPosition(mWindow.getSize().x / 2.f, mWindow.getSize().y / 2.f);
        
        mWindow.draw(rect);
    }

    void Application::Tick(float deltaTime)
    {

    }
}