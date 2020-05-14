#pragma once

#include "../GameObject.h"

class GameObjectAttorney
{
	friend class SceneEnterCommand;
	friend class SceneExitCommand;
private:
	static void ConnectToScene(GameObject * g) { g->ConnectToScene(); };
	static void DisconnectFromScene(GameObject * g) { g->DisconnectFromScene(); };
};