#pragma once

#include "Enemy.h"

class EnemyManager;

class Tank;
class Bullet;
class EnemyBullet;

class GraphicsObject_TextureLight;
class GraphicsObject_WireframeConstantColor;

typedef GraphicsObject_TextureLight EnemyModel;

class EnemyBase : public Enemy
{
public:
	EnemyBase();
	EnemyBase(const EnemyBase&) = delete;
	EnemyBase& operator=(const EnemyBase&) = delete;
	virtual ~EnemyBase() {};

	void Initialize(Tank * t, Vect v, TerrainObject * mod, float time = InitialTime);

	virtual void Update();

	virtual void Alarm0();

	virtual void SceneEntry();
	virtual void SceneExit();

private:
	const float turretHeight = 11;
	const float ShipTransSpeed = 0.5f;
	const float ShipRotAng = .025f;
};