#include "EnemyBullet.h"
#include "EnemyBulletFactory.h"
#include "..\AustEngine\ParticleSystem\ParticleEffect.h"
#include "..\AustEngine\Resource Managers\ShaderManager.h"
#include "..\AustEngine\Resource Managers\ModelManager.h"
#include "..\AustEngine\Resource Managers\ParticleEffectManager.h"
#include "..\AustEngine\Camera Manager\CameraManager.h"
#include "..\AustEngine\Collision\VolumeType.h"

EnemyBullet::EnemyBullet()
{
	Model *PModelSphere = ModelManager::Get("UnitSphere");

	ShaderObject *pShaderObject_constantColor = ShaderManager::Get("colorConstantRender");

	Vect Blue(0.0f, 0.0f, 1.0f, 1.0f);

	myBSphere = new BSphere(PModelSphere, pShaderObject_constantColor, Blue);

	myEffect = ParticleEffectManager::Get("FireExplosion");

	SetColliderModel(PModelSphere, VolumeType::BSPHERE);

	SetCollidableGroup<EnemyBullet>();
}

void EnemyBullet::Update()
{
	EnemyBulletPos += Vect(0, 0, 1) * EnemyBulletRot * EnemyBulletTransSpeed;

	// adjust matrix
	Matrix world = EnemyBulletScale * EnemyBulletRot * Matrix(TRANS, EnemyBulletPos);
	myBSphere->SetWorld(world);
	this->UpdateCollisionData(world);
}

void EnemyBullet::Draw()
{
	myBSphere->Render(SceneManager::GetCurrentScene()->getCamera());
}

void EnemyBullet::Collision(Tank*)
{
	myEffect->SpawnParticleGenerator(EnemyBulletPos);
	if (Alarmable::CheckAlarm(AlarmableManager::ALARM_ID::ALARM_0) != 0)
		Alarmable::SubmitSceneDeregistration(0);
	SubmitExit();
}

void EnemyBullet::Collision(Tree*)
{
	myEffect->SpawnParticleGenerator(EnemyBulletPos);
	if (Alarmable::CheckAlarm(AlarmableManager::ALARM_ID::ALARM_0) != 0)
		Alarmable::SubmitSceneDeregistration(0);
	SubmitExit();
}

void EnemyBullet::CollisionTerrain()
{
	myEffect->SpawnParticleGenerator(EnemyBulletPos);
	if (Alarmable::CheckAlarm(AlarmableManager::ALARM_ID::ALARM_0) != 0)
		Alarmable::SubmitSceneDeregistration(0);
	SubmitExit();
};

void EnemyBullet::Store(StorageNode & node)
{
	strcpy_s(node.tag, "EnemyBullet");
	node.v1 = EnemyBulletPos;
	node.m1 = EnemyBulletRot;
	node.b1 = dead;
	node.alarms[0] = Alarmable::CheckAlarm(AlarmableManager::ALARM_ID::ALARM_0);
}

EnemyBullet::~EnemyBullet()
{
	delete myBSphere;
}