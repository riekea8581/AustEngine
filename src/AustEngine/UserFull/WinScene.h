#pragma once

#include "../AustEngine/Scene/Scene.h"
#include "EnemyManager.h"

class RestartHack;
class WinBG;

class WinScene : public Scene
{
public:
	WinScene() = default;
	WinScene(const WinScene&) = delete;
	WinScene& operator=(const WinScene&) = delete;
	virtual ~WinScene() {};
	virtual void Initialize();
	virtual void SceneEnd();
private:

	RestartHack * hack;
	WinBG * bg;
};
