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
        void SetInitialHealth(float health, float maxHealth);

        Delegate<float, float, float> onHealthChanged;
        Delegate<float, float, float> onTakenDamage;
        Delegate<> onHealthEmpty;

    private:
        void TakeDamage(float damageAmount);
        void HealthEmpty();

        float mHealth;
        float mMaxHealth;
    };
}