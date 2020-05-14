#pragma once

#include "../AustEngine/Scene/Scene.h"

class WallPlane;
class TankManager;
class EnemyManager;
class GodCam;

class BaseScene1 : public Scene
{
public:
	BaseScene1() = default;
	BaseScene1(const BaseScene1&) = delete;
	BaseScene1& operator=(const BaseScene1&) = delete;
	virtual ~BaseScene1() {};

	virtual void Initialize();
	virtual void Recreate();
	virtual void SceneEnd();
private:
	WallPlane * FrontWall;
	WallPlane * BackWall;
	WallPlane * LeftWall;
	WallPlane * RightWall;
	TankManager * TankMgr;
	EnemyManager * EnemyMgr;
	GodCam * godCam;
};
