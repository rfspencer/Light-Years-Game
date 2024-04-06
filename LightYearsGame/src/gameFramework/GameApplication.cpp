#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include "framework/AssetManager.h"
#include "player/PlayerSpaceShip.h"
#include "config.h"

ly::Application* GetApplication()
{
    return new ly::GameApplication{};
}

namespace ly
{
    GameApplication::GameApplication()
        : Application(600, 980, "Light Years", sf::Style::Titlebar | sf::Style::Close)
    {
        AssetManager::Get().SetAssetRootDirectory(GetResourceDir());
        weak<World> newWorld = LoadWorld<World>();
        testPlayerSpaceship = newWorld.lock()->SpawnActor<PlayerSpaceShip>();
        testPlayerSpaceship.lock()->SetActorLocation(sf::Vector2f(300.f, 490.f));
        testPlayerSpaceship.lock()->SetActorRotation(0.f);

        weak<SpaceShip> testSpaceShip = newWorld.lock()->SpawnActor<SpaceShip>();
        testSpaceShip.lock()->SetTexture("SpaceShooterRedux/PNG/playerShip1_blue.png");
        testSpaceShip.lock()->SetActorLocation(sf::Vector2f {100.f, 50.f});
        testSpaceShip.lock()->SetTeamID(2);
        counter = 0.f;
    }

    void GameApplication::Tick(float deltaTime)
    {
        counter += deltaTime;
        /*if (counter > 10.f)
        {
            if (!testPlayerSpaceship.expired())
            {
                testPlayerSpaceship.lock()->Destroy();
            }
        }*/
    }
}