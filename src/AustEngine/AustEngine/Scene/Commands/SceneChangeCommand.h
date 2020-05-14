#pragma once

#include "SceneCommand.h"

class Scene;

class SceneChangeCommand : public SceneCommand
{
public:
	virtual void Execute();
	void SetTarget(Scene * s);
private:
	Scene * target;
};