
#include "weapon/ThreeWayShooter.h"


namespace ly
{

    ThreeWayShooter::ThreeWayShooter(Actor *owner, float cooldownTime, const sf::Vector2f &localOffset)
        : Shooter(owner),
        mShooterLeft{owner, cooldownTime, localOffset + sf::Vector2f{10.f, -10.f}, -30.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"},
        mShooterMid{owner, cooldownTime, localOffset, 0.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"},
        mShooterRight{owner, cooldownTime, localOffset + sf::Vector2f{10.f, 10.f}, 30.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"},
        mTopShooterLeft{owner, cooldownTime, localOffset + sf::Vector2f{10.f, -10.f}, -15.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"},
        mTopShooterRight{owner, cooldownTime, localOffset + sf::Vector2f{10.f, 10.f}, 15.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"}
    {

    }

    void ThreeWayShooter::IncrementLevel(int amount)
    {
        Shooter::IncrementLevel(amount);

        mShooterLeft.IncrementLevel(amount);
        mShooterMid.IncrementLevel(amount);
        mShooterRight.IncrementLevel(amount);

        mTopShooterLeft.IncrementLevel(amount);
        mTopShooterRight.IncrementLevel(amount);
    }

    void ThreeWayShooter::ShootImplementation()
    {
        mShooterLeft.Shoot();
        mShooterMid.Shoot();
        mShooterRight.Shoot();

        if (GetCurrentLevel() == GetMaxLevel())
        {
            mTopShooterLeft.Shoot();
            mTopShooterRight.Shoot();
        }
    }
}