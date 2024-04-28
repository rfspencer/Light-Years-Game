#include "weapon/Shooter.h"

namespace ly
{
    Shooter::Shooter(Actor *owner)
        : mOwner{owner},
        mCurrentLevel{1},
        mMaxLevel{4}
    {

    }

    void Shooter::Shoot()
    {
        if (CanShoot() && !IsOnCooldown())
        {
            ShootImplementation();
        }
    }

    void Shooter::IncrementLevel(int amount)
    {
        if (mCurrentLevel == mMaxLevel) return;
        ++mCurrentLevel;
    }

    void Shooter::SetCurrentLevel(int newLevel)
    {
        mCurrentLevel = newLevel;
    }


}