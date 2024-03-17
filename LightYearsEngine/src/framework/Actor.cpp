#include "framework/Actor.h"
#include "framework/Core.h"

namespace ly
{
    Actor::Actor(ly::World *owningWorld)
        : mOwningWorld{owningWorld},
        mHasBeganPlay{false}
    {

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

    void Actor::BeginPlay()
    {
        LY_LOG("Actor begin play.");
    }

    void Actor::Tick(float deltaTime)
    {
        LY_LOG("Actor ticking...");
    }
}