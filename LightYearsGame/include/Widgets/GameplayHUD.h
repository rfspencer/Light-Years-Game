#pragma once

#include "widgets/HUD.h"
#include "widgets/TextWidget.h"
#include "widgets/ValueGauge.h"
#include "widgets/ImageWidget.h"
#include "widgets/Button.h"

namespace ly
{
    class Actor;

    class GameplayHUD : public HUD
    {
    public:
        GameplayHUD();

        void Tick(float deltaTime) override;
        void Draw(sf::RenderWindow &windowRef) override;
        bool HandleEvent(const sf::Event &event) override;
        void GameFinished(bool playerWon);

        Delegate<> onRestartButtonClicked;
        Delegate<> onQuitButtonClicked;

    private:
        void Init(const sf::RenderWindow &windowRef) override;
        void PlayerHealthUpdated(float amount, float currentHealth, float maxHealth);
        void RefreshHealthBar();
        void ConnectPlayerStatus();
        void PlayerLifeCountUpdated(int amount);
        void PlayerScoreUpdated(int newScore);
        void PlayerSpaceshipDestroyed(Actor* actor);

        void RestartButtonClicked();
        void QuitButtonClicked();

        TextWidget mFramerateText;
        ValueGauge mPlayerHealthBar;
        ImageWidget mPlayerLifeIcon;
        TextWidget mPlayerLifeText;
        ImageWidget mPlayerScoreIcon;
        TextWidget mPlayerScoreText;

        sf::Color mHealthBarColor;
        sf::Color mCriticalBarColor;
        float mCriticalThreshold;

        float mWidgetSpacing;

        TextWidget mWinLoseText;
        TextWidget mFinalScoreText;
        Button mRestartButton;
        Button mQuitButton;
    };
}