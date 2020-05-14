#pragma once

#include "..\AustEngine\Game Object\GameObject.h"
#include "..\AustEngine\Storable\Storable.h"

class EnemyManager;

class Tank;
class Bullet;
class EnemyBullet;
class Tree;
class ParticleEffect;

class GraphicsObject_TextureLight;
class GraphicsObject_WireframeConstantColor;

typedef GraphicsObject_TextureLight EnemyModel;

class Enemy : public GameObject, public Storable
{
public:
	Enemy() {};
	Enemy(const Enemy&) = delete;
	Enemy& operator=(const Enemy&) = delete;
	virtual ~Enemy();

	virtual void Draw();

	virtual void Collision(Bullet*);
	virtual void Collision(Tank*);
	virtual void Collision(Tree*);

	int getHealth() { return health; };
	void setParent(EnemyManager * e) { parent = e; };
	void setParentIndex(int i) { parentIndex = i; };

	virtual void Store(StorageNode & node);
	virtual void Recreate(const StorageNode & node);

protected:
	Tank * target;
	EnemyManager * parent;
	TerrainObject * myTerrain;
	ParticleEffect * myEffect;

	Vect colliderColor;
	
	EnemyModel * myModel;

	Matrix ShipScale;
	Vect ShipPos;
	Matrix ShipRot;
	float ShipCurrentAngle;

	const float PI = 3.141592f;
	const float Boundary = 775;

	int parentIndex;
	int health;
	bool firing;
	static const float InitialTime;
	static const float FireTime;
	float MyTime;
};