#pragma once

#include "CollisionTestCommand.h"

class CollidableGroup;
class CollisionDispatchBase;

class CollisionTestPairCommand : public CollisionTestCommand
{
public:
	CollisionTestPairCommand() = delete;
	CollisionTestPairCommand(const CollisionTestPairCommand&) = default;
	CollisionTestPairCommand& operator=(const CollisionTestPairCommand&) = default;
	virtual ~CollisionTestPairCommand();

	CollisionTestPairCommand(CollidableGroup *g1, CollidableGroup *g2, CollisionDispatchBase *pd); 

	virtual void execute();

private:
	CollidableGroup * pG1;
	CollidableGroup * pG2;
	CollisionDispatchBase * pDispatch;
};