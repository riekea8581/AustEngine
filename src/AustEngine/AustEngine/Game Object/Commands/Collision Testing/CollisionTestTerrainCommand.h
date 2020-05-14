#pragma once

#include "CollisionTestCommand.h"

class CollidableGroup;
class CollisionDispatchBase;

class CollisionTestTerrainCommand : public CollisionTestCommand
{
public:
	CollisionTestTerrainCommand() = delete;
	CollisionTestTerrainCommand(const CollisionTestTerrainCommand&) = default;
	CollisionTestTerrainCommand& operator=(const CollisionTestTerrainCommand&) = default;
	virtual ~CollisionTestTerrainCommand();

	CollisionTestTerrainCommand(CollidableGroup *g);

	virtual void execute();

private:
	CollidableGroup * pG;
};