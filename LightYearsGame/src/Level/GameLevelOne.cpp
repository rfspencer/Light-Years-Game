#include "Level/GameLevelOne.h"

#include "Enemy/HexagonStage.h"
#include "Enemy/UFOStage.h"
#include "Enemy/VanguardStage.h"
#include "gameplay/GameStage.h"
#include "gameplay/WaitStage.h"
#include "player/PlayerManager.h"
#include "player/PlayerSpaceShip.h"
#include "Enemy/TwinBladeStage.h"


namespace ly
{

    GameLevelOne::GameLevelOne(Application *owningApp)
        : World(owningApp)
    {

    }

    void GameLevelOne::BeginPlay()
    {
        Player newPlayer = PlayerManager::Get().CreateNewPlayer();
        newPlayer.SpawnSpaceShip(this);
    }

    void GameLevelOne::InitGameStages()
    {
        AddStage(shared<UFOStage>{new UFOStage{this}});

        AddStage(shared<WaitStage>{new WaitStage{this, 5.f}});
        AddStage(shared<VanguardStage>{new VanguardStage{this}});

        AddStage(shared<WaitStage>{new WaitStage{this, 10.f}});
        AddStage(shared<TwinBladeStage>{new TwinBladeStage{this}});

        AddStage(shared<WaitStage>{new WaitStage{this, 10.f}});
        AddStage(shared<HexagonStage>{new HexagonStage{this}});
    }
}