#pragma once

#include <stack>
#include "Bullet.h"

class Bullet;

class BulletFactory
{
private:
	static BulletFactory* ptrInstance;

	BulletFactory() = default;
	BulletFactory(const BulletFactory&) = delete;
	BulletFactory& operator=(const BulletFactory&) = delete;
	~BulletFactory();

	static BulletFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new BulletFactory;
		return *ptrInstance;
	}

	std::stack<Bullet*> allItems;
	std::stack<Bullet*> recycledItems;

	void privCreateBullet(Vect v, Matrix m, float f);
	void privRecycleBullet(Bullet* b);

public:

	static void CreateBullet(Vect v, Matrix m, float f = 0) { Instance().privCreateBullet(v, m, f); };
	static void RecycleBullet(Bullet* b) { Instance().privRecycleBullet(b); };
	static void Terminate();
};