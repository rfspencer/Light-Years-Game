#pragma once

#include "framework/Actor.h"

namespace ly
{
    class SpaceShip : public Actor
    {
    public:
        SpaceShip(World* owningWorld, const std::string& texturePath = "");
        void Tick(float deltaTime) override;

        void SetVelocity(const sf::Vector2f& newVelocity);
        sf::Vector2f GetVelocity() const { return mVelocity; }

        virtual void Shoot();

        void BeginPlay() override;

    private:
        sf::Vector2f mVelocity;
    };
}