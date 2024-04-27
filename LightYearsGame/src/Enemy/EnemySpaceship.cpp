
#include "Enemy/EnemySpaceship.h"
#include "framework/MathUtility.h"
#include "player/PlayerManager.h"

namespace ly
{

    EnemySpaceship::EnemySpaceship(World *owningWorld, const std::string &texturePath, float collisionDamage,const List<RewardFactoryFunction> rewards)
        : SpaceShip{owningWorld, texturePath}, mCollisionDamage{collisionDamage}, mRewardFactories{rewards}, mScoreAwardAmount{10}
    {
        SetTeamID(2);
    }

    void EnemySpaceship::Tick(float deltaTime)
    {
        SpaceShip::Tick(deltaTime);

        if (IsActorOutOfWindowBounds(GetActorGlobalBounds().width * 2.f))
        {
            Destroy();
        }
    }

    void EnemySpaceship::SetScoreAwardAmount(unsigned int amount)
    {
        mScoreAwardAmount = amount;
    }

    void EnemySpaceship::SpawnReward()
    {
        if (mRewardFactories.size() == 0) return;

        int pick = (int)RandomRange(0, mRewardFactories.size());
        if (pick >= 0 && pick < mRewardFactories.size())
        {
            weak<Reward> newReward = mRewardFactories[pick](GetWorld());
            newReward.lock()->SetActorLocation(GetActorLocation());
        }
    }

    void EnemySpaceship::OnActorBeginOverlap(Actor *other)
    {
        SpaceShip::OnActorBeginOverlap(other);

        if (IsOtherHostile(other))
        {
            other->ApplyDamage(mCollisionDamage);
        }
    }

    void EnemySpaceship::BlewUp()
    {
        SpawnReward();
        Player* player = PlayerManager::Get().GetPlayer();
        if (player)
        {
            player->AddScore(mScoreAwardAmount);
        }
    }
}
