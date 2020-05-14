#include "UnpauseHack.h"
#include "..\AustEngine\Storable\StorableManager.h"

UnpauseHack::UnpauseHack()
{
	Inputable::SubmitSceneRegistration(KEY_ENTER, KEY_PRESS);
	Inputable::SubmitSceneRegistration(KEY_BACKSPACE, KEY_PRESS);
}

void UnpauseHack::KeyPressed(AZUL_KEY k)
{
	switch (k)
	{
	case AZUL_KEY::KEY_ENTER:
		StorableManager::RecreateScene();
		break;
	case AZUL_KEY::KEY_BACKSPACE:
		StorableManager::WriteToFile();
		break;
	}
}