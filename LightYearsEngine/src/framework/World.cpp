#include "framework/World.h"
#include "framework/Core.h"

namespace ly
{
    World::World(Application *owningApp)
        : mOwningApp{owningApp}, mBeganPlay{false}
    {

    }

    void World::BeginPlayInternal()
    {
        if (!mBeganPlay)
        {
            mBeganPlay = true;
            BeginPlay();
        }
    }

    void World::TickInternal(float deltaTime)
    {
        Tick(deltaTime);
    }

    World::~World()
    {

    }

    void World::BeginPlay()
    {
        LY_LOG("Begin play");
    }

    void World::Tick(float deltaTime)
    {
        LY_LOG("Tick at frame rate %f: ", 1.f / deltaTime);
    }
}