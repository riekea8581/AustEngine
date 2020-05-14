#pragma once

#include "../AustEngine/Scene/Scene.h"

class WallPlane;
class TankManager;
class EnemyManager;
class TreeManager;
class GodCam;

class BaseScene2 : public Scene
{
public:
	BaseScene2() = default;
	BaseScene2(const BaseScene2&) = delete;
	BaseScene2& operator=(const BaseScene2&) = delete;
	virtual ~BaseScene2() {};
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
	TreeManager * TreeMgr;
	GodCam * godCam;
};
