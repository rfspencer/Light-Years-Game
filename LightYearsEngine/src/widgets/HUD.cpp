#include "widgets/HUD.h"


namespace ly
{

    HUD::HUD()
        : mAlreadyInit{false}
    {

    }

    void HUD::NativeInit(const sf::RenderWindow &windowRef)
    {
        if (!mAlreadyInit)
        {
            mAlreadyInit = true;
            Init(windowRef);
        }
    }

    void HUD::Init(const sf::RenderWindow &windowRef)
    {

    }

    bool HUD::HandleEvent(const sf::Event &event)
    {
        return false;
    }
}