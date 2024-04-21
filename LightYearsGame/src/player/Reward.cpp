#include "player/Reward.h"
#include "player/PlayerSpaceShip.h"
#include "weapon/ThreeWayShooter.h"
#include "weapon/FrontWiper.h"
#include "framework/World.h"

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
        PlayerSpaceShip* playerSpaceShip = dynamic_cast<PlayerSpaceShip*>(otherActor);

        if (playerSpaceShip != nullptr && !playerSpaceShip->IsPendingDestroy())
        {
            mRewardFunction(playerSpaceShip);
            Destroy();
        }
    }

    weak<Reward> CreateReward(World *world, const std::string &texturePath, RewardFunction rewardFunction)
    {
        weak<Reward> reward = world->SpawnActor<Reward>(texturePath, rewardFunction);
        return reward;
    }

    weak<Reward> CreateHealthReward(World *world)
    {
        return CreateReward(world, "SpaceShooterRedux/PNG/pickups/pill_green.png", RewardHealth);
    }

    weak<Reward> CreateThreeWayShooterReward(World *world)
    {
        return CreateReward(world, "SpaceShooterRedux/PNG/pickups/three_shooter_pickup.png", RewardThreeWayShooter);
    }

    weak<Reward> CreateFrontWiperReward(World *world)
    {
        return CreateReward(world, "SpaceShooterRedux/PNG/pickups/front_row_shooter_pickup.png", RewardFrontWiper);
    }

    void RewardHealth(PlayerSpaceShip *player)
    {
        static float rewardAmount = 10.f;
        if (player && !player->IsPendingDestroy())
        {
            player->GetHealthComp().ChangeHealth(rewardAmount);
        }
    }

    void RewardThreeWayShooter(PlayerSpaceShip *player)
    {
        if (player && !player->IsPendingDestroy())
        {
            player->SetShooter(unique<Shooter>{new ThreeWayShooter{player, 0.4f, {50.f, 0.f}}});
        }
    }

    void RewardFrontWiper(PlayerSpaceShip *player)
    {
        if (player && !player->IsPendingDestroy())
        {
            player->SetShooter(unique<Shooter>{new FrontWiper{player, 0.4f, {50.f, 0.f}}});
        }
    }
}