#include "Tank.h"
#include "TankTurret.h"
#include "TankManager.h"
#include "TankFactory.h"
#include "BulletFactory.h"
#include "PauseScene.h"
#include "EnemyBullet.h"
#include "..\AustEngine\ParticleSystem\ParticleEffect.h"
#include "..\AustEngine\Resource Managers\ShaderManager.h"
#include "..\AustEngine\Resource Managers\TextureManager.h"
#include "..\AustEngine\Resource Managers\ModelManager.h"
#include "..\AustEngine\Resource Managers\ParticleEffectManager.h"
#include "..\AustEngine\Camera Manager\CameraManager.h"
#include "..\AustEngine\Scene\SceneManager.h"
#include "..\AustEngine\Collision\Attorneys\VisualizerAttorney.h"
#include "..\AustEngine\Collision\VolumeType.h"
#include "..\AustEngine\Collision\CollisionVolumeBSphere.h"
#include "..\AustEngine\MathTools\MathTools.h"
#include "..\AustEngine\Terrain\TerrainObject.h"

Tank::Tank()
{
	Model *pModelTank = ModelManager::Get("Tank");

	Texture *pTankTex = TextureManager::Get("blue");

	ShaderObject *pShaderObject_textureLight = ShaderManager::Get("textureLightRender");

	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	Vect Blue(0.0f, 0.0f, 1.0f, 1.0f);

	myTank = new TankModel(pModelTank, pShaderObject_textureLight, pTankTex, LightColor, LightPos);

	myEffect = ParticleEffectManager::Get("FireExplosion");

	SetColliderModel(pModelTank, VolumeType::OBB);

	colliderColor = Vect(0, 0, 1.0f);

	SetCollidableGroup<Tank>();

	myTurret = new TankTurret();
}

void Tank::Initialize(Vect v, TerrainObject * t)
{
	myTerrain = t; 
	
	ShipScale.set(SCALE, 5, 5, 5);
	ShipPos.set(v.X(), v.Y() + 500, v.Z());
	ShipCurrentAngle = PI / 2;
	ShipRot = Matrix(IDENTITY);

	ShipPos = myTerrain->SnapToCell(ShipPos);
	ShipPos += Vect(0, 5, 0, 0);

	Matrix world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	myTurret->SetMatrices(ShipPos + Vect(0, turretHeight, 0), Vect(0, 1, 0), ShipRot, ShipScale);
	myTank->SetWorld(world);
	this->InitializeCollisionData(world);

	petCamera = getCamera();
	up3DCam = Vect(0.0f, 1.0f, 0.0f);
	pos3DCam = Vect(ShipPos.X(), ShipPos.Y() + 40.0f, ShipPos.Z() - 120.0f);
	lookAt3DCam = Vect(ShipPos.X(), ShipPos.Y() + 20.0f, ShipPos.Z());
	petCamera->setOrientAndPosition(up3DCam, lookAt3DCam, pos3DCam);
	petCamera->updateCamera(); 

	CanFire = true;
	
	SubmitEntry();
}

void Tank::Update()
{
	// Calculate rotation caused by terrain angling
	Vect up = myTerrain->GetFaceNormal(ShipPos);
	up[w] = 0;
	Vect fwd = up * Matrix(ROT_Z, PI / 2);
	fwd[w] = 0;
	Vect right = up.cross(fwd);
	right[w] = 0;

	Matrix TerrainOffset(right, up, fwd, Vect(0, 0, 0));
	
	ShipRot = Matrix(ROT_AXIS_ANGLE, up, ShipCurrentAngle);

	// Ship translation movement (not using time-based values for simplicity)
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_W))
	{
		ShipPos += fwd * ShipRot * ShipTransSpeed;
		ShipPos = MathTools::ClampPoint(ShipPos, Vect(-Boundary, -Boundary, -Boundary), Vect(Boundary, Boundary, Boundary));
		if (abs(ShipPos.X()) != Boundary && abs(ShipPos.Y()) != Boundary && abs(ShipPos.Z()) != Boundary)
		{
			pos3DCam += fwd * ShipRot * ShipTransSpeed;
		}
		else
		{
			ShipPos += fwd * ShipRot * -ShipTransSpeed;
		}
		lookAt3DCam = Vect(ShipPos.X(), ShipPos.Y() + 20.0f, ShipPos.Z());
		petCamera->setOrientAndPosition(up3DCam, lookAt3DCam, pos3DCam);
		petCamera->updateCamera();
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_S))
	{
		ShipPos += fwd * ShipRot * -ShipTransSpeed;
		ShipPos = MathTools::ClampPoint(ShipPos, Vect(-Boundary, -Boundary, -Boundary), Vect(Boundary, Boundary, Boundary));
		if (abs(ShipPos.X()) != Boundary && abs(ShipPos.Y()) != Boundary && abs(ShipPos.Z()) != Boundary)
		{
			pos3DCam += fwd * ShipRot * -ShipTransSpeed;
		}
		else
		{
			ShipPos += fwd * ShipRot * ShipTransSpeed;
		}
		lookAt3DCam = Vect(ShipPos.X(), ShipPos.Y() + 20.0f, ShipPos.Z());
		petCamera->setOrientAndPosition(up3DCam, lookAt3DCam, pos3DCam);
		petCamera->updateCamera();
	}

	// Ship Rotation movement (not using time-based values for simplicity)
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_A))
	{
		ShipCurrentAngle += ShipRotAng;
		pos3DCam -= ShipPos;
		pos3DCam *= Matrix(ROT_Y, ShipRotAng);
		pos3DCam += ShipPos;
		petCamera->setOrientAndPosition(up3DCam, lookAt3DCam, pos3DCam);
		petCamera->updateCamera();
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_D))
	{
		ShipCurrentAngle -= ShipRotAng;
		pos3DCam -= ShipPos;
		pos3DCam *= Matrix(ROT_Y, -ShipRotAng);
		pos3DCam += ShipPos;
		petCamera->setOrientAndPosition(up3DCam, lookAt3DCam, pos3DCam);
		petCamera->updateCamera();
	}

	// Tank adjust matrix
	ShipRot = TerrainOffset * ShipRot;
	myTurret->SetMatrices(ShipPos + Vect(0, turretHeight, 0), up, ShipRot, ShipScale);
	Matrix world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	myTank->SetWorld(world);
	this->UpdateCollisionData(world);

	// Display BSphere
	SendColCommand(colliderColor);
}

void Tank::KeyPressed(AZUL_KEY k)
{
	switch (k)
	{
	case AZUL_KEY::KEY_SPACE:
		if (CanFire == true)
		{
			CanFire = false;
			Alarmable::SubmitSceneRegistration(0, 1);
			myTurret->FireBullet();
		}
 		break;
	case AZUL_KEY::KEY_ENTER:
		SceneManager::SubmitChangeScene(new PauseScene());
		StorableManager::SerializeAll();
		break;
	}
}

void Tank::Draw()
{
	myTank->Render(SceneManager::GetCurrentScene()->getCamera());
	myTerrain->HighlightCell(ShipPos);
	myTerrain->HighlightAllCells(GetVolume(), GetSphere(), Vect(GetSphere().GetCenter().X() + GetSphere().GetRadius(), GetSphere().GetCenter().Y() + GetSphere().GetRadius(), GetSphere().GetCenter().Z() + GetSphere().GetRadius()),
		Vect(GetSphere().GetCenter().X() - GetSphere().GetRadius(), GetSphere().GetCenter().Y() - GetSphere().GetRadius(), GetSphere().GetCenter().Z() - GetSphere().GetRadius()));
}

void Tank::Alarm0()
{
	CanFire = true;
}

void Tank::SceneEntry()
{
	Updatable::SubmitSceneRegistration();
	Drawable::SubmitSceneRegistration();
	Inputable::SubmitSceneRegistration(KEY_SPACE, KEY_PRESS);
	Inputable::SubmitSceneRegistration(KEY_ENTER, KEY_PRESS);
	SubmitCollisionRegistration();
	StorableManager::StoreElement(this);
}

void Tank::SceneExit()
{
	Updatable::SubmitSceneDeregistration();
	Drawable::SubmitSceneDeregistration();
	if (Alarmable::CheckAlarm(AlarmableManager::ALARM_ID::ALARM_0) != 0)
		Alarmable::SubmitSceneDeregistration(0);
	Inputable::SubmitSceneDeregistration(KEY_SPACE, KEY_PRESS);
	Inputable::SubmitSceneDeregistration(KEY_ENTER, KEY_PRESS);
	SubmitCollisionDeregistration();
	TankFactory::RecycleTank(this);
}

void Tank::Collision(Enemy*)
{
	myEffect->SpawnParticleGenerator(ShipPos);
	parent->DecrementHealth(3);
}

void Tank::Collision(EnemyBullet* other)
{
	parent->DecrementHealth(other->getDamage());
}

void Tank::Collision(Tree*)
{
	myEffect->SpawnParticleGenerator(ShipPos);
	parent->DecrementHealth(1);
}

void Tank::Store(StorageNode & node)
{
	strcpy_s(node.tag, "Tank");
	node.v1 = colliderColor;
	node.v2 = ShipPos;
	node.m1 = Matrix(up3DCam, lookAt3DCam, pos3DCam, Vect(0, 0, 0));
	node.m2 = ShipScale;
	node.f1 = (float) parent->GetHealth();
	node.f2 = ShipCurrentAngle;
	node.b1 = CanFire;
	node.alarms[0] = Alarmable::CheckAlarm(AlarmableManager::ALARM_ID::ALARM_0);
}

void Tank::Recreate(const StorageNode & node)
{
	colliderColor = node.v1;
	ShipPos = node.v2;
	up3DCam = Vect(node.m1.M0(), node.m1.M1(), node.m1.M2(), node.m1.M3());
	lookAt3DCam = Vect(node.m1.M4(), node.m1.M5(), node.m1.M6(), node.m1.M7());
	pos3DCam = Vect(node.m1.M8(), node.m1.M9(), node.m1.M10(), node.m1.M11());
	petCamera->setOrientAndPosition(up3DCam, lookAt3DCam, pos3DCam);
	petCamera->updateCamera(); 
	ShipScale = node.m2;
	ShipCurrentAngle = node.f2;
	CanFire = node.b1;
	if (node.alarms[0] != 0)
	{
		Alarmable::SubmitSceneRegistration(AlarmableManager::ALARM_ID::ALARM_0, node.alarms[0]);
	}
}

Tank::~Tank()
{
	delete myTank;
	delete myTurret;
}