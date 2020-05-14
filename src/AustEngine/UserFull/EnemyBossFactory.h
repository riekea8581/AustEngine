#pragma once

#include <stack>
#include "AzulCore.h"

class Tank;
class EnemyBoss;
class TerrainObject;

class EnemyBossFactory
{
private:
	static EnemyBossFactory* ptrInstance;

	EnemyBossFactory() = default;
	EnemyBossFactory(const EnemyBossFactory&) = delete;
	EnemyBossFactory& operator=(const EnemyBossFactory&) = delete;
	~EnemyBossFactory();

	static EnemyBossFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new EnemyBossFactory;
		return *ptrInstance;
	}

	Tank *target;

	std::stack<EnemyBoss*> allItems;
	std::stack<EnemyBoss*> recycledItems;

	EnemyBoss * privCreateEnemy(Vect v, TerrainObject * mod, float t);
	void privRecycleEnemy(EnemyBoss* b);

public:

	static void SetTarget(Tank * f) { Instance().target = f; };
	static EnemyBoss * CreateEnemy(Vect v, TerrainObject * mod, float t = 0) { return Instance().privCreateEnemy(v, mod, t); };
	static void RecycleEnemy(EnemyBoss* b) { Instance().privRecycleEnemy(b); };
	static void Terminate();
};