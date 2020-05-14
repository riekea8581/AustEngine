#pragma once

#include "Command.h"
#include "../Inputable.h"
#include "../Attorneys/InputableAttorney.h"

class InputDeregistrationCommand : public Command
{
public:
	InputDeregistrationCommand(Inputable * i, EVENT_TYPE e, Inputable::InputIterator it)
		:target(i), eventType(e), iterator(it) { };
	virtual void execute() { InputableAttorney::InputRegistration::SceneDeregistration(target, eventType, iterator); };
private:
	Inputable * target;
	EVENT_TYPE eventType;
	Inputable::InputIterator iterator;
};