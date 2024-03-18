#pragma once
#include <string>

std::string GetResourceDir()
{
#ifdef NDEBUG // Release build
    return "assets/";
#else
    return "D:/git/Cpp-Game-from-Scratch/LightYearsGame/assets/";
#endif
}
