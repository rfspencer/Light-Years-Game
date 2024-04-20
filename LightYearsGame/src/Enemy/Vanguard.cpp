
#include "Enemy/Vanguard.h"

namespace ly
{


    Vanguard::Vanguard(World *owningWorld, const std::string &texturePath, const sf::Vector2f &velocity)
        : EnemySpaceship(owningWorld, texturePath),
        mShooter{new BulletShooter(this)}
    {
        SetVelocity(velocity);
        SetActorRotation(180.f);
    }

    void Vanguard::Shoot()
    {
        mShooter->Shoot();
    }

    void Vanguard::Tick(float deltaTime)
    {
        EnemySpaceship::Tick(deltaTime);

        Shoot();
    }
}