#pragma once

#include "Enemy/EnemySpaceship.h"

namespace ly
{
    class BulletShooter;

    class UFO : public EnemySpaceship
    {
    public:
        UFO(World* owningWorld, const std::string& texturePath = "SpaceShooterRedux/PNG/ufoRed.png", const sf::Vector2f& velocity = sf::Vector2f{0.f, 100.f}, float rotationSpeed = 40.f);

        virtual void Tick(float deltaTime) override;

    private:
        virtual void Shoot() override;

        unique<BulletShooter> mShooter1;
        unique<BulletShooter> mShooter2;
        unique<BulletShooter> mShooter3;
        float mRotationSpeed;
    };
}