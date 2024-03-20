#pragma once

#include "weapon/Shooter.h"
#include <SFML/System.hpp>

namespace ly
{
    class BulletShooter : public Shooter
    {
    public:
        BulletShooter(Actor* owner, float cooldownTime = 1.f);

        bool IsOnCooldown() const override;

    private:
        void ShootImplementation() override;
        sf::Clock mCooldownClock;
        float mCooldownTime;
    };
}