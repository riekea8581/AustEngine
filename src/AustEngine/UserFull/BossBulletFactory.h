#pragma once

#include <stack>
#include "EnemyBossBullet.h"

class EnemyBossBullet;

class BossBulletFactory
{
private:
	static BossBulletFactory* ptrInstance;

	BossBulletFactory() = default;
	BossBulletFactory(const BossBulletFactory&) = delete;
	BossBulletFactory& operator=(const BossBulletFactory&) = delete;
	~BossBulletFactory();

	static BossBulletFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new BossBulletFactory;
		return *ptrInstance;
	}

	std::stack<EnemyBossBullet*> allItems;
	std::stack<EnemyBossBullet*> recycledItems;

	void privCreateEnemyBullet(Vect v, Matrix m);
	void privRecycleEnemyBullet(EnemyBossBullet* b);

public:

	static void CreateEnemyBullet(Vect v, Matrix m) { Instance().privCreateEnemyBullet(v, m); };
	static void RecycleEnemyBullet(EnemyBossBullet* b) { Instance().privRecycleEnemyBullet(b); };
	static void Terminate();
};