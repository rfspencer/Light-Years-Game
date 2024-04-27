#include "Level/GameLevelOne.h"

#include "Enemy/HexagonStage.h"
#include "Enemy/UFOStage.h"
#include "Enemy/VanguardStage.h"
#include "Enemy/TwinBladeStage.h"
#include "gameplay/GameStage.h"
#include "gameplay/WaitStage.h"
#include "player/PlayerManager.h"
#include "player/PlayerSpaceShip.h"
#include "widgets/GameplayHUD.h"


namespace ly
{

    GameLevelOne::GameLevelOne(Application *owningApp)
        : World(owningApp)
    {

    }

    void GameLevelOne::BeginPlay()
    {
        Player& newPlayer = PlayerManager::Get().CreateNewPlayer();
        mPlayerSpaceShip = newPlayer.SpawnSpaceShip(this);
        mPlayerSpaceShip.lock()->onActorDestroyed.BindAction(GetWeakRef(), &GameLevelOne::PlayerSpaceShipDestroyed);
        mGameplayHUD = SpawnHUD<GameplayHUD>();
    }

    void GameLevelOne::PlayerSpaceShipDestroyed(Actor *destroyedPlayerSpaceShip)
    {
        mPlayerSpaceShip = PlayerManager::Get().GetPlayer()->SpawnSpaceShip(this);
        if (!mPlayerSpaceShip.expired())
        {
            mPlayerSpaceShip.lock()->onActorDestroyed.BindAction(GetWeakRef(), &GameLevelOne::PlayerSpaceShipDestroyed);
        }
        else
        {
            GameOver();
        }
    }

    void GameLevelOne::InitGameStages()
    {
        AddStage(shared<WaitStage>{new WaitStage{this, 5.f}});
        AddStage(shared<VanguardStage>{new VanguardStage{this}});

        AddStage(shared<WaitStage>{new WaitStage{this, 10.f}});
        AddStage(shared<TwinBladeStage>{new TwinBladeStage{this}});

        AddStage(shared<WaitStage>{new WaitStage{this, 10.f}});
        AddStage(shared<HexagonStage>{new HexagonStage{this}});

        AddStage(shared<WaitStage>{new WaitStage{this, 10.f}});
        AddStage(shared<UFOStage>{new UFOStage{this}});
    }

    void GameLevelOne::GameOver()
    {
        LY_LOG("Game Over! ===============================================================");
    }
}