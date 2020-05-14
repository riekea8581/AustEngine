#include "EnemyManager.h"
#include "EnemyManagerState.h"
#include "EnemyManagerBaseState.h"
#include "EnemyManagerBossState.h"
#include "Enemy.h"
#include "EnemyBaseFactory.h"
#include "EnemyRamFactory.h"
#include "EnemyBossFactory.h"
#include "..\AustEngine\Sprite\Sprite.h"

EnemyManager::EnemyManager(TerrainObject * t)
{
	myTerrain = t;
	EnemyCount = 0;
	SceneChanged = false;

	Drawable::SubmitSceneRegistration();
}

void EnemyManager::SpawnBase(Vect v)
{
	EnemyArray[EnemyCount] = (Enemy *) EnemyBaseFactory::CreateEnemy(v, myTerrain);
	EnemyArray[EnemyCount]->setParent(this);
	EnemyArray[EnemyCount]->setParentIndex(EnemyCount);
	EnemyCount++;
}

void EnemyManager::SpawnRam(Vect v)
{
	EnemyArray[EnemyCount] = (Enemy *)EnemyRamFactory::CreateEnemy(v, myTerrain);
	EnemyArray[EnemyCount]->setParent(this);
	EnemyArray[EnemyCount]->setParentIndex(EnemyCount);
	EnemyCount++;
}

void EnemyManager::SpawnBoss(Vect v)
{
	EnemyArray[EnemyCount] = (Enemy *)EnemyBossFactory::CreateEnemy(v, myTerrain);
	EnemyArray[EnemyCount]->setParent(this);
	EnemyArray[EnemyCount]->setParentIndex(EnemyCount);
	EnemyCount++;
}

void EnemyManager::Despawn(int index)
{
	EnemyCount--;
	EnemyArray[index] = nullptr;
	if (myState->CheckDeath(EnemyArray[0], EnemyCount))
	{
		Alarmable::SubmitSceneRegistration(0, 1.5f);
	}
}

void EnemyManager::Override(int index, StorageNode node)
{
	EnemyArray[index]->Recreate(node);
}

void EnemyManager::Draw2D()
{
	if(EnemyArray[0] != nullptr)
		myState->DrawHealthBar(EnemyCount, EnemyArray[0]->getHealth());
	myState->DrawHealthBar(EnemyCount, 0);
}

void EnemyManager::Alarm0()
{
	SceneManager::SubmitChangeScene(nextScene);
	SceneChanged = true;
}

void EnemyManager::SetState(STATE_TYPE s)
{
	switch (s)
	{
	case STATE_TYPE::BASE_STATE:
		myState = new EnemyManagerBaseState();
		break;
	case STATE_TYPE::BOSS_STATE:
		myState = new EnemyManagerBossState();
		break;
	}
	myState->LoadSprite();
}

EnemyManager::~EnemyManager()
{
	delete myState;
	if(!SceneChanged)
		delete nextScene;
}