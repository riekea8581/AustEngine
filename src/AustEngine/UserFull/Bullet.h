#pragma once

#include "..\AustEngine\Game Object\GameObject.h"
#include "Tank.h"
#include "Enemy.h"

typedef GraphicsObject_WireframeConstantColor BSphere;

class ParticleEffect;

class Bullet : public GameObject, public Storable
{
public:
	Bullet();
	Bullet(const Bullet&) = delete;
	Bullet& operator=(const Bullet&) = delete;
	virtual ~Bullet();

	void Initialize(Vect v, Matrix m, float t = BulletTime);

	virtual void Update();
	virtual void Draw();

	virtual void Alarm0() { SubmitExit(); };
	virtual void OverrideAlarm(AlarmableManager::ALARM_ID, float) {};

	virtual void SceneEntry();
	virtual void SceneExit();

	virtual void Collision(Enemy*);
	virtual void Collision(Tree*);
	virtual void CollisionTerrain();

	virtual void Store(StorageNode & node);

private:
	Matrix BulletScale;
	Vect BulletPos;
	Matrix BulletRot;
	
	BSphere * myBSphere;
	ParticleEffect * myEffect;

	const float BulletTransSpeed = 1;
	static const float BulletTime;

	float MyTime;
	bool dead;
};