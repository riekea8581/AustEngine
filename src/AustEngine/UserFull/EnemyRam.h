#pragma once

#include "Enemy.h"

class EnemyManager;

class Tank;
class Bullet;
class EnemyBullet;

class GraphicsObject_TextureLight;
class GraphicsObject_WireframeConstantColor;

typedef GraphicsObject_TextureLight EnemyModel;

class EnemyRam : public Enemy
{
public:
	EnemyRam();
	EnemyRam(const EnemyRam&) = delete;
	EnemyRam& operator=(const EnemyRam&) = delete;
	virtual ~EnemyRam() {};

	void Initialize(Tank * t, Vect v, TerrainObject * mod);

	virtual void Update();

	virtual void SceneEntry();
	virtual void SceneExit();

private:
	const float ShipTransSpeed = 1;
	const float ShipRotAng = .05f;
};