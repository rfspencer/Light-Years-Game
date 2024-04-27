#include "framework/Object.h"
#include "framework/Core.h"

namespace ly
{
    unsigned int Object::uniqueIDCounter = 0;
    ly::Object::Object()
        : mIsPendingDestroy{false},
        mUniqueID{GetNextAvailableID()}
    {
    }

    Object::~Object()
    {
        LY_LOG("ObjectD Destroyed");
    }

    void Object::Destroy()
    {
        onDestroy.Broadcast(this);
        mIsPendingDestroy = true;
    }

    weak<Object> Object::GetWeakRef()
    {
        return weak_from_this();
    }

    weak<const Object> Object::GetWeakRef() const
    {
        return weak_from_this();
    }

    unsigned int Object::GetNextAvailableID()
    {
        return uniqueIDCounter++;
    }
}
