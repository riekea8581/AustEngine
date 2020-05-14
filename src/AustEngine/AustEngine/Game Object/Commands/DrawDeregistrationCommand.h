#pragma once

#include "../Drawable.h"
#include "../Attorneys/DrawableAttorney.h"

class DrawDeregistrationCommand : public Command
{
public:
	DrawDeregistrationCommand(Drawable * d) { target = d; };
	virtual void execute() { DrawableAttorney::DrawRegistration::SceneDeregistration(target); };
private:
	Drawable * target;
};