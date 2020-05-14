#pragma once

#include <stack>
#include "AzulCore.h"

class Tank;
class EnemyRam;
class TerrainObject;

class EnemyRamFactory
{
private:
	static EnemyRamFactory* ptrInstance;

	EnemyRamFactory() = default;
	EnemyRamFactory(const EnemyRamFactory&) = delete;
	EnemyRamFactory& operator=(const EnemyRamFactory&) = delete;
	~EnemyRamFactory();

	static EnemyRamFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new EnemyRamFactory;
		return *ptrInstance;
	}

	Tank *target;

	std::stack<EnemyRam*> allItems;
	std::stack<EnemyRam*> recycledItems;

	EnemyRam * privCreateEnemy(Vect v, TerrainObject * mod);
	void privRecycleEnemy(EnemyRam* b);

public:

	static void SetTarget(Tank * f) { Instance().target = f; };
	static EnemyRam * CreateEnemy(Vect v, TerrainObject * mod) { return Instance().privCreateEnemy(v, mod); };
	static void RecycleEnemy(EnemyRam* b) { Instance().privRecycleEnemy(b); };
	static void Terminate();
};