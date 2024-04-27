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
                       const List<RewardFactoryFunction> rewards =
                               {
                                       CreateHealthReward,
                                       CreateThreeWayShooterReward,
                                       CreateFrontWiperReward
                               }
                       );

        virtual void Tick(float deltaTime) override;
        void SetScoreAwardAmount(unsigned int amount);

    private:
        void SpawnReward();
        float mCollisionDamage;
        unsigned int mScoreAwardAmount;
        virtual void OnActorBeginOverlap(Actor* other) override;
        void BlewUp() override;

        List<RewardFactoryFunction> mRewardFactories;
    };
}