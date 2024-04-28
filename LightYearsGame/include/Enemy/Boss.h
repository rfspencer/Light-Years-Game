#pragma once

#include "Enemy/EnemySpaceship.h"
#include "weapon/BulletShooter.h"
#include "weapon/ThreeWayShooter.h"
#include "weapon/FrontWiper.h"

namespace ly
{
    class Boss : public EnemySpaceship
    {
    public:
        Boss(World* world);
        void Tick(float deltaTime) override;
        void BeginPlay() override;

    private:
        float mSpeed;
        float mSwitchDistanceToEdge;
        void CheckMove();

        BulletShooter mBaseShooterLeft;
        BulletShooter mBaseShooterRight;

        ThreeWayShooter mThreeWayShooter;
        FrontWiper mFrontalWiperLeft;
        FrontWiper mFrontalWiperRight;

        BulletShooter mFinalStageShooterLeft;
        BulletShooter mFinalStageShooterRight;

        void ShootBaseShooters();
        void ShootThreeWayShooter();
        void ShootFrontalWipers();
        void HealthChanged(float amount, float currentHealth, float maxHealth);

        void SetStage(int newStage);
        int mStage;
    };
}