#pragma once
#include <string>

std::string GetResourceDir()
{
#ifdef NDEBUG // Release build
    return "assets/";
#else
    return "D:/git/Light-Years-Game/LightYearsGame/assets/";
#endif
}
