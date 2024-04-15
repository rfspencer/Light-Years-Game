#include "spaceship/SpaceShip.h"
#include "framework/MathUtility.h"

namespace ly
{
    SpaceShip::SpaceShip(World *owningWorld, const std::string &texturePath)
        : Actor(owningWorld, texturePath),
        mVelocity{},
        mHealthComponent{100.f, 100.f},
        mBlinkTime{0.f},
        mBlinkDuration{0.3f},
        mBlinkColorOffset{255, 0, 0, 255}
    {

    }

    void SpaceShip::Tick(float deltaTime)
    {
        Actor::Tick(deltaTime);

        AddActorLocationOffset(GetVelocity() * deltaTime);
        UpdateBlink(deltaTime);
    }

    void SpaceShip::BeginPlay()
    {
        Actor::BeginPlay();

        SetEnablePhysics(true);

        mHealthComponent.onHealthChanged.BindAction(GetWeakRef(), &SpaceShip::OnHealthChanged);
        mHealthComponent.onTakenDamage.BindAction(GetWeakRef(), &SpaceShip::OnTakenDamage);
        mHealthComponent.onHealthEmpty.BindAction(GetWeakRef(), &SpaceShip::OnBlowUp);
    }

    void SpaceShip::Blink()
    {
        if (mBlinkTime == 0)
        {
            mBlinkTime = mBlinkDuration;
        }
    }

    void SpaceShip::UpdateBlink(float deltaTime)
    {
        if (mBlinkTime > 0)
        {
            mBlinkTime -= deltaTime;
            mBlinkTime = mBlinkTime > 0 ? mBlinkTime : 0.f;

            GetSprite().setColor(LerpColor(sf::Color::White, mBlinkColorOffset, mBlinkTime));
        }
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
        Blink();
    }

    void SpaceShip::OnBlowUp()
    {
        Destroy();
    }
}