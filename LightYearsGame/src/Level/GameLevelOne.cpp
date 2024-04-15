#include "Level/GameLevelOne.h"

#include "Enemy/Vanguard.h"
#include "player/PlayerSpaceShip.h"
#include "framework/TimerManager.h"


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
        TimerManager::Get().SetTimer(GetWeakRef(), &GameLevelOne::TimerCallback_Test, 10.f);
    }

    void GameLevelOne::TimerCallback_Test()
    {
        
    }
}