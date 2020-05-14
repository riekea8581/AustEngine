#include "Enemy.h"
#include "EnemyManager.h"
#include "EnemyBaseFactory.h"
#include "Tank.h"
#include "EnemyBulletFactory.h"
#include "..\AustEngine\Resource Managers\ShaderManager.h"
#include "..\AustEngine\Resource Managers\TextureManager.h"
#include "..\AustEngine\Resource Managers\ModelManager.h"
#include "..\AustEngine\Camera Manager\CameraManager.h"
#include "..\AustEngine\Scene\SceneManager.h"
#include "..\AustEngine\Collision\VolumeType.h"
#include "..\AustEngine\MathTools\MathTools.h"
#include "..\AustEngine\ParticleSystem\ParticleEffect.h"
#include <math.h>

const float Enemy::InitialTime = 0.125;
const float Enemy::FireTime = 3;

void Enemy::Draw()
{
	myModel->Render(SceneManager::GetCurrentScene()->getCamera());
}

void Enemy::Collision(Bullet *)
{
	health--;
	if (health <= 0)
	{
		parent->Despawn(parentIndex);
		SubmitExit();
	}
}

void Enemy::Collision(Tank *)
{
	myEffect->SpawnParticleGenerator(ShipPos);
	health = 0;
	parent->Despawn(parentIndex);
	SubmitExit();
}

void Enemy::Collision(Tree *)
{
	myEffect->SpawnParticleGenerator(ShipPos);
	health--;
	if (health <= 0)
	{
		parent->Despawn(parentIndex);
		SubmitExit();
	}
}

void Enemy::Store(StorageNode & node)
{
	strcpy_s(node.tag, "Enemy");
	node.v1 = colliderColor;
	node.v2 = ShipPos;
	node.m1 = ShipRot;
	node.m2 = ShipScale;
	node.f1 = (float) health;
	node.f2 = ShipCurrentAngle;
	node.b1 = firing;
	node.alarms[0] = Alarmable::CheckAlarm(AlarmableManager::ALARM_ID::ALARM_0);
}

void Enemy::Recreate(const StorageNode & node)
{
	colliderColor = node.v1;
	ShipPos = node.v2;
	ShipRot = node.m1;
	ShipScale = node.m2;
	health = (int) node.f1;
	ShipCurrentAngle = node.f2;
	firing = node.b1;
	if (node.alarms[0] != 0)
	{
		MyTime = node.alarms[0];
	}
}

Enemy::~Enemy()
{
	delete myModel;
}