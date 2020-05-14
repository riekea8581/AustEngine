#pragma once

#include <stack>
#include "AABBColCommand.h"

class AABBColCommand;

class AABBCommandFactory
{
private:
	static AABBCommandFactory* ptrInstance;

	AABBCommandFactory() = default;
	AABBCommandFactory(const AABBCommandFactory&) = delete;
	AABBCommandFactory& operator=(const AABBCommandFactory&) = delete;
	~AABBCommandFactory();

	static AABBCommandFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new AABBCommandFactory;
		return *ptrInstance;
	}

	std::stack<AABBColCommand*> allItems;
	std::stack<AABBColCommand*> recycledItems;

	AABBColCommand * privCreateCommand(const CollisionVolumeAABB &b, Vect v);
	void privRecycleCommand(AABBColCommand* c);

public:
	static AABBColCommand * CreateCommand(const CollisionVolumeAABB &b, Vect v) { return Instance().privCreateCommand(b, v); };
	static void RecycleCommand(AABBColCommand* c) { Instance().privRecycleCommand(c); };
	static void Terminate();
};