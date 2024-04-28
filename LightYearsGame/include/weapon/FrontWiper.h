#pragma once

#include <SFML/Graphics.hpp>
#include "weapon/BulletShooter.h"

namespace ly
{
    class FrontWiper : public Shooter
    {
    public:
        FrontWiper(Actor* ownerActor, float cooldownTime = 0.3f, const sf::Vector2f& localOffset = {0.f, 0.f}, float localRotationOffset = 0.f, float width = 60.f);

        void IncrementLevel(int amount = 1) override;
        void SetCurrentLevel(int newLevel) override;

    private:

        void ShootImplementation() override;

        float mWidth;

        BulletShooter mShooter1;
        BulletShooter mShooter2;
        BulletShooter mShooter3;
        BulletShooter mShooter4;

        BulletShooter mShooter5;
        BulletShooter mShooter6;
    };
}