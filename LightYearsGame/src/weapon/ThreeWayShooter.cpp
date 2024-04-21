
#include "weapon/ThreeWayShooter.h"


namespace ly
{

    ThreeWayShooter::ThreeWayShooter(Actor *owner, float cooldownTime, const sf::Vector2f &localOffset)
        : Shooter(owner),
        mShooterLeft{owner, cooldownTime, localOffset + sf::Vector2f{10.f, -10.f}, -30.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"},
        mShooterMid{owner, cooldownTime, localOffset, 0.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"},
        mShooterRight{owner, cooldownTime, localOffset + sf::Vector2f{10.f, 10.f}, 30.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"}
    {

    }

    void ThreeWayShooter::ShootImplementation()
    {
        mShooterLeft.Shoot();
        mShooterMid.Shoot();
        mShooterRight.Shoot();
    }
}