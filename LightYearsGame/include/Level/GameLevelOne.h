#pragma once

#include "framework/World.h"
#include "framework/TimerManager.h"

namespace ly
{
    class PlayerSpaceShip;
    class GameplayHUD;

    class GameLevelOne : public World
    {
    public:
        GameLevelOne(Application* owningApp);

    private:
        void AllGameStagesFinished() override;

        virtual void BeginPlay() override;

        weak<PlayerSpaceShip> mPlayerSpaceShip;
        void PlayerSpaceShipDestroyed(Actor* destroyedPlayerSpaceShip);

        weak<GameplayHUD> mGameplayHUD;

        TimerHandle timerHandle_Test;

        virtual void InitGameStages() override;

        void SpawnCosmetics();

        virtual void GameOver();

        void QuitGame();
        void RestartGame();
    };
}