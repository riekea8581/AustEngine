#pragma once

#include <stack>
#include "BSphereColCommand.h"

class BSphereColCommand;

class BSphereCommandFactory
{
private:
	static BSphereCommandFactory* ptrInstance;

	BSphereCommandFactory() = default;
	BSphereCommandFactory(const BSphereCommandFactory&) = delete;
	BSphereCommandFactory& operator=(const BSphereCommandFactory&) = delete;
	~BSphereCommandFactory();

	static BSphereCommandFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new BSphereCommandFactory;
		return *ptrInstance;
	}

	std::stack<BSphereColCommand*> allItems;
	std::stack<BSphereColCommand*> recycledItems;

	BSphereColCommand * privCreateCommand(const CollisionVolumeBSphere &s, Vect v);
	void privRecycleCommand(BSphereColCommand* c);

public:
	static BSphereColCommand * CreateCommand(const CollisionVolumeBSphere &s, Vect v) { return Instance().privCreateCommand(s, v); };
	static void RecycleCommand(BSphereColCommand* c) { Instance().privRecycleCommand(c); };
	static void Terminate();
};