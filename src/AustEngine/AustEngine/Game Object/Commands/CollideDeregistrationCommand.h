#pragma once

#include "Command.h"
#include "../Collidable.h"
#include "../Attorneys/CollisionAttorney.h"

class CollideDeregistrationCommand : public Command
{
public:
	CollideDeregistrationCommand(Collidable * u) { target = u; };
	virtual void execute() { CollisionAttorney::CommandRegistration::SceneDeregistration(target); };
private:
	Collidable * target;
};