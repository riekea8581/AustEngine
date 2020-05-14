#include "EnemyRam.h"
#include "EnemyManager.h"
#include "EnemyRamFactory.h"
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

EnemyRam::EnemyRam()
{
	Model *pModelEnemyRam = ModelManager::Get("Tank");

	Texture *pEnemyRamTex = TextureManager::Get("gray");

	ShaderObject *pShaderObject_constantColor = ShaderManager::Get("textureLightRender");

	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	Vect Blue(0.0f, 0.0f, 1.0f, 1.0f);

	myModel = new TankModel(pModelEnemyRam, pShaderObject_constantColor, pEnemyRamTex, LightColor, LightPos);

	myEffect = ParticleEffectManager::Get("FireExplosion");

	SetColliderModel(pModelEnemyRam, VolumeType::OBB);

	colliderColor = Vect(0, 0, 1.0f);

	SetCollidableGroup<Enemy>();
}

void EnemyRam::Initialize(Tank * t, Vect v, TerrainObject * mod)
{
	myTerrain = mod;
	
	ShipScale.set(SCALE, 4, 4, 4);
	ShipPos.set(v.X(), v.Y() + 500, v.Z());
	ShipCurrentAngle = PI / 2;
	ShipRot = Matrix(IDENTITY);

	ShipPos = myTerrain->SnapToCell(ShipPos);
	ShipPos += Vect(0, 5, 0, 0);

	Matrix world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	myModel->SetWorld(world);
	this->InitializeCollisionData(world);

	target = t;
	health = 1;

	SubmitEntry();
}

void EnemyRam::Update()
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
	ShipPos += right * ShipRot * ShipTransSpeed;
	ShipPos = MathTools::ClampPoint(ShipPos, Vect(-Boundary, -Boundary, -Boundary), Vect(Boundary, Boundary, Boundary));

	// Tank adjust matrix
	Matrix world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	myModel->SetWorld(world);
	this->UpdateCollisionData(world);

	// Display Collider
	SendColCommand(colliderColor);
}

void EnemyRam::SceneEntry()
{
	Updatable::SubmitSceneRegistration();
	Drawable::SubmitSceneRegistration();
	SubmitCollisionRegistration();
	StorableManager::StoreElement(this);
	if (health <= 0)
	{
		parent->Despawn(parentIndex);
		SubmitExit();
	}
}

void EnemyRam::SceneExit()
{
	Updatable::SubmitSceneDeregistration();
	Drawable::SubmitSceneDeregistration();
	SubmitCollisionDeregistration();
	EnemyRamFactory::RecycleEnemy(this);
}