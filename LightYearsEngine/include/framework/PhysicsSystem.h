#pragma once

#include "framework/Core.h"
#include "box2d/b2_world.h"

namespace ly
{
    class Actor;
    class PhysicsContactListener : public b2ContactListener
    {
        void BeginContact(b2Contact* contact) override;
        void EndContact(b2Contact* contact) override;
    };

    class PhysicsSystem
    {
    public:
        static PhysicsSystem& Get();
        void Step(float deltaTime);
        b2Body* AddListener(Actor* listener);
        void RemoveListener(b2Body* bodyToRemove);

        float GetPhysicsScale() { return mPhysicsScale; }

    protected:
        PhysicsSystem();

    private:
        static unique<PhysicsSystem> physicsSystem;
        b2World mPhysicsWorld;
        float mPhysicsScale;
        int mVelocityIterations;
        int mPositionIterations;

        PhysicsContactListener mContactListener;
    };
}