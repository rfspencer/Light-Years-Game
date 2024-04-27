#pragma once

#include "widgets/HUD.h"
#include "widgets/TextWidget.h"
#include "widgets/ValueGauge.h"
#include "widgets/ImageWidget.h"

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
        void ConnectPlayerLifeCount();
        void PlayerLifeCountUpdated(int amount);
        void PlayerSpaceshipDestroyed(Actor* actor);

        TextWidget mFramerateText;
        ValueGauge mPlayerHealthBar;
        ImageWidget mPlayerLifeIcon;
        TextWidget mPlayerLifeText;

        sf::Color mHealthBarColor;
        sf::Color mCriticalBarColor;
        float mCriticalThreshold;

        float mWidgetSpacing;
    };
}