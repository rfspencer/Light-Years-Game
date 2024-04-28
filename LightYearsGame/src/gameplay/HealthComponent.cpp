
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

        onHealthChanged.Broadcast(amount, mHealth, mMaxHealth);

        if (amount < 0)
        {
            TakeDamage(-amount);
            if (mHealth <= 0)
            {
                HealthEmpty();
            }
        }
    }

    void HealthComponent::SetInitialHealth(float health, float maxHealth)
    {
        mHealth = health;
        mMaxHealth = maxHealth;
    }

    void HealthComponent::TakeDamage(float damageAmount)
    {
        onTakenDamage.Broadcast(damageAmount, mHealth, mMaxHealth);
    }

    void HealthComponent::HealthEmpty()
    {
        onHealthEmpty.Broadcast();
    }
}