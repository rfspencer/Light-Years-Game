#pragma once

#include "spaceship/SpaceShip.h"
#include "player/Reward.h"

namespace ly
{
    class EnemySpaceship : public SpaceShip
    {
    public:

        EnemySpaceship(World *owningWorld,
                       const std::string &texturePath,
                       float collisionDamage = 200.f,
                       float rewardSpawnWeight = 0.5f,
                       const List<RewardFactoryFunction> rewards =
                               {
                                       CreateHealthReward,
                                       CreateThreeWayShooterReward,
                                       CreateFrontWiperReward,
                                       CreateLifeReward
                               }
                       );

        virtual void Tick(float deltaTime) override;
        void SetScoreAwardAmount(unsigned int amount);
        void SetRewardSpawnWeight(float weight);

    private:
        void SpawnReward();
        float mCollisionDamage;
        unsigned int mScoreAwardAmount;
        float mRewardSpawnWeight;
        void OnActorBeginOverlap(Actor* other) override;
        void BlewUp() override;

        List<RewardFactoryFunction> mRewardFactories;
    };
}