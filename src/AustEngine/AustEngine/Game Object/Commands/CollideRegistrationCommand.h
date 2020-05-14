#pragma once

#include "Command.h"
#include "../Collidable.h"
#include "../Attorneys/CollisionAttorney.h"

class CollideRegistrationCommand : public Command
{
public:
	CollideRegistrationCommand(Collidable * c) { target = c; };
	virtual void execute() { CollisionAttorney::CommandRegistration::SceneRegistration(target); };
private:
	Collidable * target;
};