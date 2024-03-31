#pragma once


namespace ly
{

    class HealthComponent
    {
    public:
        HealthComponent(float health, float maxHealth);

        void ChangeHealth(float amount);

        float GetHealth() { return mHealth; }
        float GetMaxHealth() { return mMaxHealth; }

    private:
        void TakeDamage(float damageAmount);
        void HealthEmpty();
        void HealthRegen(float regenAmount);

        float mHealth;
        float mMaxHealth;
    };
}