#pragma once

#include "framework/Object.h"
#include "framework/Delegate.h"

namespace ly
{
    class PlayerSpaceShip;
    class World;

    class Player : public Object
    {
    public:
        Player();

        weak<PlayerSpaceShip> SpawnSpaceShip(World* world);
        weak<PlayerSpaceShip> GetCurrentSpaceShip() const { return mCurrentPlayerSpaceShip; }

        void AddLifeCount(unsigned int count);
        int GetLifeCount() const { return mLifeCount; }

        void AddScore(unsigned int amount);
        int GetScore() const { return mScore; }

        Delegate<int> onLifeChanged;
        Delegate<int> onScoreChange;
        Delegate<> onLifeExhausted;

    private:
        unsigned int mLifeCount;
        unsigned int mScore;
        weak<PlayerSpaceShip> mCurrentPlayerSpaceShip;
    };
}