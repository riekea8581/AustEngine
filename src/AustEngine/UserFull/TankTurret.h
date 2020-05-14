#pragma once

#include "AzulCore.h"
#include "..\AustEngine\Game Object\GameObject.h"

class TankTurretManager;

class Bullet;

typedef GraphicsObject_TextureLight TankTurretModel;

class TankTurret : public GameObject
{
public:
	TankTurret();
	TankTurret(const TankTurret&) = delete;
	TankTurret& operator=(const TankTurret&) = delete;
	virtual ~TankTurret();

	void Initialize();

	void Update();

	void SetMatrices(Vect up, Vect t, Matrix & r, Matrix & s);
	void FireBullet();

	virtual void SceneEntry();
	virtual void SceneExit();

private:

	Vect colliderColor;

	Camera * petCamera;
	Vect up3DCam;
	Vect pos3DCam;
	Vect lookAt3DCam;

	TankTurretModel * myTankTurret;

	Matrix TurretScale;
	Vect TurretPos;
	Matrix TurretRot;
	float TurretCurrentAngle;

	const float scale = 5;
	const float PI = 3.141592f;
	const float TurretRotAng = .05f;
};