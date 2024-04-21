#pragma once

#include <functional>
#include "framework/Actor.h"

namespace ly
{
    class PlayerSpaceShip;
    using RewardFunction = std::function<void(PlayerSpaceShip*)>;

    class Reward : public Actor
    {
    public:
        Reward(World* world, const std::string& texturePath, RewardFunction rewardFunction, float speed = 200.f);

        void BeginPlay() override;
        void Tick(float deltaTime) override;

    private:
        void OnActorBeginOverlap(ly::Actor *otherActor) override;

        float mSpeed;
        RewardFunction mRewardFunction;
    };
}