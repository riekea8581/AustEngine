#include "EnemyBulletFactory.h"

EnemyBulletFactory* EnemyBulletFactory::ptrInstance = NULL;

void EnemyBulletFactory::privCreateEnemyBullet(Vect v, Matrix m, float f)
{
	EnemyBaseBullet* b;
	if (recycledItems.empty())
	{
		b = new EnemyBaseBullet();
		allItems.push(b);
	}
	else
	{
		b = recycledItems.top();
		recycledItems.pop();
	}
	if (f != 0)
	{
		b->Initialize(v, m, f);
	}
	else b->Initialize(v, m);
}

void EnemyBulletFactory::privRecycleEnemyBullet(EnemyBaseBullet* b)
{
	recycledItems.push(static_cast<EnemyBaseBullet*>(b));
}

void EnemyBulletFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

EnemyBulletFactory::~EnemyBulletFactory()
{
	while (!allItems.empty())
	{
		delete allItems.top();
		allItems.pop();
	}
}