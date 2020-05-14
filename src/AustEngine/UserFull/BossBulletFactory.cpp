#include "BossBulletFactory.h"

BossBulletFactory* BossBulletFactory::ptrInstance = NULL;

void BossBulletFactory::privCreateEnemyBullet(Vect v, Matrix m)
{
	EnemyBossBullet* b;
	if (recycledItems.empty())
	{
		b = new EnemyBossBullet();
		allItems.push(b);
	}
	else
	{
		b = recycledItems.top();
		recycledItems.pop();
	}
	b->Initialize(v, m);
}

void BossBulletFactory::privRecycleEnemyBullet(EnemyBossBullet* b)
{
	recycledItems.push(static_cast<EnemyBossBullet*>(b));
}

void BossBulletFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

BossBulletFactory::~BossBulletFactory()
{
	while (!allItems.empty())
	{
		delete allItems.top();
		allItems.pop();
	}
}