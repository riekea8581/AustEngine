#pragma once

#include "Command.h"
#include "../Updatable.h"
#include "../Attorneys/UpdatableAttorney.h"

class UpdateRegistrationCommand : public Command
{
public:
	UpdateRegistrationCommand(Updatable * u) { target = u; };
	virtual void execute() { UpdatableAttorney::UpdateRegistration::SceneRegistration(target); };
private:
	Updatable * target;
};