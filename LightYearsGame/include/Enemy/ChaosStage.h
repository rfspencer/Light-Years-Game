#pragma once

#include <SFML/Graphics.hpp>
#include "gameplay/GameStage.h"
#include "framework/TimerManager.h"

namespace ly
{
class ChaosStage : public GameStage
    {
    public:
        ChaosStage(World* world);

        void StartStage() override;

    private:
        void StageFinished() override;
        void SpawnVanguard();
        void SpawnTwinShooter();
        void SpawnHexagon();
        void SpawnUFO();

        void InreaseDifficulty();
        void StageDurationReached();

        sf::Vector2f GetRandomSpawnLocation() const;
        sf::Vector2f GetRandomSpawnLocationSide() const;

        float mSpawnInterval;
        float mMinSpawnInterval;

        float mSpawnIntervalDecrement;
        float mSpawnIntervalDecrementInterval;

        float mStageDuration;

        TimerHandle mDifficultTimerHandle;
        TimerHandle mSpawnTimer;
    };
}