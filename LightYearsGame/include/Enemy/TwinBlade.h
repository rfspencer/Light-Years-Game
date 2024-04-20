#pragma once

#include "Enemy/EnemySpaceship.h"
#include "weapon/BulletShooter.h"

namespace ly
{
    class TwinBlade : public EnemySpaceship
    {
    public:
        TwinBlade(World* owningWorld, const std::string& texturePath = "SpaceShooterRedux/PNG/Enemies/enemyBlack1.png", const sf::Vector2f& velocity = {0.f, 120.f});
        virtual void Tick(float deltaTime);
        virtual void Shoot() override;

    private:

        unique<BulletShooter> mShooterLeft;
        unique<BulletShooter> mShooterRight;
    };
}