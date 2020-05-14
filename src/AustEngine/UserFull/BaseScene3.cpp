#define _USE_MATH_DEFINES

#include <math.h>
#include "BaseScene3.h"
#include "WinScene.h"
#include "WallPlane.h"

#include "Tank.h"
#include "TankManager.h"
#include "TankFactory.h"

#include "Enemy.h"
#include "EnemyManager.h"
#include "EnemyBaseFactory.h"
#include "EnemyBossFactory.h"

#include "Bullet.h"
#include "BulletFactory.h"

#include "EnemyBossBullet.h"
#include "EnemyBulletFactory.h"
#include "BossBulletFactory.h"

#include "GodCam.h"

#include "..\AustEngine\Resource Managers\TextureManager.h"
#include "..\AustEngine\ParticleSystem\ParticleEmitterFactory.h"

void BaseScene3::Initialize()
{
	setTerrain("Level3");
	StorableManager::SetTag("Level3");
	FrontWall = new WallPlane(Matrix(SCALE, 1600, 1600, 1600) * Matrix(ROT_Z, (const float)M_PI / 2)
		* Matrix(ROT_Y, (const float)-M_PI / 2) * Matrix(TRANS, 0, 800, 800), TextureManager::Get("Stage3Wall"));
	BackWall = new WallPlane(Matrix(SCALE, 1600, 1600, 1600) * Matrix(ROT_Z, (const float)M_PI / 2)
		* Matrix(ROT_Y, (const float)M_PI / 2) * Matrix(TRANS, 0, 800, -800), TextureManager::Get("Stage3Wall"));
	RightWall = new WallPlane(Matrix(SCALE, 1600, 1600, 1600) * Matrix(ROT_Z, (const float)M_PI / 2)
		* Matrix(ROT_Y, (const float)M_PI) * Matrix(TRANS, -800, 800, 0), TextureManager::Get("Stage3Wall"));
	LeftWall = new WallPlane(Matrix(SCALE, 1600, 1600, 1600) * Matrix(ROT_Z, (const float)M_PI / 2) * Matrix(TRANS, 800, 800, 0),
		TextureManager::Get("Stage3Wall"));
	TankMgr = new TankManager(Vect(0, 0, 0), getTerrain());
	EnemyMgr = new EnemyManager(getTerrain());
	EnemyMgr->SetState(EnemyManager::STATE_TYPE::BOSS_STATE);
	godCam = new GodCam();
	godCam->SetTank(TankMgr->GetTank());
	EnemyBaseFactory::SetTarget(TankMgr->GetTank());
	EnemyBossFactory::SetTarget(TankMgr->GetTank());
	EnemyMgr->SetNextScene(new WinScene());
	EnemyMgr->SpawnBoss(Vect(100, 500, 100));
	EnemyMgr->SpawnBase(Vect(700, 500, 700));
	EnemyMgr->SpawnBase(Vect(-700, 500, 700));
	EnemyMgr->SpawnBase(Vect(700, 500, -700));
	EnemyMgr->SpawnBase(Vect(-700, 500, -700));

	SetCollisionPair<Enemy, Bullet>();
	SetCollisionPair<Tank, EnemyBullet>();
	SetCollisionPair<Tank, Enemy>();
	SetCollisionTerrain<Bullet>();
	SetCollisionTerrain<EnemyBullet>();
}

void BaseScene3::Recreate()
{
	Initialize();
	int offset = StorableManager::GetTagLength();
	int EnemyCount = 0;
	for (int i = 0; i < StorableManager::GetCount(); i++)
	{
		StorageNode node = StorableManager::Deserialize(offset);
		if (strcmp(node.tag, "Tank") == 0)
		{
			TankMgr->Override(node);
		}
		else if (strcmp(node.tag, "Enemy") == 0)
		{
			EnemyMgr->Override(EnemyCount, node);
			EnemyCount++;
		}
		else if (strcmp(node.tag, "Bullet") == 0)
		{
			if (!node.b1) BulletFactory::CreateBullet(node.v1, node.m1);
		}
		else if (strcmp(node.tag, "EnemyBullet") == 0)
		{
			if (!node.b1) BossBulletFactory::CreateEnemyBullet(node.v1, node.m1);
		}
		offset += sizeof(StorageNode);
	}
}

void BaseScene3::SceneEnd()
{
	delete FrontWall;
	delete BackWall;
	delete LeftWall;
	delete RightWall;
	delete TankMgr;
	delete EnemyMgr;
	delete godCam;
	TankFactory::Terminate();
	EnemyBaseFactory::Terminate();
	EnemyBossFactory::Terminate();
	BulletFactory::Terminate();
	EnemyBulletFactory::Terminate();
	BossBulletFactory::Terminate();
	ParticleEmitterFactory::Terminate();
	StorableManager::ClearList();
}