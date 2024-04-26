#pragma once

#include "widgets/HUD.h"
#include "widgets/TextWidget.h"
#include "widgets/ValueGauge.h"

namespace ly
{
    class Actor;

    class GameplayHUD : public HUD
    {
    public:
        GameplayHUD();

        void Tick(float deltaTime) override;
        void Draw(sf::RenderWindow &windowRef) override;

    private:
        void Init(const sf::RenderWindow &windowRef) override;
        void PlayerHealthUpdated(float amount, float currentHealth, float maxHealth);
        void RefreshHealthBar();
        void PlayerSpaceshipDestroyed(Actor* actor);

        TextWidget mFramerateText;
        ValueGauge mPlayerHealthBar;

        sf::Color mHealthBarColor;
        sf::Color mCriticalBarColor;
        float mCriticalThreshold;
    };
}