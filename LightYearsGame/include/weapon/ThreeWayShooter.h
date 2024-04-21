#pragma once

#include <SFML/Graphics.hpp>

#include "weapon/BulletShooter.h"


namespace ly
{
    class ThreeWayShooter : public Shooter
    {
    public:
        ThreeWayShooter(Actor* owner, float cooldownTime = 0.1f, const sf::Vector2f& localOffset = {0.f, 0.f});

        BulletShooter mShooterLeft;
        BulletShooter mShooterMid;
        BulletShooter mShooterRight;

        BulletShooter mTopShooterLeft;
        BulletShooter mTopShooterRight;

        void IncrementLevel(int amount = 1) override;

    private:

        void ShootImplementation() override;
    };
}