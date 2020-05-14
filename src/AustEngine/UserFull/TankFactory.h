#pragma once

#include <stack>
#include "Tank.h"

class Tank;
class TerrainObject;

class TankFactory
{
private:
	static TankFactory* ptrInstance;

	TankFactory() = default;
	TankFactory(const TankFactory&) = delete;
	TankFactory& operator=(const TankFactory&) = delete;
	~TankFactory();

	static TankFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new TankFactory;
		return *ptrInstance;
	}

	Tank *target;

	std::stack<Tank*> allItems;
	std::stack<Tank*> recycledItems;

	Tank * privCreateTank(Vect v, TerrainObject * t);
	void privRecycleTank(Tank* t);

public:

	static void SetTarget(Tank * f) { Instance().target = f; };
	static Tank * CreateTank(Vect v, TerrainObject * t) { return Instance().privCreateTank(v, t); };
	static void RecycleTank(Tank* t) { Instance().privRecycleTank(t); };
	static void Terminate();
};