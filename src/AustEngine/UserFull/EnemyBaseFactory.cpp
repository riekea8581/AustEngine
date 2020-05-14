#include "EnemyBaseFactory.h"
#include "EnemyBase.h"

EnemyBaseFactory* EnemyBaseFactory::ptrInstance = NULL;

EnemyBase * EnemyBaseFactory::privCreateEnemy(Vect v, TerrainObject * mod, float t)
{
	EnemyBase* b;
	if (recycledItems.empty())
	{
		b = new EnemyBase();
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

void EnemyBaseFactory::privRecycleEnemy(EnemyBase* b)
{
	recycledItems.push(static_cast<EnemyBase*>(b));
}

void EnemyBaseFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

EnemyBaseFactory::~EnemyBaseFactory()
{
	while (!allItems.empty())
	{
		delete allItems.top();
		allItems.pop();
	}
}