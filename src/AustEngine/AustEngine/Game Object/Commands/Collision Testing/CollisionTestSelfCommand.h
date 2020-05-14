#pragma once

#include "CollisionTestCommand.h"

class CollidableGroup;
class CollisionDispatchBase;

class CollisionTestSelfCommand : public CollisionTestCommand
{
public:
	CollisionTestSelfCommand() = delete;
	CollisionTestSelfCommand(const CollisionTestSelfCommand&) = default;
	CollisionTestSelfCommand& operator=(const CollisionTestSelfCommand&) = default;
	virtual ~CollisionTestSelfCommand();

	CollisionTestSelfCommand(CollidableGroup *g, CollisionDispatchBase *pd);

	virtual void execute();

private:
	CollidableGroup * pG;
	CollisionDispatchBase * pDispatch;
};