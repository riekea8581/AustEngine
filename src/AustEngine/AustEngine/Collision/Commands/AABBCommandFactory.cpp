#include "AABBCommandFactory.h"

AABBCommandFactory* AABBCommandFactory::ptrInstance = NULL;

AABBColCommand * AABBCommandFactory::privCreateCommand(const CollisionVolumeAABB &b, Vect v)
{
	AABBColCommand* c;
	if (recycledItems.empty())
	{
		c = new AABBColCommand(b, v);
		allItems.push(c);
	}
	else
	{
		c = recycledItems.top();
		recycledItems.pop();
		c->setBox(b);
		c->setColor(v);
	}
	return c;
}

void AABBCommandFactory::privRecycleCommand(AABBColCommand* c)
{
	recycledItems.push(static_cast<AABBColCommand*>(c));
}

void AABBCommandFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

AABBCommandFactory::~AABBCommandFactory()
{
	while (!allItems.empty())
	{
		delete allItems.top();
		allItems.pop();
	}
}