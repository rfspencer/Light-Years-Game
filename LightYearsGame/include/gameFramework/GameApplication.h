#pragma once

#include <framework/Application.h>
#include <framework/Core.h>

namespace ly
{
    class SpaceShip;

    class GameApplication : public Application
    {
    public:
        GameApplication();
        void Tick(float deltaTime) override;

    private:
        float counter;
        weak<SpaceShip> testPlayerSpaceship;
    };
}