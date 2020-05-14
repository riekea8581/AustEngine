#pragma once

#include "..\AustEngine\Game Object\GameObject.h"
#include "EnemyBullet.h"

typedef GraphicsObject_WireframeConstantColor BSphere;

class EnemyBossBullet : public EnemyBullet
{
public:
	EnemyBossBullet() : EnemyBullet() { damage = 2; };
	EnemyBossBullet(const EnemyBossBullet&) = delete;
	EnemyBossBullet& operator=(const EnemyBossBullet&) = delete;
	~EnemyBossBullet() {};

	virtual void Initialize(Vect v, Matrix m, float t = BulletTime);

	virtual void Alarm0() { SubmitExit(); };

	virtual void SceneEntry();
	virtual void SceneExit();

private:
	static const float BulletTime;
};