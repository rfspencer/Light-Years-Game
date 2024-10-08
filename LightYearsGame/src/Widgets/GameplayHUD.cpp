
#include "Widgets/GameplayHUD.h"
#include "player/PlayerManager.h"
#include "player/PlayerSpaceShip.h"
#include "player/Player.h"


namespace ly
{

    GameplayHUD::GameplayHUD()
        : mFramerateText{"Frame rate: "},
          mPlayerHealthBar{},
          mPlayerLifeIcon{"SpaceShooterRedux/PNG/pickups/playerLife1_blue.png"},
          mPlayerLifeText{""},
          mPlayerScoreIcon{"SpaceShooterRedux/PNG/Power-ups/star_gold.png"},
          mPlayerScoreText{""},
          mHealthBarColor{128, 255, 128, 255},
          mCriticalBarColor{255, 0 ,0, 255},
          mCriticalThreshold{0.3},
          mWidgetSpacing{10.f},
          mWinLoseText{""},
          mFinalScoreText{""},
          mRestartButton{"Restart"},
          mQuitButton{"Quit"},
          mWindowSize{}
    {
        mFramerateText.SetTextSize(15);
        mPlayerLifeText.SetTextSize(20);
        mPlayerScoreText.SetTextSize(20);

        mWinLoseText.SetVisibility(false);
        mFinalScoreText.SetVisibility(false);
        mRestartButton.SetVisibility(false);
        mQuitButton.SetVisibility(false);
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
        mWindowSize = windowRef.getSize();
        mFramerateText.NativeDraw(windowRef);
        mPlayerHealthBar.NativeDraw(windowRef);
        mPlayerLifeIcon.NativeDraw(windowRef);
        mPlayerLifeText.NativeDraw(windowRef);
        mPlayerScoreIcon.NativeDraw(windowRef);
        mPlayerScoreText.NativeDraw(windowRef);

        mWinLoseText.NativeDraw(windowRef);
        mFinalScoreText.NativeDraw(windowRef);
        mRestartButton.NativeDraw(windowRef);
        mQuitButton.NativeDraw(windowRef);
    }

    bool GameplayHUD::HandleEvent(const sf::Event &event)
    {
        if (mRestartButton.HandleEvent(event)) return true;
        if (mQuitButton.HandleEvent(event)) return true;

        return HUD::HandleEvent(event);
    }

    void GameplayHUD::Init(const sf::RenderWindow &windowRef)
    {
        auto windowSize = windowRef.getSize();
        mWindowSize = windowSize;
        mPlayerHealthBar.SetWidgetLocation(sf::Vector2f{20.f, windowSize.y - 50.f});

        sf::Vector2f nextWidgetPosition = mPlayerHealthBar.GetWidgetLocation();

        nextWidgetPosition += sf::Vector2f{mPlayerHealthBar.GetBound().width + mWidgetSpacing, 0.f};
        mPlayerLifeIcon.SetWidgetLocation(nextWidgetPosition);

        nextWidgetPosition += sf::Vector2f{mPlayerLifeIcon.GetBound().width + mWidgetSpacing, 0.f};
        mPlayerLifeText.SetWidgetLocation(nextWidgetPosition);

        nextWidgetPosition += sf::Vector2f{mPlayerLifeText.GetBound().width + mWidgetSpacing * 4, -2.f};
        mPlayerScoreIcon.SetWidgetLocation(nextWidgetPosition);

        nextWidgetPosition += sf::Vector2f{mPlayerScoreIcon.GetBound().width + mWidgetSpacing, 0.f};
        mPlayerScoreText.SetWidgetLocation(nextWidgetPosition);

        RefreshHealthBar();
        ConnectPlayerStatus();

        mWinLoseText.SetTextSize(40);
        mWinLoseText.SetWidgetLocation({(windowSize.x / 2.f) - (mWinLoseText.GetBound().width / 2.f), 100.f});

        mFinalScoreText.SetTextSize(30);
        mFinalScoreText.SetWidgetLocation({(windowSize.x / 2.f) - (mFinalScoreText.GetBound().width / 2.f), 200.f});

        mRestartButton.SetWidgetLocation({(windowSize.x / 2.f) - (mRestartButton.GetBound().width / 2.f), windowSize.y / 2.f});
        mQuitButton.SetWidgetLocation(mRestartButton.GetWidgetLocation() + sf::Vector2f{0.f, 50.f});

        mRestartButton.onButtonClicked.BindAction(GetWeakRef(), &GameplayHUD::RestartButtonClicked);
        mQuitButton.onButtonClicked.BindAction(GetWeakRef(), &GameplayHUD::QuitButtonClicked);
    }

    void GameplayHUD::RefreshHealthBar()
    {
        Player *player = PlayerManager::Get().GetPlayer();
        if (player && !player->GetCurrentSpaceShip().expired())
        {
            weak<PlayerSpaceShip> playerSpaceShip = player->GetCurrentSpaceShip();
            playerSpaceShip.lock()->onActorDestroyed.BindAction(GetWeakRef(), &GameplayHUD::PlayerSpaceshipDestroyed);
            HealthComponent& healthComponent = player->GetCurrentSpaceShip().lock()->GetHealthComp();
            healthComponent.onHealthChanged.BindAction(GetWeakRef(), &GameplayHUD::PlayerHealthUpdated);
            PlayerHealthUpdated(0, healthComponent.GetHealth(), healthComponent.GetMaxHealth());
        }
    }

    void GameplayHUD::ConnectPlayerStatus()
    {
        Player* player = PlayerManager::Get().GetPlayer();
        if (player)
        {
            int lifeCount = player->GetLifeCount();
            mPlayerLifeText.SetString(std::to_string(lifeCount));
            player->onLifeChanged.BindAction(GetWeakRef(), &GameplayHUD::PlayerLifeCountUpdated);

            int playerScore = player->GetScore();
            mPlayerScoreText.SetString(std::to_string(playerScore));
            player->onScoreChange.BindAction(GetWeakRef(), &GameplayHUD::PlayerScoreUpdated);
        }
    }

    void GameplayHUD::PlayerLifeCountUpdated(int amount)
    {
        mPlayerLifeText.SetString(std::to_string(amount));
    }

    void GameplayHUD::PlayerHealthUpdated(float amount, float currentHealth, float maxHealth)
    {
        mPlayerHealthBar.UpdateValue(currentHealth, maxHealth);
        if(currentHealth / maxHealth <= mCriticalThreshold)
        {
            mPlayerHealthBar.SetForegroundColor(mCriticalBarColor);
        }
        else
        {
            mPlayerHealthBar.SetForegroundColor(mHealthBarColor);
        }
    }

    void GameplayHUD::PlayerScoreUpdated(int newScore)
    {
        mPlayerScoreText.SetString(std::to_string(newScore));
    }

    void GameplayHUD::PlayerSpaceshipDestroyed(Actor *actor)
    {
        RefreshHealthBar();
    }

    void GameplayHUD::GameFinished(bool playerWon)
    {
        mWinLoseText.SetVisibility(true);
        mFinalScoreText.SetVisibility(true);
        mRestartButton.SetVisibility(true);
        mQuitButton.SetVisibility(true);

        int score = PlayerManager::Get().GetPlayer()->GetScore();
        mFinalScoreText.SetString("Score: " + std::to_string(score));
        mFinalScoreText.SetTextSize(30);

        if (playerWon)
        {
            mWinLoseText.SetString("You Win!");
        }
        else
        {
            mWinLoseText.SetString("You Lose!");
        }
        mWinLoseText.SetWidgetLocation({(mWindowSize.x / 2.f) - (mWinLoseText.GetBound().width / 2.f), 100.f});
        mFinalScoreText.SetWidgetLocation({(mWindowSize.x / 2.f) - (mFinalScoreText.GetBound().width / 2.f), 200.f});
    }

    void GameplayHUD::RestartButtonClicked()
    {
        onRestartButtonClicked.Broadcast();
    }

    void GameplayHUD::QuitButtonClicked()
    {
        onQuitButtonClicked.Broadcast();
    }
}