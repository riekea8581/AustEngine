#pragma once

#include "..\AustEngine\Game Object\GameObject.h"
#include "EnemyBullet.h"

typedef GraphicsObject_WireframeConstantColor BSphere;

class EnemyBaseBullet : public EnemyBullet
{
public:
	EnemyBaseBullet() : EnemyBullet() { damage = 1; };
	EnemyBaseBullet(const EnemyBaseBullet&) = delete;
	EnemyBaseBullet& operator=(const EnemyBaseBullet&) = delete;
	~EnemyBaseBullet() {};

	virtual void Initialize(Vect v, Matrix m, float t = BulletTime);

	virtual void Alarm0() { SubmitExit(); };

	virtual void SceneEntry();
	virtual void SceneExit();

private:
	static const float BulletTime;
};