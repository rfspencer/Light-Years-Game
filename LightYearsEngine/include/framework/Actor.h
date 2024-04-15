#pragma once

#include <SFML/Graphics.hpp>

#include "framework/Object.h"
#include "framework/Core.h"

class b2Body;

namespace ly
{
    class World;

    class Actor : public Object
    {
    public:
        Actor(World* owningWorld, const std::string& texturePath = "");
        virtual ~Actor();

        void BeginPlayInternal();
        void TickInternal(float deltaTime);
        virtual void BeginPlay();
        virtual void Tick(float deltaTime);

        virtual void SetTexture(const std::string& texturePath);
        void Render(sf::RenderWindow& window);

        void SetActorLocation(const sf::Vector2f& newLocation);
        void SetActorRotation(float newRotation);
        void AddActorLocationOffset(const sf::Vector2f& offsetAmount);
        void AddActorRotationOffset(float offsetAmount);

        sf::Vector2f GetActorLocation() const;
        float GetActorRotation() const;
        sf::Vector2f GetActorForwardDirection() const;
        sf::Vector2f GetActorRightDirection() const;
        sf::FloatRect GetActorGlobalBounds() const;

        sf::Vector2u GetWindowSize() const;

        const World* GetWorld() const { return mOwningWorld; }
        World* GetWorld() { return mOwningWorld; }

        bool IsActorOutOfWindowBounds(float allowance = 10.f) const;

        void SetEnablePhysics(bool enable);
        virtual void OnActorBeginOverlap(Actor* otherActor);
        virtual void OnActorEndOverlap(Actor* otherActor);
        virtual void Destroy() override;

        static uint8 GetNeutralTeamID() { return neutralTeamID; }

        void SetTeamID(uint8 teamID) { mTeamID = teamID; }
        uint8 GetTeamID() const { return mTeamID; }
        bool IsOtherHostile(Actor* other) const;

        virtual void ApplyDamage(float amount);

        sf::Sprite& GetSprite() { return mSprite; }
        const sf::Sprite& GetSprite() const { return mSprite; }

    private:
        void InitializePhysics();
        void UnInitializePhysics();
        void UpdatePhysicsBodyTransform();

        World* mOwningWorld;
        void CenterPivot();

        bool mHasBeganPlay;

        sf::Sprite mSprite;
        shared<sf::Texture> mTexture;

        b2Body* mPhysicsBody;
        bool mPhysicsEnabled;

        uint8 mTeamID;

        const static uint8 neutralTeamID = 255;
    };
}