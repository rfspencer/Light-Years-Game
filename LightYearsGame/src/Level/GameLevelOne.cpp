#include "Level/GameLevelOne.h"

#include "Enemy/VanguardStage.h"
#include "gameplay/GameStage.h"
#include "player/PlayerSpaceShip.h"
#include "Enemy/TwinBladeStage.h"


namespace ly
{

    GameLevelOne::GameLevelOne(Application *owningApp)
        : World(owningApp)
    {
        testPlayerSpaceship = SpawnActor<PlayerSpaceShip>();
        testPlayerSpaceship.lock()->SetActorLocation(sf::Vector2f(300.f, 490.f));
        testPlayerSpaceship.lock()->SetActorRotation(0.f);
    }

    void GameLevelOne::BeginPlay()
    {
    }

    void GameLevelOne::InitGameStages()
    {
        AddStage(shared<TwinBladeStage>{new TwinBladeStage{this}});
        AddStage(shared<VanguardStage>{new VanguardStage{this}});
    }
}