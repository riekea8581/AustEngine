#include "TankTurret.h"
#include "BulletFactory.h"
#include "..\AustEngine\Resource Managers\ShaderManager.h"
#include "..\AustEngine\Resource Managers\TextureManager.h"
#include "..\AustEngine\Resource Managers\ModelManager.h"

TankTurret::TankTurret()
{
	//Model *pModelTankTurret = ModelManager::Get("TankTurret");
	//
	//Texture *pTankTurretTex = TextureManager::Get("blue");
	//
	//ShaderObject *pShaderObject_textureLight = ShaderManager::Get("textureLightRender");
	//
	//Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	//Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	//Vect Blue(0.0f, 0.0f, 1.0f, 1.0f);
	//
	//myTankTurret = new TankTurretModel(pModelTankTurret, pShaderObject_textureLight, pTankTurretTex, LightColor, LightPos);
	Initialize();
}

void TankTurret::Initialize()
{
	TurretScale.set(SCALE, scale, scale, scale);
	TurretCurrentAngle = 0;
	SubmitEntry();
}

void TankTurret::Update()
{
	// Turret Rotation movement (not using time-based values for simplicity)
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_Q))
	{
		TurretCurrentAngle += TurretRotAng;
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_E))
	{
		TurretCurrentAngle -= TurretRotAng;
	}
}

void TankTurret::SetMatrices(Vect t, Vect up, Matrix & r, Matrix & s)
{
	TurretPos = t;
	TurretRot = r;
	TurretRot = r * Matrix(ROT_AXIS_ANGLE, up, TurretCurrentAngle);
	TurretScale = s;
	//Matrix world = TurretScale * TurretRot * Matrix(TRANS, TurretPos);
	//myTank->SetWorld(world);
}

void TankTurret::FireBullet()
{
	BulletFactory::CreateBullet(TurretPos, TurretRot);
}

void TankTurret::SceneEntry()
{
	Updatable::SubmitSceneRegistration();
	//Drawable::SubmitSceneRegistration();
}

void TankTurret::SceneExit()
{
	Updatable::SubmitSceneDeregistration();
	//Drawable::SubmitSceneDeregistration();
}

TankTurret::~TankTurret()
{

}