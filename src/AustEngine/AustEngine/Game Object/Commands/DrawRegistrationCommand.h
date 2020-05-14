#pragma once

#include "Command.h"
#include "../Drawable.h"
#include "../Attorneys/DrawableAttorney.h"

class DrawRegistrationCommand : public Command
{
public:
	DrawRegistrationCommand(Drawable * d) { target = d; };
	virtual void execute() { DrawableAttorney::DrawRegistration::SceneRegistration(target); };
private:
	Drawable * target;
};