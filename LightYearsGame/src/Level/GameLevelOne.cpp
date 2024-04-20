#include "Level/GameLevelOne.h"

#include "Enemy/Vanguard.h"
#include "player/PlayerSpaceShip.h"


namespace ly
{

    GameLevelOne::GameLevelOne(Application *owningApp)
        : World(owningApp)
    {
        testPlayerSpaceship = SpawnActor<PlayerSpaceShip>();
        testPlayerSpaceship.lock()->SetActorLocation(sf::Vector2f(300.f, 490.f));
        testPlayerSpaceship.lock()->SetActorRotation(0.f);

        weak<Vanguard> testSpaceShip = SpawnActor<Vanguard>();
        testSpaceShip.lock()->SetActorLocation(sf::Vector2f {100.f, 50.f});

    }

    void GameLevelOne::BeginPlay()
    {
        timerHandle_Test = TimerManager::Get().SetTimer(GetWeakRef(), &GameLevelOne::TimerCallback_Test, 2.f, true);
    }

    void GameLevelOne::TimerCallback_Test()
    {
        LY_LOG("Callback called!");
        TimerManager::Get().ClearTimer(timerHandle_Test);
    }
}