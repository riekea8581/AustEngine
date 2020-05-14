#pragma once

#include "Command.h"
#include "../GameObject.h"
#include "../Attorneys/GameObjectAttorney.h"

class SceneExitCommand : public Command
{
public:
	SceneExitCommand(GameObject * g) { target = g; };
	virtual void execute() { GameObjectAttorney::DisconnectFromScene(target); };
private:
	GameObject * target;
};