#include "RestartHack.h"
#include "BaseScene1.h"
#include "..\AustEngine\Scene\SceneManager.h"
#include "..\AustEngine\Storable\StorableManager.h"

RestartHack::RestartHack()
{
	Inputable::SubmitSceneRegistration(KEY_ENTER, KEY_PRESS);
}

void RestartHack::KeyPressed(AZUL_KEY k)
{
	switch (k)
	{
	case AZUL_KEY::KEY_ENTER:
		SceneManager::SubmitChangeScene(new BaseScene1());
		break;
	}
}