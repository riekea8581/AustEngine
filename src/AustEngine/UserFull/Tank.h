#pragma once

#include "AzulCore.h"
#include "..\AustEngine\Game Object\GameObject.h"
#include "..\AustEngine\Storable\Storable.h"

class TankManager;

class GraphicsObject_TextureLight;
class GraphicsObject_WireframeConstantColor;

class TankTurret;
class Enemy;
class EnemyBoss; 
class EnemyBullet;
class EnemyBossBullet;
class Tree;
class TerrainObject;
class ParticleEffect;

typedef GraphicsObject_TextureLight TankModel;

class Tank : public GameObject, public Storable
{
public:
	Tank();
	Tank(const Tank&) = delete;
	Tank& operator=(const Tank&) = delete;
	virtual ~Tank();

	void Initialize(Vect v, TerrainObject * t);
	void Kill() { SubmitExit(); };
	virtual void Update();
	virtual void Draw();

	virtual void Alarm0();

	virtual void SceneEntry();
	virtual void SceneExit();

	virtual void KeyPressed(AZUL_KEY k);

	virtual void Collision(Enemy*);
	virtual void Collision(EnemyBullet*);
	virtual void Collision(Tree*);

	Vect GetPos() { return ShipPos; };
	float getRot() { return ShipCurrentAngle; };
	void setParent(TankManager * t) { parent = t; };

	virtual void Store(StorageNode & node);
	virtual void Recreate(const StorageNode & node);

private:
	Matrix ShipRot;
	Matrix ShipScale;
	Vect ShipPos;
	Vect colliderColor;
	
	Vect up3DCam;
	Vect pos3DCam;
	Vect lookAt3DCam;
	
	TankTurret * myTurret;
	TankManager * parent;
	TerrainObject * myTerrain;
	TankModel * myTank;
	ParticleEffect * myEffect;
	Camera * petCamera;

	float ShipCurrentAngle;
	const float PI = 3.141592f;
	const float turretHeight = 11;
	const float ShipTransSpeed = 1;
	const float ShipRotAng = .05f;
	const float Boundary = 775;
	bool BsphereToggle;
	bool CanFire;
};