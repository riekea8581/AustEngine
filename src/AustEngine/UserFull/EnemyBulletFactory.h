#pragma once

#include <stack>
#include "EnemyBaseBullet.h"

class EnemyBaseBullet;

class EnemyBulletFactory
{
private:
	static EnemyBulletFactory* ptrInstance;

	EnemyBulletFactory() = default;
	EnemyBulletFactory(const EnemyBulletFactory&) = delete;
	EnemyBulletFactory& operator=(const EnemyBulletFactory&) = delete;
	~EnemyBulletFactory();

	static EnemyBulletFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new EnemyBulletFactory;
		return *ptrInstance;
	}

	std::stack<EnemyBaseBullet*> allItems;
	std::stack<EnemyBaseBullet*> recycledItems;

	void privCreateEnemyBullet(Vect v, Matrix m, float f);
	void privRecycleEnemyBullet(EnemyBaseBullet* b);

public:

	static void CreateEnemyBullet(Vect v, Matrix m, float f = 0) { Instance().privCreateEnemyBullet(v, m, f); };
	static void RecycleEnemyBullet(EnemyBaseBullet* b) { Instance().privRecycleEnemyBullet(b); };
	static void Terminate();
};