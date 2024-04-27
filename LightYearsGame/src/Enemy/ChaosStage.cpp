
#include "Enemy/ChaosStage.h"
#include "Enemy/Vanguard.h"
#include "Enemy/TwinBlade.h"
#include "Enemy/Hexagon.h"
#include "Enemy/UFO.h"
#include "framework/World.h"
#include "framework/MathUtility.h"


namespace ly
{

    ChaosStage::ChaosStage(World *world)
        : GameStage(world),
        mSpawnInterval{4.f},
        mMinSpawnInterval{0.8f},
        mSpawnIntervalDecrement{0.5f},
        mSpawnIntervalDecrementInterval{5.f},
        mStageDuration{60.f}
    {

    }

    void ChaosStage::StartStage()
    {
        mSpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnVanguard, mSpawnInterval);
        mDifficultTimerHandle= TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::IncreaseDifficulty, mSpawnIntervalDecrementInterval, true);
        TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::StageDurationReached, mStageDuration);
    }

    void ChaosStage::StageFinished()
    {
        TimerManager::Get().ClearTimer(mDifficultTimerHandle);
        TimerManager::Get().ClearTimer(mSpawnTimer);
    }

    void ChaosStage::SpawnVanguard()
    {
        weak<Vanguard> newVanguard = GetWorld()->SpawnActor<Vanguard>();
        newVanguard.lock()->SetActorLocation(GetRandomSpawnLocationTop());
        mSpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnTwinBlade, mSpawnInterval);
    }

    void ChaosStage::SpawnTwinBlade()
    {
        weak<TwinBlade> newTwinBlade = GetWorld()->SpawnActor<TwinBlade>();
        newTwinBlade.lock()->SetActorLocation(GetRandomSpawnLocationTop());
        mSpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnHexagon, mSpawnInterval);
    }

    void ChaosStage::SpawnHexagon()
    {
        weak<Hexagon> newHexagon= GetWorld()->SpawnActor<Hexagon>();
        newHexagon.lock()->SetActorLocation(GetRandomSpawnLocationTop());
        mSpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnUFO, mSpawnInterval);
    }

    void ChaosStage::SpawnUFO()
    {
        weak<UFO> newUFO = GetWorld()->SpawnActor<UFO>();
        sf::Vector2f spawnLocation = GetRandomSpawnLocationSide();

        auto windowSize = GetWorld()->GetWindowSize();
        sf::Vector2f center = sf::Vector2f{windowSize.x / 2.f, windowSize.y / 2.f};
        sf::Vector2f dirToCenter = center - spawnLocation;
        Normalize(dirToCenter);

        newUFO.lock()->SetActorLocation(spawnLocation);
        newUFO.lock()->SetVelocity(dirToCenter * 200.f);

        mSpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnVanguard, mSpawnInterval);
    }

    void ChaosStage::StageDurationReached()
    {
        FinishStage();
    }

    void ChaosStage::IncreaseDifficulty()
    {
        mSpawnInterval -= mSpawnIntervalDecrement;
        if(mSpawnInterval < mMinSpawnInterval)
        {
            mSpawnInterval = mMinSpawnInterval;
        }
    }

    sf::Vector2f ChaosStage::GetRandomSpawnLocationTop() const
    {
        auto windowSize = GetWorld()->GetWindowSize();
        float spawnX = RandomRange(100.f, windowSize.x - 100.f);
        float spawnY = -100.f;

        return {spawnX, spawnY};
    }

    sf::Vector2f ChaosStage::GetRandomSpawnLocationSide() const
    {
        auto windowSize = GetWorld()->GetWindowSize();
        float spawnLeft = RandomRange(-1, 1);
        float spawnLocationX = 0;

        if (spawnLeft < 0)
        {
            spawnLocationX = windowSize.x + 100.f;
        }
        else
        {
            spawnLocationX = -100.f;
        }

        float spawnLocationY = RandomRange(0, windowSize.y);

        return sf::Vector2f{spawnLocationX, spawnLocationY};
    }
}
