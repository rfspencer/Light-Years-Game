#include "framework/Object.h"
#include "framework/Core.h"

namespace ly
{
    ly::Object::Object()
        : mIsPendingDestroy{false}
    {
    }

    Object::~Object()
    {
        LY_LOG("ObjectD Destroyed");
    }

    void Object::Destroy()
    {
        mIsPendingDestroy = true;
    }
}
