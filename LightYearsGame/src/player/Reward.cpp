#include "player/Reward.h"
#include "player/PlayerSpaceShip.h"

namespace ly
{

    Reward::Reward(World *world, const std::string &texturePath, RewardFunction rewardFunction, float speed)
        : Actor{world, texturePath},
        mRewardFunction{rewardFunction},
        mSpeed{speed}
    {

    }

    void Reward::BeginPlay()
    {
        Actor::BeginPlay();

        SetEnablePhysics(true);
    }

    void Reward::Tick(float deltaTime)
    {
        Actor::Tick(deltaTime);

        AddActorLocationOffset({0.f, mSpeed * deltaTime});
    }

    void Reward::OnActorBeginOverlap(ly::Actor *otherActor)
    {
        // TODO: clean up casting.
        PlayerSpaceShip* playerSpaceShip = static_cast<PlayerSpaceShip*>(otherActor);

        if (playerSpaceShip != nullptr && !playerSpaceShip->IsPendingDestroy())
        {
            mRewardFunction(playerSpaceShip);
        }
    }
}