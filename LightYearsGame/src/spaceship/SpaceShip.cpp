#include "spaceship/SpaceShip.h"

namespace ly
{
    SpaceShip::SpaceShip(World *owningWorld, const std::string &texturePath)
        : Actor(owningWorld, texturePath),
        mVelocity{}
    {

    }

    void SpaceShip::Tick(float deltaTime)
    {
        Actor::Tick(deltaTime);

        AddActorLocationOffset(GetVelocity() * deltaTime);
    }

    void SpaceShip::SetVelocity(const sf::Vector2f &newVelocity)
    {
        mVelocity = newVelocity;
    }

    void SpaceShip::Shoot()
    {

    }
}