
#include "gameplay/HealthComponent.h"
#include "framework/Core.h"


namespace ly
{

    HealthComponent::HealthComponent(float health, float maxHealth)
        : mHealth{health},
        mMaxHealth{maxHealth}
    {

    }

    void HealthComponent::ChangeHealth(float amount)
    {
        if (amount == 0) return;
        if (mHealth == 0) return;

        mHealth += amount;
        if (mHealth < 0)
        {
            mHealth = 0;
        }

        if (mHealth > mMaxHealth)
        {
            mHealth = mMaxHealth;
        }

        if (amount < 0)
        {
            TakeDamage(-amount);
            if (mHealth <= 0)
            {
                HealthEmpty();
            }
        }
        else
        {
            HealthRegen(amount);
        }
    }

    void HealthComponent::TakeDamage(float damageAmount)
    {
        LY_LOG("Took damage: %f, current health %f/%f", damageAmount, GetHealth(), GetMaxHealth());
    }

    void HealthComponent::HealthEmpty()
    {
        LY_LOG("Dead");
    }

    void HealthComponent::HealthRegen(float regenAmount)
    {
        LY_LOG("Regen health: %f, current health %f/%f", regenAmount, GetHealth(), GetMaxHealth());
    }
}