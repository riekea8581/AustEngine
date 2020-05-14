#pragma once

#include "../Updatable.h"
#include "../Attorneys/UpdatableAttorney.h"

class UpdateDeregistrationCommand : public Command
{
public:
	UpdateDeregistrationCommand(Updatable * u) { target = u; };
	virtual void execute() { UpdatableAttorney::UpdateRegistration::SceneDeregistration(target); };
private:
	Updatable * target;
};