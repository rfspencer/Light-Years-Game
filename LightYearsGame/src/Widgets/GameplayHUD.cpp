
#include "Widgets/GameplayHUD.h"


namespace ly
{

    GameplayHUD::GameplayHUD()
        : mFramerateText{"Frame rate: "}
    {
        mFramerateText.SetTextSize(15);
    }

    void GameplayHUD::Tick(float deltaTime)
    {
        HUD::Tick(deltaTime);

        int frameRate = int(1 / deltaTime);
        std::string frameRateStr = "Frame Rate: " + std::to_string(frameRate);
        mFramerateText.SetString(frameRateStr);
    }

    void GameplayHUD::Draw(sf::RenderWindow &windowRef)
    {
        mFramerateText.NativeDraw(windowRef);
    }
}