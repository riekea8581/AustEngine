#include "EnemyBossBullet.h"
#include "BossBulletFactory.h"
#include "..\AustEngine\Resource Managers\ShaderManager.h"
#include "..\AustEngine\Resource Managers\ModelManager.h"
#include "..\AustEngine\Camera Manager\CameraManager.h"
#include "..\AustEngine\Collision\VolumeType.h"

const float EnemyBossBullet::BulletTime = 6;

void EnemyBossBullet::Initialize(Vect v, Matrix m, float t)
{
	dead = false;
	MyTime = t;
	EnemyBulletScale.set(SCALE, 2, 2, 2);
	EnemyBulletRot = m;
	EnemyBulletPos = v;
	Matrix world = EnemyBulletScale * EnemyBulletRot * Matrix(TRANS, EnemyBulletPos);
	myBSphere->SetWorld(world);
	this->UpdateCollisionData(world);
	SubmitEntry();
}

void EnemyBossBullet::SceneEntry()
{
	Updatable::SubmitSceneRegistration();
	Drawable::SubmitSceneRegistration();
	Alarmable::SubmitSceneRegistration(0, MyTime);
	StorableManager::StoreElement(this);
	SubmitCollisionRegistration();
}

void EnemyBossBullet::SceneExit()
{
	Updatable::SubmitSceneDeregistration();
	Drawable::SubmitSceneDeregistration();
	SubmitCollisionDeregistration();
	StorableManager::UnStoreElement(this);
	BossBulletFactory::RecycleEnemyBullet(this);
}