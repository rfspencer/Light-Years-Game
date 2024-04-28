#pragma once

#include "spaceship/SpaceShip.h"
#include "weapon/Shooter.h"
#include "framework/TimerManager.h"

namespace ly
{

    class PlayerSpaceShip : public SpaceShip
    {
    public:
        PlayerSpaceShip(World* owningWorld, const std::string& texturePath = "SpaceShooterRedux/PNG/playerShip1_blue.png");

        void Tick(float deltaTime) override;
        void SetSpeed(float newSpeed) { mSpeed = newSpeed; }
        float GetSpeed() { return mSpeed; }

        void Shoot() override;
        void SetShooter(unique<Shooter>&& newShooter);
        void ApplyDamage(float amount) override;
        void BeginPlay() override;

    private:
        void HandleInput();
        void NormalizeInput();
        void ClampInputOnEdge();
        void ConsumeInput(float deltaTime);
        void StopInvulnerable();
        void UpdateInvulnerable(float deltaTime);
        sf::Vector2f mMoveInput;
        float mSpeed;

        unique<Shooter> mShooter;

        float mInvulnerableTime;
        TimerHandle mInvulnerableTimerHandle;
        bool mInvulnerable;

        float mInvulnerableFlashInterval;
        float mInvulnerableFlashTimer;
        float mInvulnerableFlashDuration;
    };
}