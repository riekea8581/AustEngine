#pragma once

#include <stack>
#include "OBBColCommand.h"

class OBBColCommand;

class OBBCommandFactory
{
private:
	static OBBCommandFactory* ptrInstance;

	OBBCommandFactory() = default;
	OBBCommandFactory(const OBBCommandFactory&) = delete;
	OBBCommandFactory& operator=(const OBBCommandFactory&) = delete;
	~OBBCommandFactory();

	static OBBCommandFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new OBBCommandFactory;
		return *ptrInstance;
	}

	std::stack<OBBColCommand*> allItems;
	std::stack<OBBColCommand*> recycledItems;

	OBBColCommand * privCreateCommand(const CollisionVolumeOBB &b, Vect v);
	void privRecycleCommand(OBBColCommand* c);

public:
	static OBBColCommand * CreateCommand(const CollisionVolumeOBB &b, Vect v) { return Instance().privCreateCommand(b, v); };
	static void RecycleCommand(OBBColCommand* c) { Instance().privRecycleCommand(c); };
	static void Terminate();
};