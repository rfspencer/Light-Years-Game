#include "player/PlayerSpaceShip.h"
#include "SFML/System.hpp"
#include "framework/MathUtility.h"
#include "weapon/BulletShooter.h"
#include "weapon/ThreeWayShooter.h"
#include "weapon/FrontWiper.h"

namespace ly
{

    PlayerSpaceShip::PlayerSpaceShip(World *owningWorld, const std::string &texturePath)
        : SpaceShip(owningWorld, texturePath),
        mMoveInput{},
        mSpeed{200.f},
        mShooter{new BulletShooter{this, 0.1f, {50.f, 0.f}}},
        mInvulnerableTime{2.f},
        mInvulnerable{true},
        mInvulnerableFlashInterval{0.5f},
        mInvulnerableFlashTimer{0.f},
        mInvulnerableFlashDuration{1.f}
    {
        SetTeamID(1);
    }

    void PlayerSpaceShip::Tick(float deltaTime)
    {
        SpaceShip::Tick(deltaTime);

        HandleInput();
        ConsumeInput(deltaTime);
        UpdateInvulnerable(deltaTime);
    }

    void PlayerSpaceShip::HandleInput()
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            mMoveInput.y = -1.f;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            mMoveInput.y = 1.f;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            mMoveInput.x = -1.f;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            mMoveInput.x = 1.f;
        }

        ClampInputOnEdge();
        NormalizeInput();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            Shoot();
        }
    }

    void PlayerSpaceShip::ConsumeInput(float deltaTime)
    {
        SetVelocity(mMoveInput * mSpeed);
        mMoveInput.x = mMoveInput.y = 0.f;
    }

    void PlayerSpaceShip::NormalizeInput()
    {
        Normalize(mMoveInput);
    }

    void PlayerSpaceShip::ClampInputOnEdge()
    {
        sf::Vector2f actorLocation = GetActorLocation();
        if(actorLocation.x < 0 && mMoveInput.x == -1.f)
        {
            mMoveInput.x = 0.f;
        }
        if(actorLocation.x > GetWindowSize().x && mMoveInput.x == 1.f)
        {
            mMoveInput.x = 0.f;
        }
        if(actorLocation.y < 0 && mMoveInput.y == -1.f)
        {
            mMoveInput.y = 0.f;
        }
        if(actorLocation.y > GetWindowSize().y && mMoveInput.y == 1.f)
        {
            mMoveInput.y = 0.f;
        }
    }

    void PlayerSpaceShip::Shoot()
    {
        if (mShooter)
        {
            mShooter->Shoot();
        }
    }

    void PlayerSpaceShip::SetShooter(unique<Shooter> &&newShooter)
    {
        if(mShooter && typeid(*mShooter.get()) == typeid(*newShooter.get()))
        {
            mShooter->IncrementLevel();
            return;
        }
        mShooter = std::move(newShooter);
    }

    void PlayerSpaceShip::ApplyDamage(float amount)
    {
        if (!mInvulnerable)
        {
            SpaceShip::ApplyDamage(amount);
        }
    }

    void PlayerSpaceShip::BeginPlay()
    {
        SpaceShip::BeginPlay();

        TimerManager::Get().SetTimer(GetWeakRef(), &PlayerSpaceShip::StopInvulnerable, mInvulnerableTime);
    }

    void PlayerSpaceShip::StopInvulnerable()
    {
        GetSprite().setColor({255,255,255,255});
        mInvulnerable = false;
    }

    void PlayerSpaceShip::UpdateInvulnerable(float deltaTime)
    {
        if (!mInvulnerable) return;

        mInvulnerableFlashTimer += deltaTime * mInvulnerableFlashDuration;
        if (mInvulnerableFlashTimer < 0 || mInvulnerableFlashTimer > mInvulnerableFlashInterval)
        {
            mInvulnerableFlashDuration *= -1;
        }

        GetSprite().setColor(LerpColor({255, 255, 255, 64}, {255, 255, 255, 128}, mInvulnerableFlashTimer / mInvulnerableFlashInterval));
    }
}