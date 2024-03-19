#pragma once

#include <framework/Application.h>
#include <framework/Core.h>

namespace ly
{
    class PlayerSpaceShip;

    class GameApplication : public Application
    {
    public:
        GameApplication();
        void Tick(float deltaTime) override;

    private:
        float counter;
        weak<PlayerSpaceShip> testPlayerSpaceship;
    };
}