#pragma once

#include "Scene.h"

class SceneNull : public Scene
{
public:
	SceneNull() = default;
	SceneNull(const SceneNull&) = delete;
	SceneNull& operator=(const SceneNull&) = delete;
	~SceneNull() {};
private:
	virtual void Initialize() {};
	virtual void SceneEnd() {};
};