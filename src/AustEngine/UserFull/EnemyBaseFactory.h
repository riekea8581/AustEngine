#pragma once

#include <stack>
#include "AzulCore.h"

class Tank;
class EnemyBase;
class TerrainObject;

class EnemyBaseFactory
{
private:
	static EnemyBaseFactory* ptrInstance;

	EnemyBaseFactory() = default;
	EnemyBaseFactory(const EnemyBaseFactory&) = delete;
	EnemyBaseFactory& operator=(const EnemyBaseFactory&) = delete;
	~EnemyBaseFactory();

	static EnemyBaseFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new EnemyBaseFactory;
		return *ptrInstance;
	}

	Tank *target;

	std::stack<EnemyBase*> allItems;
	std::stack<EnemyBase*> recycledItems;

	EnemyBase * privCreateEnemy(Vect v, TerrainObject * mod, float t);
	void privRecycleEnemy(EnemyBase* b);

public:

	static void SetTarget(Tank * f) { Instance().target = f; };
	static EnemyBase * CreateEnemy(Vect v, TerrainObject * mod, float t = 0) { return Instance().privCreateEnemy(v, mod, t); };
	static void RecycleEnemy(EnemyBase* b) { Instance().privRecycleEnemy(b); };
	static void Terminate();
};