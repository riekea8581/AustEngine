#include "EnemyBossFactory.h"
#include "EnemyBoss.h"

EnemyBossFactory* EnemyBossFactory::ptrInstance = NULL;

EnemyBoss * EnemyBossFactory::privCreateEnemy(Vect v, TerrainObject * mod, float t)
{
	EnemyBoss* b;
	if (recycledItems.empty())
	{
		b = new EnemyBoss();
		allItems.push(b);
	}
	else
	{
		b = recycledItems.top();
		recycledItems.pop();
	}
	if (t != 0)
	{
		b->Initialize(target, v, mod, t);
	}
	else b->Initialize(target, v, mod);
	return b;
}

void EnemyBossFactory::privRecycleEnemy(EnemyBoss* b)
{
	recycledItems.push(static_cast<EnemyBoss*>(b));
}

void EnemyBossFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

EnemyBossFactory::~EnemyBossFactory()
{
	while (!allItems.empty())
	{
		delete allItems.top();
		allItems.pop();
	}
}