
#include "Widgets/GameplayHUD.h"
#include "player/PlayerManager.h"
#include "player/PlayerSpaceShip.h"
#include "player/Player.h"


namespace ly
{

    GameplayHUD::GameplayHUD()
        : mFramerateText{"Frame rate: "},
          mPlayerHealthBar{},
          mHealthBarColor{128, 255, 128, 255},
          mCriticalBarColor{255, 0 ,0, 255},
          mCriticalThreshold{0.3},
          mPlayerLifeIcon{"SpaceShooterRedux/PNG/pickups/playerLife1_blue.png"},
          mWidgetSpacing{10.f}
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
        mPlayerLifeIcon.NativeDraw(windowRef);
    }

    void GameplayHUD::Init(const sf::RenderWindow &windowRef)
    {
        auto windowSize = windowRef.getSize();
        mPlayerHealthBar.SetWidgetLocation(sf::Vector2f{20.f, windowSize.y - 50.f});
        sf::Vector2f lifeIconPos = mPlayerHealthBar.GetWidgetLocation();
        lifeIconPos += sf::Vector2f{mPlayerHealthBar.GetBound().width + mWidgetSpacing, 0.f};
        mPlayerLifeIcon.SetWidgetLocation(lifeIconPos);

        RefreshHealthBar();
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
            mPlayerHealthBar.UpdateValue(healthComponent.GetHealth(), healthComponent.GetMaxHealth());
        }
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

    void GameplayHUD::PlayerSpaceshipDestroyed(Actor *actor)
    {
        RefreshHealthBar();
    }
}