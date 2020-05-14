#pragma once

#include "AzulCore.h"

class CameraManager
{
public:
	CameraManager();
	CameraManager(const CameraManager&) = default;
	CameraManager& operator=(const CameraManager&) = default;
	~CameraManager();

	Camera *getCamera() { return currentCamera; };
	Camera *getOrthCamera() { return orthCamera; };

private:
	Camera * defaultCamera;
	Camera * orthCamera;
	Camera * currentCamera;
};