#include "BSphereCommandFactory.h"

BSphereCommandFactory* BSphereCommandFactory::ptrInstance = NULL;

BSphereColCommand * BSphereCommandFactory::privCreateCommand(const CollisionVolumeBSphere &s, Vect v)
{
	BSphereColCommand* b;
	if (recycledItems.empty())
	{
		b = new BSphereColCommand(s, v);
		allItems.push(b);
	}
	else
	{
		b = recycledItems.top();
		recycledItems.pop();
		b->setSphere(s);
		b->setColor(v);
	}
	return b;
}

void BSphereCommandFactory::privRecycleCommand(BSphereColCommand* b)
{
	recycledItems.push(static_cast<BSphereColCommand*>(b));
}

void BSphereCommandFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

BSphereCommandFactory::~BSphereCommandFactory()
{
	while (!allItems.empty())
	{
		delete allItems.top();
		allItems.pop();
	}
}