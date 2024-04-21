#pragma once

#include "spaceship/SpaceShip.h"
#include "weapon/Shooter.h"

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

    private:
        void HandleInput();
        void NormalizeInput();
        void ClampInputOnEdge();
        void ConsumeInput(float deltaTime);
        sf::Vector2f mMoveInput;
        float mSpeed;

        unique<Shooter> mShooter;
    };
}