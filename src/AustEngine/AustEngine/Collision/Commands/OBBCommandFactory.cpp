#include "OBBCommandFactory.h"

OBBCommandFactory* OBBCommandFactory::ptrInstance = NULL;

OBBColCommand * OBBCommandFactory::privCreateCommand(const CollisionVolumeOBB &b, Vect v)
{
	OBBColCommand* c;
	if (recycledItems.empty())
	{
		c = new OBBColCommand(b, v);
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

void OBBCommandFactory::privRecycleCommand(OBBColCommand* c)
{
	recycledItems.push(static_cast<OBBColCommand*>(c));
}

void OBBCommandFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

OBBCommandFactory::~OBBCommandFactory()
{
	while (!allItems.empty())
	{
		delete allItems.top();
		allItems.pop();
	}
}