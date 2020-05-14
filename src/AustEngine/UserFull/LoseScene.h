#pragma once

#include "../AustEngine/Scene/Scene.h"
#include "EnemyManager.h"

class RestartHack;
class LoseBG;

class LoseScene : public Scene
{
public:
	LoseScene() = default;
	LoseScene(const LoseScene&) = delete;
	LoseScene& operator=(const LoseScene&) = delete;
	virtual ~LoseScene() {};
	virtual void Initialize();
	virtual void SceneEnd();
private:
	RestartHack * hack;
	LoseBG * bg;
};
