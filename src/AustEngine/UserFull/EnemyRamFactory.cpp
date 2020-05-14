#include "EnemyRamFactory.h"
#include "EnemyRam.h"

EnemyRamFactory* EnemyRamFactory::ptrInstance = NULL;

EnemyRam * EnemyRamFactory::privCreateEnemy(Vect v, TerrainObject * mod)
{
	EnemyRam* b;
	if (recycledItems.empty())
	{
		b = new EnemyRam();
		allItems.push(b);
	}
	else
	{
		b = recycledItems.top();
		recycledItems.pop();
	}
	b->Initialize(target, v, mod);
	return b;
}

void EnemyRamFactory::privRecycleEnemy(EnemyRam* b)
{
	recycledItems.push(static_cast<EnemyRam*>(b));
}

void EnemyRamFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

EnemyRamFactory::~EnemyRamFactory()
{
	while (!allItems.empty())
	{
		delete allItems.top();
		allItems.pop();
	}
}