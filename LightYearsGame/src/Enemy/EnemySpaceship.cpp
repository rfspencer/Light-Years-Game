
#include "Enemy/EnemySpaceship.h"

namespace ly
{

    EnemySpaceship::EnemySpaceship(World *owningWorld, const std::string &texturePath, float collisionDamage)
        : SpaceShip{owningWorld, texturePath}, mCollisionDamage{collisionDamage}
    {
        SetTeamID(2);
    }

    void EnemySpaceship::Tick(float deltaTime)
    {
        SpaceShip::Tick(deltaTime);

        if (IsActorOutOfWindowBounds(GetActorGlobalBounds().width))
        {
            Destroy();
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
}
