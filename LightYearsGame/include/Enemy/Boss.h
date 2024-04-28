#pragma once

#include "Enemy/EnemySpaceship.h"

namespace ly
{
    class Boss : public EnemySpaceship
    {
    public:
        Boss(World* world);
        void Tick(float deltaTime) override;

    private:
        float mSpeed;
        float mSwitchDistanceToEdge;
    };
}