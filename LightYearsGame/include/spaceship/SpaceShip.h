#pragma once

#include "framework/Actor.h"

#include "gameplay/HealthComponent.h"

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
        void ApplyDamage(float amount) override;

        void BeginPlay() override;

        HealthComponent& GetHealthComp() { return mHealthComponent; }

    private:
        void Blink();

        void UpdateBlink(float deltaTime);

        virtual void OnHealthChanged(float amount, float health, float maxHealth);
        virtual void OnTakenDamage(float amount, float health, float maxHealth);
        virtual void OnBlowUp();
        virtual void BlewUp();

        sf::Vector2f mVelocity;
        HealthComponent mHealthComponent;

        float mBlinkTime;
        float mBlinkDuration;
        sf::Color mBlinkColorOffset;

    };
}