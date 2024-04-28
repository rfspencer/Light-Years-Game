
#include "weapon/FrontWiper.h"


namespace ly
{

    FrontWiper::FrontWiper(Actor *ownerActor, float cooldownTime, const sf::Vector2f &localOffset, float width)
        : Shooter{ownerActor},
        mWidth{width},
        mShooter1{ownerActor, cooldownTime, {localOffset.x, localOffset.y - width / 2.f}, 0.f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png"},
        mShooter2{ownerActor, cooldownTime, {localOffset.x, localOffset.y - width / 6.f}, 0.f, "SpaceShooterRedux/PNG/Lasers/laserBlue07.png"},
        mShooter3{ownerActor, cooldownTime, {localOffset.x, localOffset.y + width / 6.f}, 0.f, "SpaceShooterRedux/PNG/Lasers/laserBlue07.png"},
        mShooter4{ownerActor, cooldownTime, {localOffset.x, localOffset.y + width / 2.f}, 0.f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png"},
        mShooter5{ownerActor, 0.1, {localOffset.x, localOffset.y + width / 1.5f}, 15.f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png"},
        mShooter6{ownerActor, 0.1, {localOffset.x, localOffset.y - width / 1.5f}, -15.f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png"}
    {

    }

    void FrontWiper::IncrementLevel(int amount)
    {
        Shooter::IncrementLevel(amount);

        mShooter1.IncrementLevel(amount);
        mShooter2.IncrementLevel(amount);
        mShooter3.IncrementLevel(amount);
        mShooter4.IncrementLevel(amount);

        mShooter5.IncrementLevel(amount);
        mShooter6.IncrementLevel(amount);
    }

    void FrontWiper::SetCurrentLevel(int newLevel)
    {
        Shooter::SetCurrentLevel(newLevel);

        mShooter1.SetCurrentLevel(newLevel);
        mShooter2.SetCurrentLevel(newLevel);
        mShooter3.SetCurrentLevel(newLevel);
        mShooter4.SetCurrentLevel(newLevel);

        mShooter5.SetCurrentLevel(newLevel);
        mShooter6.SetCurrentLevel(newLevel);
    }

    void FrontWiper::ShootImplementation()
    {
        mShooter1.Shoot();
        mShooter2.Shoot();
        mShooter3.Shoot();
        mShooter4.Shoot();

        if (GetCurrentLevel() == GetMaxLevel())
        {
            mShooter5.Shoot();
            mShooter6.Shoot();
        }
    }
}