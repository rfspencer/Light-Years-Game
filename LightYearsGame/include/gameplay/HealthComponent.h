#pragma once
#include "framework/Delegate.h"

namespace ly
{

    class HealthComponent
    {
    public:
        HealthComponent(float health, float maxHealth);

        void ChangeHealth(float amount);

        float GetHealth() { return mHealth; }
        float GetMaxHealth() { return mMaxHealth; }

        Delegate<float, float, float> onHealthChanged;

    private:
        void TakeDamage(float damageAmount);
        void HealthEmpty();
        void HealthRegen(float regenAmount);

        float mHealth;
        float mMaxHealth;
    };
}