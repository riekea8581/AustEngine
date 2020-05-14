#pragma once

#include "../AustEngine/Scene/Scene.h"

class StartHack;
class StartBG;

class StartScene : public Scene
{
public:
	StartScene() = default;
	StartScene(const StartScene&) = delete;
	StartScene& operator=(const StartScene&) = delete;
	virtual ~StartScene() {};
	virtual void Initialize();
	virtual void SceneEnd();
private:
	StartHack * hack;
	StartBG * bg;
};
