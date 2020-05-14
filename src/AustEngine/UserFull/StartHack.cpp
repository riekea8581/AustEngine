#include "StartHack.h"
#include "BaseScene1.h"
#include "..\AustEngine\Scene\SceneManager.h"
#include "..\AustEngine\Storable\StorableManager.h"

StartHack::StartHack()
{
	Inputable::SubmitSceneRegistration(KEY_1, KEY_PRESS);
	Inputable::SubmitSceneRegistration(KEY_2, KEY_PRESS);
}

void StartHack::KeyPressed(AZUL_KEY k)
{
	switch (k)
	{
	case AZUL_KEY::KEY_1:
		SceneManager::SubmitChangeScene(new BaseScene1());
		break;
	case AZUL_KEY::KEY_2:
		if(StorableManager::ReadFromFile())
			StorableManager::RecreateScene();
		break;
	}
}