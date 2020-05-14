#include "Bullet.h"
#include "BulletFactory.h"
#include "..\AustEngine\ParticleSystem\ParticleEffect.h"
#include "..\AustEngine\Resource Managers\ShaderManager.h"
#include "..\AustEngine\Resource Managers\ModelManager.h"
#include "..\AustEngine\Resource Managers\ParticleEffectManager.h"
#include "..\AustEngine\Camera Manager\CameraManager.h"
#include "..\AustEngine\Collision\VolumeType.h"

const float Bullet::BulletTime = 4;

Bullet::Bullet()
{
	Model *PModelSphere = ModelManager::Get("UnitSphere");

	ShaderObject *pShaderObject_constantColor = ShaderManager::Get("colorConstantRender");

	Vect Blue(0.0f, 0.0f, 1.0f, 1.0f);

	myBSphere = new BSphere(PModelSphere, pShaderObject_constantColor, Blue);

	myEffect = ParticleEffectManager::Get("FireExplosion");

	SetColliderModel(PModelSphere, VolumeType::BSPHERE);

	SetCollidableGroup<Bullet>();
}

void Bullet::Initialize(Vect v, Matrix m, float t)
{
	dead = false;
	MyTime = t;
	BulletScale.set(SCALE, 1, 1, 1);
	BulletRot = m;
	BulletPos = v;
	Matrix world = BulletScale * BulletRot * Matrix(TRANS, BulletPos);
	myBSphere->SetWorld(world);
	this->UpdateCollisionData(world);
	SubmitEntry();
}

void Bullet::Update()
{
	BulletPos += Vect(0, 0, 1) * BulletRot * BulletTransSpeed;

	// adjust matrix
	Matrix world = BulletScale * BulletRot * Matrix(TRANS, BulletPos);
	myBSphere->SetWorld(world);
	this->UpdateCollisionData(world);
}

void Bullet::Draw()
{
	myBSphere->Render(SceneManager::GetCurrentScene()->getCamera());
}

void Bullet::Collision(Enemy*)
{
	myEffect->SpawnParticleGenerator(BulletPos);
	if (Alarmable::CheckAlarm(AlarmableManager::ALARM_ID::ALARM_0) != 0)
		Alarmable::SubmitSceneDeregistration(0);
	SubmitExit();
};

void Bullet::Collision(Tree*)
{
	myEffect->SpawnParticleGenerator(BulletPos);
	if (Alarmable::CheckAlarm(AlarmableManager::ALARM_ID::ALARM_0) != 0)
		Alarmable::SubmitSceneDeregistration(0);
	SubmitExit();
};

void Bullet::CollisionTerrain()
{
	myEffect->SpawnParticleGenerator(BulletPos);
	if (Alarmable::CheckAlarm(AlarmableManager::ALARM_ID::ALARM_0) != 0)
		Alarmable::SubmitSceneDeregistration(0);
	SubmitExit();
};

void Bullet::SceneEntry()
{
	Updatable::SubmitSceneRegistration();
	Drawable::SubmitSceneRegistration();
	Alarmable::SubmitSceneRegistration(0, MyTime);
	SubmitCollisionRegistration();
	StorableManager::StoreElement(this);
}

void Bullet::SceneExit()
{
	dead = true;
	Updatable::SubmitSceneDeregistration();
	Drawable::SubmitSceneDeregistration();
	SubmitCollisionDeregistration();
	StorableManager::UnStoreElement(this);
	BulletFactory::RecycleBullet(this);
}

void Bullet::Store(StorageNode & node)
{
	strcpy_s(node.tag, "Bullet");
	node.v1 = BulletPos;
	node.m1 = BulletRot;
	node.b1 = dead;
	node.alarms[0] = Alarmable::CheckAlarm(AlarmableManager::ALARM_ID::ALARM_0);
}

Bullet::~Bullet()
{
	delete myBSphere;
}