#include "EnemyBaseBullet.h"
#include "EnemyBulletFactory.h"
#include "..\AustEngine\Resource Managers\ShaderManager.h"
#include "..\AustEngine\Resource Managers\ModelManager.h"
#include "..\AustEngine\Camera Manager\CameraManager.h"
#include "..\AustEngine\Collision\VolumeType.h"

const float EnemyBaseBullet::BulletTime = 4;

void EnemyBaseBullet::Initialize(Vect v, Matrix m, float t)
{
	dead = false;
	MyTime = t;
	EnemyBulletScale.set(SCALE, 1, 1, 1);
	EnemyBulletRot = m;
	EnemyBulletPos = v;
	Matrix world = EnemyBulletScale * EnemyBulletRot * Matrix(TRANS, EnemyBulletPos);
	myBSphere->SetWorld(world);
	this->UpdateCollisionData(world);
	SubmitEntry();
}

void EnemyBaseBullet::SceneEntry()
{
	Updatable::SubmitSceneRegistration();
	Drawable::SubmitSceneRegistration();
	Alarmable::SubmitSceneRegistration(0, MyTime);
	StorableManager::StoreElement(this);
	SubmitCollisionRegistration();
}

void EnemyBaseBullet::SceneExit()
{
	dead = true;
	Updatable::SubmitSceneDeregistration();
	Drawable::SubmitSceneDeregistration();
	SubmitCollisionDeregistration();
	StorableManager::UnStoreElement(this);
	EnemyBulletFactory::RecycleEnemyBullet(this);
}