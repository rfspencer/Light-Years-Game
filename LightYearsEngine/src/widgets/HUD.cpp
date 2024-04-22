#include "widgets/HUD.h"


namespace ly
{

    HUD::HUD()
        : mAlreadyInit{false}
    {

    }

    void HUD::NativeInit(sf::RenderWindow &windowRef)
    {
        if (!mAlreadyInit)
        {
            mAlreadyInit = true;
            Init(windowRef);
        }
    }

    void HUD::Init(sf::RenderWindow &windowRef)
    {

    }

    bool HUD::HandleEvent(const sf::Event &event)
    {
        return false;
    }
}