#pragma once

#include "..\AustEngine\Game Object\GameObject.h"
#include "..\AustEngine\Storable\Storable.h"

class TreeManager;

class Tank;
class Enemy;
class Bullet;
class EnemyBullet;

class GraphicsObject_TextureLight;
class GraphicsObject_WireframeConstantColor;

typedef GraphicsObject_TextureLight TreeModel;

class Tree : public GameObject, public Storable
{
public:
	Tree();
	Tree(const Tree&) = delete;
	Tree& operator=(const Tree&) = delete;
	virtual ~Tree();

	virtual void Initialize(Vect & v);
	virtual void Draw();

	virtual void Collision(Tank*);
	virtual void Collision(Enemy*);
	virtual void Collision(Bullet*);
	virtual void Collision(EnemyBullet*);

	virtual void SceneEntry();
	virtual void SceneExit();

	float getHealth() { return health; };
	void setParent(TreeManager * e) { parent = e; };
	void setParentIndex(int i) { parentIndex = i; };

	virtual void Store(StorageNode & node);
	virtual void Recreate(const StorageNode & node);

private:
	Tank * target;
	TreeManager * parent;

	Vect colliderColor;

	TreeModel * myModel;

	Matrix TreeScale;
	Vect TreePos;
	Matrix ShipRot;

	int parentIndex;
	float health;

	float PI = 3.14159265f;
	float yOffset = 60;
};