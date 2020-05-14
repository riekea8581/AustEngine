#include "CollisionManager.h"
#include <cassert>

CollisionManager::PWTypeID CollisionManager::TypeIDNextNumber = 0;

CollidableGroup *CollisionManager::GetColGroup(PWTypeID id)
{
	return ColGroupCollection[id];
}

void CollisionManager::SetGroupForTypeID(CollisionManager::PWTypeID id)
{
	if (ColGroupCollection[id] == nullptr)
	{
		ColGroupCollection[id] = new CollidableGroup();
		numColGroups++;
	}
}
void CollisionManager::ProcessCollisions()
{
	CollidableGroupCollection::iterator it = ColGroupCollection.begin();
	for (int i = 0; i < numColGroups; i++)
	{
		if (*it != nullptr)
		{
			(*it)->ComputeAABB();
			it++;
		}
	}
	for (CollisionTestCommands::iterator it2 = colTestCmds.begin(); it2 != colTestCmds.end(); it2++)
	{
		(*it2)->execute();
	}
}

CollisionManager::~CollisionManager()
{
	for (CollidableGroupCollection::iterator it = ColGroupCollection.begin(); it != ColGroupCollection.end(); it++)
	{
		delete *it;
	}
	for (CollisionTestCommands::iterator it = colTestCmds.begin(); it != colTestCmds.end(); it++)
	{
		delete *it;
	}
}