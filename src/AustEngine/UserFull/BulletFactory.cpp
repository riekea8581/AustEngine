#include "BulletFactory.h"

BulletFactory* BulletFactory::ptrInstance = NULL;

void BulletFactory::privCreateBullet(Vect v, Matrix m, float f)
{
	Bullet* b;
	if (recycledItems.empty())
	{
		b = new Bullet();
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

void BulletFactory::privRecycleBullet(Bullet* b)
{
	recycledItems.push(static_cast<Bullet*>(b));
}

void BulletFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

BulletFactory::~BulletFactory()
{
	while (!allItems.empty())
	{
		delete allItems.top();
		allItems.pop();
	}
}