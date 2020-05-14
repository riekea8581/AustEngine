#define _USE_MATH_DEFINES

#include <math.h>
#include "BaseScene2.h"
#include "BaseScene3.h"
#include "WallPlane.h"

#include "Tank.h"
#include "TankManager.h"
#include "TankFactory.h"

#include "Enemy.h"
#include "EnemyManager.h"
#include "EnemyBaseFactory.h"

#include "Bullet.h"
#include "BulletFactory.h"

#include "EnemyBullet.h"
#include "EnemyBulletFactory.h"

#include "Tree.h"
#include "TreeManager.h"
#include "TreeFactory.h"

#include "GodCam.h"

#include "..\AustEngine\Resource Managers\TextureManager.h"
#include "..\AustEngine\ParticleSystem\ParticleEmitterFactory.h"

void BaseScene2::Initialize()
{
	setTerrain("Level2");
	StorableManager::SetTag("Level2");
	FrontWall = new WallPlane(Matrix(SCALE, 1600, 1600, 1600) * Matrix(ROT_Z, (const float)M_PI / 2)
		* Matrix(ROT_Y, (const float)-M_PI / 2) * Matrix(TRANS, 0, 800, 800), TextureManager::Get("Stage2Wall"));
	BackWall = new WallPlane(Matrix(SCALE, 1600, 1600, 1600) * Matrix(ROT_Z, (const float)M_PI / 2)
		* Matrix(ROT_Y, (const float)M_PI / 2) * Matrix(TRANS, 0, 800, -800), TextureManager::Get("Stage2Wall"));
	RightWall = new WallPlane(Matrix(SCALE, 1600, 1600, 1600) * Matrix(ROT_Z, (const float)M_PI / 2)
		* Matrix(ROT_Y, (const float)M_PI) * Matrix(TRANS, -800, 800, 0), TextureManager::Get("Stage2Wall"));
	LeftWall = new WallPlane(Matrix(SCALE, 1600, 1600, 1600) * Matrix(ROT_Z, (const float)M_PI / 2) * Matrix(TRANS, 800, 800, 0),
		TextureManager::Get("Stage2Wall"));
	TankMgr = new TankManager(Vect(0, 0, -600), getTerrain());
	EnemyMgr = new EnemyManager(getTerrain());
	EnemyMgr->SetState(EnemyManager::STATE_TYPE::BASE_STATE);
	TreeMgr = new TreeManager();
	godCam = new GodCam();
	godCam->SetTank(TankMgr->GetTank());
	EnemyBaseFactory::SetTarget(TankMgr->GetTank());
	EnemyMgr->SetNextScene(new BaseScene3());
	EnemyMgr->SpawnBase(Vect(100, 500, 400));
	EnemyMgr->SpawnBase(Vect(400, 500, 500));
	EnemyMgr->SpawnBase(Vect(-200, 500, 600));
	EnemyMgr->SpawnBase(Vect(-300, 5, 300));
	TreeMgr->Spawn(Vect(0, 5, -450));
	TreeMgr->Spawn(Vect(200, 0, 0));
	TreeMgr->Spawn(Vect(350, 0, -475));
	TreeMgr->Spawn(Vect(500, 0, 50));
	TreeMgr->Spawn(Vect(-200, 0, 50));
	TreeMgr->Spawn(Vect(-300, 20, -450));
	TreeMgr->Spawn(Vect(-450, 20, -250));

	SetCollisionPair<Enemy, Bullet>();
	SetCollisionPair<Tank, EnemyBullet>();
	SetCollisionPair<Tank, Enemy>();
	SetCollisionTerrain<Bullet>();
	SetCollisionTerrain<EnemyBullet>();
	SetCollisionPair<Tree, Enemy>();
	SetCollisionPair<Tree, Tank>();
	SetCollisionPair<Tree, Bullet>();
	SetCollisionPair<Tree, EnemyBullet>();
}

void BaseScene2::Recreate()
{
	Initialize();
	int offset = StorableManager::GetTagLength();
	int EnemyCount = 0;
	int TreeCount = 0;
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
		else if (strcmp(node.tag, "Tree") == 0)
		{
			TreeMgr->Override(TreeCount, node);
			TreeCount++;
		}
		offset += sizeof(StorageNode);
	}
}

void BaseScene2::SceneEnd()
{
	delete FrontWall;
	delete BackWall;
	delete LeftWall;
	delete RightWall;
	delete TankMgr;
	delete EnemyMgr;
	delete TreeMgr;
	delete godCam;
	TankFactory::Terminate();
	EnemyBaseFactory::Terminate();
	BulletFactory::Terminate();
	EnemyBulletFactory::Terminate();
	TreeFactory::Terminate();
	ParticleEmitterFactory::Terminate();
	StorableManager::ClearList();
}