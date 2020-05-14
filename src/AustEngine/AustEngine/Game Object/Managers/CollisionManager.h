#pragma once

#include "CollidableGroup.h"
#include "../Commands/Collision Testing/CollisionDispatch.h"
#include "../Commands/Collision Testing/CollisionTestPairCommand.h"
#include "../Commands/Collision Testing/CollisionTestSelfCommand.h"
#include "../Commands/Collision Testing/CollisionTestTerrainCommand.h"
#include <vector>
#include <list>

class CollisionManager
{
public:
	using PWTypeID = int;
	static const PWTypeID PWID_UNDEFINED = -1;

private:
	typedef std::vector<CollidableGroup*> CollidableGroupCollection;
	CollidableGroupCollection ColGroupCollection;
	static const int CollectionLength = 2000;

	typedef std::list<CollisionTestCommand*> CollisionTestCommands;
	CollisionTestCommands colTestCmds;

	static PWTypeID TypeIDNextNumber;
	void SetGroupForTypeID(PWTypeID id);

	int numColGroups;

public:
	CollisionManager()
		:ColGroupCollection(CollidableGroupCollection(CollectionLength)), numColGroups(0) {};
	CollisionManager(const CollisionManager&) = delete;
	CollisionManager& operator=(const CollisionManager&) = delete;
	~CollisionManager();

	CollidableGroup *GetColGroup(PWTypeID id);
	void ProcessCollisions();

	// Template Functions

	template <typename C>
	PWTypeID GetTypeID()
	{
		static PWTypeID myTypeID = TypeIDNextNumber++;
		SetGroupForTypeID(myTypeID);
		return myTypeID;
	}
	template<typename C1, typename C2>
	void SetCollisionPair()
	{
		CollidableGroup* pg1 = ColGroupCollection[GetTypeID<C1>()];
		CollidableGroup* pg2 = ColGroupCollection[GetTypeID<C2>()];

		CollisionDispatch<C1, C2>* pDispatch = new CollisionDispatch<C1, C2>();

		colTestCmds.push_back(new CollisionTestPairCommand(pg1, pg2, pDispatch));
	}
	template<typename C> void SetCollisionSelf()
	{
		CollidableGroup* pg = ColGroupCollection[GetTypeID<C>()];

		CollisionDispatch<C, C>* pDispatch = new CollisionDispatch<C, C>();

		colTestCmds.push_back(new CollisionTestSelfCommand(pg, pDispatch));
	}

	template<typename C> void SetCollisionTerrain()
	{
		CollidableGroup* pg = ColGroupCollection[GetTypeID<C>()];

		colTestCmds.push_back(new CollisionTestTerrainCommand(pg));
	}
};