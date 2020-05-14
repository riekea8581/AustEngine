#pragma once

#include "..\AustEngine\Game Object\GameObject.h"
#include "Tank.h"
#include "Enemy.h"

typedef GraphicsObject_WireframeConstantColor BSphere;

class ParticleEffect;

class EnemyBullet : public GameObject, public Storable
{
public:
	EnemyBullet();
	EnemyBullet(const EnemyBullet&) = delete;
	EnemyBullet& operator=(const EnemyBullet&) = delete;
	virtual ~EnemyBullet();

	virtual void Initialize(Vect v, Matrix m) {};

	virtual void Update();
	virtual void Draw();

	virtual void Alarm0() { SubmitExit(); };

	virtual void SceneEntry() {};
	virtual void SceneExit() {};

	virtual void Collision(Tank*);
	virtual void Collision(Tree*);
	virtual void CollisionTerrain();

	virtual void Store(StorageNode & s);

	int getDamage() { return damage; };

protected:
	BSphere * myBSphere;
	ParticleEffect * myEffect;
	
	Matrix EnemyBulletScale;
	Vect EnemyBulletPos;
	Matrix EnemyBulletRot;

	const float EnemyBulletTransSpeed = 1;
	float MyTime;

	int damage;
	bool dead;
};