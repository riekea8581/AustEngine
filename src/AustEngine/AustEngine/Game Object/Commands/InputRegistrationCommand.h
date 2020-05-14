#pragma once

#include "Command.h"
#include "../Inputable.h"
#include "../Attorneys/InputableAttorney.h"

class Inputable;

class InputRegistrationCommand : public Command
{
public:
	InputRegistrationCommand(Inputable * i, AZUL_KEY k, EVENT_TYPE e, Inputable::InputIterator it)
		:target(i), key(k), eventType(e), iterator(it) { };
	virtual void execute() { InputableAttorney::InputRegistration::SceneRegistration(target, key, eventType, iterator); };
private:
	Inputable * target;
	AZUL_KEY key;
	EVENT_TYPE eventType;
	Inputable::InputIterator iterator;
};