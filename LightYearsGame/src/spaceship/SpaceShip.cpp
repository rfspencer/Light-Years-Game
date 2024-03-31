#include "spaceship/SpaceShip.h"

namespace ly
{
    SpaceShip::SpaceShip(World *owningWorld, const std::string &texturePath)
        : Actor(owningWorld, texturePath),
        mVelocity{},
        mHealthComponent{100.f, 100.f}
    {

    }

    void SpaceShip::Tick(float deltaTime)
    {
        Actor::Tick(deltaTime);

        AddActorLocationOffset(GetVelocity() * deltaTime);
    }

    void SpaceShip::BeginPlay()
    {
        Actor::BeginPlay();

        SetEnablePhysics(true);
    }

    void SpaceShip::SetVelocity(const sf::Vector2f &newVelocity)
    {
        mVelocity = newVelocity;
    }

    void SpaceShip::Shoot()
    {

    }
}