
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
          mWidgetSpacing{10.f}
    {
        mFramerateText.SetTextSize(15);
        mPlayerLifeText.SetTextSize(20);
        mPlayerScoreText.SetTextSize(20);
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
        mPlayerLifeIcon.NativeDraw(windowRef);
        mPlayerLifeText.NativeDraw(windowRef);
        mPlayerScoreIcon.NativeDraw(windowRef);
        mPlayerScoreText.NativeDraw(windowRef);
    }

    void GameplayHUD::Init(const sf::RenderWindow &windowRef)
    {
        auto windowSize = windowRef.getSize();
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
}