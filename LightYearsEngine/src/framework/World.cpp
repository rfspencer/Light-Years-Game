#include "framework/World.h"
#include "framework/Actor.h"
#include "framework/Core.h"

namespace ly
{
    World::World(Application *owningApp)
        : mOwningApp{owningApp},
        mBeganPlay{false},
        mActors{},
        mPendingActors{}
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
        for(shared<Actor> actor : mPendingActors)
        {
            mActors.push_back(actor);
            actor->BeginPlayInternal();
        }
        mPendingActors.clear();

        for (auto iter = mActors.begin(); iter != mActors.end();)
        {
            if (iter->get()->IsPendingDestroy())
            {
                iter = mActors.erase(iter);
            }
            else
            {
                iter->get()->Tick(deltaTime);
                ++iter;
            }
        }

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