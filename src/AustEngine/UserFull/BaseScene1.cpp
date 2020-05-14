#define _USE_MATH_DEFINES

#include <math.h>
#include "BaseScene1.h"
#include "BaseScene2.h"
#include "WallPlane.h"

#include "Tank.h"
#include "TankManager.h"
#include "TankFactory.h"

#include "Enemy.h"
#include "EnemyManager.h"
#include "EnemyBaseFactory.h"
#include "EnemyRamFactory.h"

#include "Bullet.h"
#include "BulletFactory.h"

#include "EnemyBullet.h"
#include "EnemyBulletFactory.h"

#include "GodCam.h"

#include "..\AustEngine\Resource Managers\TextureManager.h"
#include "..\AustEngine\ParticleSystem\ParticleEmitterFactory.h"

void BaseScene1::Initialize()
{
	setTerrain("Level1");
	StorableManager::SetTag("Level1");
	FrontWall = new WallPlane(Matrix(SCALE, 1600, 1600, 1600) * Matrix(ROT_Z, (const float)M_PI / 2)
		* Matrix(ROT_Y, (const float) -M_PI / 2) * Matrix(TRANS, 0, 800, 800), TextureManager::Get("Stage1Wall"));
	BackWall = new WallPlane(Matrix(SCALE, 1600, 1600, 1600) * Matrix(ROT_Z, (const float) M_PI / 2)
		* Matrix(ROT_Y, (const float) M_PI / 2) * Matrix(TRANS, 0, 800, -800), TextureManager::Get("Stage1Wall"));
	RightWall = new WallPlane(Matrix(SCALE, 1600, 1600, 1600) * Matrix(ROT_Z, (const float)M_PI / 2)
		* Matrix(ROT_Y, (const float)M_PI) * Matrix(TRANS, -800, 800, 0), TextureManager::Get("Stage1Wall"));
	LeftWall = new WallPlane(Matrix(SCALE, 1600, 1600, 1600) * Matrix(ROT_Z, (const float) M_PI / 2) * Matrix(TRANS, 800, 800, 0),
		TextureManager::Get("Stage1Wall"));
	TankMgr = new TankManager(Vect(0, 0, 0), getTerrain());
	TankMgr->ResetHealth();
	EnemyMgr = new EnemyManager(getTerrain());
	EnemyMgr->SetState(EnemyManager::STATE_TYPE::BASE_STATE);
	godCam = new GodCam();
	godCam->SetTank(TankMgr->GetTank());
	EnemyBaseFactory::SetTarget(TankMgr->GetTank());
	EnemyRamFactory::SetTarget(TankMgr->GetTank());
	EnemyMgr->SetNextScene(new BaseScene2);
	EnemyMgr->SpawnBase(Vect(160, 5, 160));
	EnemyMgr->SpawnBase(Vect(320, 5, -360));
	EnemyMgr->SpawnBase(Vect(-360, 5, 480));
	EnemyMgr->SpawnRam(Vect(240, 5, 300));
	EnemyMgr->SpawnRam(Vect(-300, 5, 500));

	SetCollisionPair<Enemy, Bullet>();
	SetCollisionPair<Tank, EnemyBullet>();
	SetCollisionPair<Tank, Enemy>();
	SetCollisionTerrain<Bullet>();
	SetCollisionTerrain<EnemyBullet>();
}

void BaseScene1::Recreate()
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
			if (!node.b1)
			{
				BulletFactory::CreateBullet(node.v1, node.m1, node.alarms[0]);
			}
		}
		else if (strcmp(node.tag, "EnemyBullet") == 0)
		{
			if (!node.b1)
			{
				EnemyBulletFactory::CreateEnemyBullet(node.v1, node.m1, node.alarms[0]);
			}
		}
		offset += sizeof(StorageNode);
	}
}

void BaseScene1::SceneEnd()
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
	EnemyRamFactory::Terminate();
	BulletFactory::Terminate();
	EnemyBulletFactory::Terminate();
	ParticleEmitterFactory::Terminate();
	StorableManager::ClearList();
}