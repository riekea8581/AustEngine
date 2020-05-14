#pragma once

#include "AzulCore.h"
#include "..\AustEngine\Game Object\GameObject.h"

class Tank;

class GodCam : public GameObject
{
public:
	GodCam();
	GodCam(const GodCam&) = delete;
	GodCam& operator=(const GodCam&) = delete;
	virtual ~GodCam() {};

	virtual void Update();

	void SetTank(Tank * t) { petTank = t; };

private:
	Tank * petTank;
	Camera * petCamera;
	Vect up3DCam;
	Vect pos3DCam;
	Vect lookAt3DCam;

	const float speed = 2.0f;
	const float rotSpeed = 0.05f;
	const float PI = 3.141592f;
};