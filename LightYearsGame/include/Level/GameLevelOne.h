#pragma once

#include "framework/World.h"

namespace ly
{
    class PlayerSpaceShip;

    class GameLevelOne : public World
    {
    public:
        GameLevelOne(Application* owningApp);

    private:
        void BeginPlay() override;
        void TimerCallback_Test();

        weak<PlayerSpaceShip> testPlayerSpaceship;
    };
}