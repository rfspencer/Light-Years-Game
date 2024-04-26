
#include "Widgets/GameplayHUD.h"
#include "player/PlayerManager.h"
#include "player/PlayerSpaceShip.h"
#include "player/Player.h"


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
    }

    void GameplayHUD::PlayerSpaceshipDestroyed(Actor *actor)
    {
        RefreshHealthBar();
    }
}