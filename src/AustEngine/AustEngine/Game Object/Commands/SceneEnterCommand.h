#pragma once

#include "Command.h"
#include "../GameObject.h"
#include "../Attorneys/GameObjectAttorney.h"

class SceneEnterCommand : public Command
{
public:
	SceneEnterCommand(GameObject * g) { target = g; };
	virtual void execute() { GameObjectAttorney::ConnectToScene(target); };
private:
	GameObject * target;
};