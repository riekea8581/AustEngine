#include "EnemyBase.h"
#include "EnemyManager.h"
#include "EnemyBaseFactory.h"
#include "Tank.h"
#include "EnemyBulletFactory.h"
#include "..\AustEngine\Terrain\TerrainObject.h"
#include "..\AustEngine\Resource Managers\ShaderManager.h"
#include "..\AustEngine\Resource Managers\TextureManager.h"
#include "..\AustEngine\Resource Managers\ModelManager.h"
#include "..\AustEngine\Camera Manager\CameraManager.h"
#include "..\AustEngine\Scene\SceneManager.h"
#include "..\AustEngine\Collision\VolumeType.h"
#include "..\AustEngine\MathTools\MathTools.h"
#include "..\AustEngine\Resource Managers\ParticleEffectManager.h"
#include <math.h>

EnemyBase::EnemyBase()
{
	Model *pModelEnemyBase = ModelManager::Get("Tank");

	Texture *pEnemyBaseTex = TextureManager::Get("red");

	ShaderObject *pShaderObject_constantColor = ShaderManager::Get("textureLightRender");

	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	Vect Blue(0.0f, 0.0f, 1.0f, 1.0f);

	myModel = new TankModel(pModelEnemyBase, pShaderObject_constantColor, pEnemyBaseTex, LightColor, LightPos);

	myEffect = ParticleEffectManager::Get("FireExplosion");

	SetColliderModel(pModelEnemyBase, VolumeType::OBB);

	colliderColor = Vect(0, 0, 1.0f);

	SetCollidableGroup<Enemy>();
}

void EnemyBase::Initialize(Tank * t, Vect v, TerrainObject * mod, float time)
{
	myTerrain = mod; 
	MyTime = time;
	
	ShipScale.set(SCALE, 5, 5, 5);
	ShipPos.set(v.X(), v.Y() + 500, v.Z());
	ShipCurrentAngle = PI / 2;
	ShipRot = Matrix(IDENTITY);

	ShipPos = myTerrain->SnapToCell(ShipPos);
	ShipPos += Vect(0, 5, 0, 0);

	Matrix world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	myModel->SetWorld(world);
	this->InitializeCollisionData(world);

	target = t;

	firing = true;
	health = 3;

	SubmitEntry();
}

void EnemyBase::Update()
{
	Vect up = myTerrain->GetFaceNormal(ShipPos);
	up[w] = 0;
	Vect fwd = up * Matrix(ROT_Z, PI / 2);
	fwd[w] = 0;
	Vect right = up.cross(fwd);
	right[w] = 0;

	Matrix TerrainOffset(right, up, fwd, Vect(0, 0, 0));

	ShipRot = Matrix(ROT_AXIS_ANGLE, up, ShipCurrentAngle); 

	Vect targetPos = target->GetPos();
	Vect direction = Vect(1, 0, 0) * ShipRot;
	Vect aim = Vect(targetPos.X() - ShipPos.X(), targetPos.Y() - ShipPos.Y(), targetPos.Z() - ShipPos.Z(), targetPos.W() - ShipPos.W());
	float angle = Vect(direction * Matrix(ROT_Y, 0)).getAngle(aim);
	float angle2 = Vect(direction * Matrix(ROT_Y, PI)).getAngle(aim);
	if (angle <= angle2)
	{
		ShipCurrentAngle += ShipRotAng;
	}
	else
	{
		ShipCurrentAngle -= ShipRotAng;
	}
	if (aim.mag() >= 175)
	{
		ShipPos += right * ShipRot * ShipTransSpeed;
	}
	else if (aim.mag() < 125)
	{
		ShipPos -= right * ShipRot * ShipTransSpeed;
	}
	
	if (aim.mag() <= 250 && firing == false)
	{
		firing = true;
		Alarmable::SubmitSceneRegistration(0, InitialTime);
	}
		

	ShipPos = MathTools::ClampPoint(ShipPos, Vect(-Boundary, -Boundary, -Boundary), Vect(Boundary, Boundary, Boundary));

	// Tank adjust matrix
	Matrix world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	myModel->SetWorld(world);
	this->UpdateCollisionData(world);

	// Display Collider
	SendColCommand(colliderColor);
}

void EnemyBase::Alarm0()
{
	Vect targetPos = target->GetPos(); 
	Vect aim = Vect(targetPos.X() - ShipPos.X(), targetPos.Y() - ShipPos.Y(), targetPos.Z() - ShipPos.Z(), targetPos.W() - ShipPos.W());
	if (aim.mag() <= 250)
	{
		firing = true;
		EnemyBulletFactory::CreateEnemyBullet(ShipPos * Matrix(TRANS, 0, turretHeight, 0), ShipRot);
		Alarmable::SubmitSceneRegistration(0, FireTime);
	}
	else firing = false;
}

void EnemyBase::SceneEntry()
{
	Updatable::SubmitSceneRegistration();
	Drawable::SubmitSceneRegistration();
	Alarmable::SubmitSceneRegistration(0, MyTime);
	SubmitCollisionRegistration();
	StorableManager::StoreElement(this);
	if (health <= 0)
	{
		parent->Despawn(parentIndex);
		SubmitExit();
	}
}

void EnemyBase::SceneExit()
{
	Updatable::SubmitSceneDeregistration();
	Drawable::SubmitSceneDeregistration();
	if (Alarmable::CheckAlarm(AlarmableManager::ALARM_ID::ALARM_0) != 0)
		Alarmable::SubmitSceneDeregistration(0);
	SubmitCollisionDeregistration();
	EnemyBaseFactory::RecycleEnemy(this);
}