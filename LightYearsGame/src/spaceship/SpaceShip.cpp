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

        mHealthComponent.onHealthChanged.BindAction(GetWeakRef(), &SpaceShip::OnHealthChanged);
        mHealthComponent.onTakenDamage.BindAction(GetWeakRef(), &SpaceShip::OnTakenDamage);
        mHealthComponent.onHealthEmpty.BindAction(GetWeakRef(), &SpaceShip::OnBlowUp);
    }

    void SpaceShip::SetVelocity(const sf::Vector2f &newVelocity)
    {
        mVelocity = newVelocity;
    }

    void SpaceShip::Shoot()
    {

    }

    void SpaceShip::ApplyDamage(float amount)
    {
        mHealthComponent.ChangeHealth(-amount);
    }

    void SpaceShip::OnHealthChanged(float amount, float health, float maxHealth)
    {

    }

    void SpaceShip::OnTakenDamage(float amount, float health, float maxHealth)
    {

    }

    void SpaceShip::OnBlowUp()
    {
        Destroy();
    }
}