#include "weapon/Bullet.h"


namespace ly
{
    Bullet::Bullet(ly::World *world, ly::Actor *owner, const std::string &texturePath, float speed, float damage)
        : Actor{world, texturePath},
        mOwner{owner},
        mSpeed{speed},
        mDamage{damage}
    {

    }

    void Bullet::Tick(float deltaTime)
    {
        Actor::Tick(deltaTime);
        Move(deltaTime);
        if (IsActorOutOfWindowBounds())
        {
            Destroy();
        }
    }

    void Bullet::SetSpeed(float newSpeed)
    {
        mSpeed = newSpeed;
    }

    void Bullet::SetDamage(float newDamage)
    {
        mDamage = newDamage;
    }

    void Bullet::Move(float deltaTime)
    {
        sf::Vector2<float> testRot = GetActorForwardDirection();
        AddActorLocationOffset(GetActorForwardDirection() * mSpeed * deltaTime);
    }

}