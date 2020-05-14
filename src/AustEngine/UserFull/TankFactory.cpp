#include "TankFactory.h"

TankFactory* TankFactory::ptrInstance = NULL;

Tank * TankFactory::privCreateTank(Vect v, TerrainObject * mod)
{
	Tank* t;
	if (recycledItems.empty())
	{
		t = new Tank();
		allItems.push(t);
	}
	else
	{
		t = recycledItems.top();
		recycledItems.pop();
	}
	t->Initialize(v, mod);
	return t;
}

void TankFactory::privRecycleTank(Tank* b)
{
	recycledItems.push(static_cast<Tank*>(b));
}

void TankFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

TankFactory::~TankFactory()
{
	while (!allItems.empty())
	{
		delete allItems.top();
		allItems.pop();
	}
}