#pragma once

#include "Enemy.h"

class EnemyManager;

class Tank;
class Bullet;
class EnemyBullet;

class GraphicsObject_TextureLight;
class GraphicsObject_WireframeConstantColor;

typedef GraphicsObject_TextureLight EnemyModel;

class EnemyBoss : public Enemy
{
public:
	EnemyBoss();
	EnemyBoss(const EnemyBoss&) = delete;
	EnemyBoss& operator=(const EnemyBoss&) = delete;
	virtual ~EnemyBoss() {};

	void Initialize(Tank * t, Vect v, TerrainObject * mod, float time = InitialTime);

	virtual void Update();

	virtual void Collision(Tank*) override {};
	virtual void Alarm0();

	virtual void SceneEntry();
	virtual void SceneExit();

private:
	const float turretHeight = 11;
	const float ShipTransSpeed = 0.25f;
	const float ShipRotAng = .035f;
	const float scale = 10;
};