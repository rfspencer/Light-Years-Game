#pragma once

#include "framework/Core.h"
#include "Object.h"

namespace ly
{
    class TimerManager
    {
    public:
        static TimerManager& Get();

        template<typename ClassName>
        void SetTimer(weak<Object> waekRef, void(ClassName::*callback)(), float duration, bool repeat = false)
        {

        }

    protected:
        TimerManager();

    private:
        static unique<TimerManager> timerManager;

    };
}