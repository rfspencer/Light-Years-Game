#pragma once

#include "spaceship/SpaceShip.h"

namespace ly
{
    class EnemySpaceship : public SpaceShip
    {
    public:

        EnemySpaceship(World* owningWorld, const std::string& texturePath, float collisionDamage = 200.f);

        virtual void Tick(float deltaTime) override;
    private:

        float mCollisionDamage;
        virtual void OnActorBeginOverlap(Actor* other) override;
    };
}