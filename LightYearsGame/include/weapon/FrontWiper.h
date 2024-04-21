#pragma once

#include <SFML/Graphics.hpp>
#include "weapon/BulletShooter.h"

namespace ly
{
    class FrontWiper : public Shooter
    {
    public:
        FrontWiper(Actor* ownerActor, float cooldownTime = 0.3f, const sf::Vector2f& localOffset = {0.f, 0.f}, float width = 60.f);

    private:

        void ShootImplementation() override;

        float mWidth;

        BulletShooter mShooter1;
        BulletShooter mShooter2;
        BulletShooter mShooter3;
        BulletShooter mShooter4;
    };
}