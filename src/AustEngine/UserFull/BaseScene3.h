#pragma once

#include "../AustEngine/Scene/Scene.h"

class WallPlane;
class TankManager;
class EnemyManager;
class GodCam;

class BaseScene3 : public Scene
{
public:
	BaseScene3() = default;
	BaseScene3(const BaseScene3&) = delete;
	BaseScene3& operator=(const BaseScene3&) = delete;
	virtual ~BaseScene3() {};
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
