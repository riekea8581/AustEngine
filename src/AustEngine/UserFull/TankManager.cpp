#include "TankManager.h"
#include "TankFactory.h"
#include "LoseScene.h"
#include "..\AustEngine\Sprite\Sprite.h"

int TankManager::TankHealth = 0;

TankManager::TankManager(const Vect & v, TerrainObject * t)
{
	if(TankHealth <= 0)
		ResetHealth();

	float SpriteXPos = 75;
	float SpriteYPos = 50;

	float SpriteXTrans = 80;
	float SpriteScale = 0.5f;

	for (int i = 0; i < TankMaxHealth; i++)
	{
		SpriteArray[i] = new Sprite(("blueTank"));
		SpriteArray[i]->SetPosition(SpriteXPos, SpriteYPos);
		SpriteArray[i]->SetScaleFactor(SpriteScale, SpriteScale);
		SpriteXPos += SpriteXTrans;
	}

	Drawable::SubmitSceneRegistration();
	myTank = TankFactory::CreateTank(v, t);
	myTank->setParent(this);
}

void TankManager::DecrementHealth(int health)
{
	TankManager::TankHealth -= health;
	if (TankManager::TankHealth <= 0)
	{
		myTank->Kill();
		Alarmable::SubmitSceneRegistration(0, 1.25f);
	}
}

void TankManager::Override(StorageNode node)
{
	TankHealth = (int) node.f1;
	myTank->Recreate(node);
}

void TankManager::Draw2D()
{
	for (int i = 0; i < TankManager::TankHealth; i++)
	{
		SpriteArray[i]->Render();
	}
}

void TankManager::Alarm0()
{
	SceneManager::SubmitChangeScene(new LoseScene());
}

TankManager::~TankManager()
{
	for (int i = 0; i < TankMaxHealth; i++)
	{
		delete SpriteArray[i];
	}
}