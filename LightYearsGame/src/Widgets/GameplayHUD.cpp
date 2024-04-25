
#include "Widgets/GameplayHUD.h"


namespace ly
{

    GameplayHUD::GameplayHUD()
        : mFramerateText{"Frame rate: "},
          mPlayerHealthBar{}
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
        mPlayerHealthBar.NativeDraw(windowRef);
    }

    void GameplayHUD::Init(const sf::RenderWindow &windowRef)
    {
        auto windowSize = windowRef.getSize();
        mPlayerHealthBar.SetWidgetLocation(sf::Vector2f{20.f, windowSize.y - 50.f});
        mPlayerHealthBar.UpdateValue(100, 200.f);
    }
}