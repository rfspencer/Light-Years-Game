
#include "Enemy/UFO.h"
#include "weapon/BulletShooter.h"

namespace ly
{

    UFO::UFO(World *owningWorld, const std::string &texturePath, const sf::Vector2f& velocity, float rotationSpeed)
        : EnemySpaceship{owningWorld, texturePath},
        mShooter1{new BulletShooter{this, 1.f, sf::Vector2f{0.f, 0.f}, -60.f}},
        mShooter2{new BulletShooter{this, 1.f, sf::Vector2f{0.f, 0.f}, 180.f}},
        mShooter3{new BulletShooter{this, 1.f, sf::Vector2f{0.f, 0.f}, 60.f}},
        mRotationSpeed{rotationSpeed}
    {
        SetVelocity(velocity);
    }

    void UFO::Tick(float deltaTime)
    {
        EnemySpaceship::Tick(deltaTime);
        Shoot();
        AddActorRotationOffset(mRotationSpeed * deltaTime);
    }

    void UFO::Shoot()
    {
        mShooter1->Shoot();
        mShooter2->Shoot();
        mShooter3->Shoot();
    }
}
