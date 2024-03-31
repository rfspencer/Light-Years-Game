#include "framework/Actor.h"
#include "framework/Core.h"
#include "framework/AssetManager.h"
#include "framework/MathUtility.h"
#include "framework/World.h"

namespace ly
{
    Actor::Actor(ly::World *owningWorld, const std::string& texturePath)
        : mOwningWorld{owningWorld},
        mHasBeganPlay{false},
        mSprite{},
        mTexture{}
    {
        SetTexture(texturePath);
    }

    Actor::~Actor()
    {
        LY_LOG("Actor destroyed");
    }

    void Actor::BeginPlayInternal()
    {
        if(!mHasBeganPlay)
        {
            mHasBeganPlay = true;
            BeginPlay();
        }
    }

    void Actor::TickInternal(float deltaTime)
    {
        if (!IsPendingDestroy())
        {
            Tick(deltaTime);
        }
    }

    void Actor::BeginPlay()
    {
    }

    void Actor::Tick(float deltaTime)
    {
    }

    void Actor::SetTexture(const std::string &texturePath)
    {
        mTexture = AssetManager::Get().LoadTexture(texturePath);
        if(!mTexture)
        {
            return;
        }

        mSprite.setTexture(*mTexture);

        int textureWidth = mTexture->getSize().x;
        int textureHeight = mTexture->getSize().y;
        mSprite.setTextureRect(sf::IntRect(sf::Vector2i{}, sf::Vector2i{textureWidth, textureHeight}));
        CenterPivot();
    }

    void Actor::Render(sf::RenderWindow &window)
    {
        if (IsPendingDestroy())
        {
            return;
        }
        window.draw(mSprite);
    }

    void Actor::SetActorLocation(const sf::Vector2f &newLocation)
    {
        mSprite.setPosition(newLocation);
    }

    void Actor::SetActorRotation(float newRotation)
    {
        mSprite.setRotation(newRotation);
    }

    void Actor::AddActorLocationOffset(const sf::Vector2f &offsetAmount)
    {
        SetActorLocation(GetActorLocation() + offsetAmount);
    }

    void Actor::AddActorRotationOffset(float offsetAmount)
    {
        SetActorRotation(GetActorRotation() + offsetAmount);
    }

    sf::Vector2f Actor::GetActorLocation() const
    {
        return mSprite.getPosition();
    }

    float Actor::GetActorRotation() const
    {
        return mSprite.getRotation();
    }

    sf::Vector2f Actor::GetActorForwardDirection() const
    {
        return RotationToVector(GetActorRotation() - 90.f);
    }

    sf::Vector2f Actor::GetActorRightDirection() const
    {
        return RotationToVector(GetActorRotation());
    }

    sf::FloatRect Actor::GetActorGlobalBounds() const
    {
        return mSprite.getGlobalBounds();
    }

    sf::Vector2u Actor::GetWindowSize() const
    {
        return mOwningWorld->GetWindowSize();
    }

    void Actor::CenterPivot()
    {
        sf::FloatRect bound = mSprite.getGlobalBounds();
        mSprite.setOrigin(bound.width / 2.f, bound.height / 2.f);
    }

    bool Actor::IsActorOutOfWindowBounds() const
    {
        float windowWidth = GetWorld()->GetWindowSize().x;
        float windowHeight = GetWorld()->GetWindowSize().y;

        float width = GetActorGlobalBounds().width;
        float height = GetActorGlobalBounds().height;

        sf::Vector2f actorPos = GetActorLocation();

        if (actorPos.x < -width)
        {
            return true;
        }
        if (actorPos.x > windowWidth + width)
        {
            return true;
        }
        if (actorPos.y < -height)
        {
            return true;
        }
        if (actorPos.y > windowHeight + height)
        {
            return true;
        }
        return false;
    }
}