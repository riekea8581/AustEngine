#pragma once

#include "..\AustEngine\Game Object\GameObject.h"

class Enemy;
class EnemyManagerState;

class EnemyManager : public GameObject
{
public:
	enum STATE_TYPE
	{
		BASE_STATE,
		BOSS_STATE
	};

	EnemyManager() = delete;
	EnemyManager(const EnemyManager&) = delete;
	EnemyManager& operator=(const EnemyManager&) = delete;
	virtual ~EnemyManager();

	EnemyManager(TerrainObject * t);

	void SpawnBase(Vect v);
	void SpawnRam(Vect v);
	void SpawnBoss(Vect v);
	void Override(int index, StorageNode node);
	void Despawn(int index);

	virtual void Draw2D();
	virtual void Alarm0();

	void SetState(STATE_TYPE s);
	void SetNextScene(Scene * s) { nextScene = s; };
private:
	static const int EnemyTotal = 10;
	
	int EnemyCount;

	Enemy * EnemyArray[EnemyTotal];
	EnemyManagerState * myState;

	Scene * nextScene;
	TerrainObject * myTerrain;
	bool SceneChanged;
};