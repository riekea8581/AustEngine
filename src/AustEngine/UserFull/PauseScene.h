#pragma once

#include "../AustEngine/Scene/Scene.h"

class UnpauseHack;
class PauseBG;

class PauseScene : public Scene
{
public:
	PauseScene() = default;
	PauseScene(const PauseScene&) = delete;
	PauseScene& operator=(const PauseScene&) = delete;
	virtual ~PauseScene() {};
	virtual void Initialize();
	virtual void SceneEnd();
private:
	UnpauseHack * hack;
	PauseBG * bg;
};
