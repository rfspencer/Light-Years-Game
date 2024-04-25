#pragma once

#include "widgets/HUD.h"
#include "widgets/TextWidget.h"
#include "widgets/ValueGauge.h"

namespace ly
{
    class GameplayHUD : public HUD
    {
    public:
        GameplayHUD();

        void Tick(float deltaTime) override;
        void Draw(sf::RenderWindow &windowRef) override;

    private:
        void Init(const sf::RenderWindow &windowRef) override;

        TextWidget mFramerateText;
        ValueGauge mPlayerHealthBar;
    };
}