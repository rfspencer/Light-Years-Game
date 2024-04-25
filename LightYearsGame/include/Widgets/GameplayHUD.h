#pragma once

#include "widgets/HUD.h"
#include "widgets/TextWidget.h"

namespace ly
{
    class GameplayHUD : public HUD
    {
    public:
        GameplayHUD();

        void Tick(float deltaTime) override;
        void Draw(sf::RenderWindow &windowRef) override;

    private:
        TextWidget mFramerateText;

    };
}