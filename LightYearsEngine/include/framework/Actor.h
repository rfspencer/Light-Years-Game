#pragma once

#include <SFML/Graphics.hpp>

#include "framework/Object.h"
#include "framework/Core.h"

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

        World* GetWorld() const { return mOwningWorld; }

        bool IsActorOutOfWindowBounds() const;

    private:
        World* mOwningWorld;
        void CenterPivot();

        bool mHasBeganPlay;

        sf::Sprite mSprite;
        shared<sf::Texture> mTexture;
    };
}