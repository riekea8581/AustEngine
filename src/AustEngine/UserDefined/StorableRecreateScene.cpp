#include "..\AustEngine\Storable\StorableManager.h"
#include "..\UserFull\BaseScene1.h"
#include "..\UserFull\BaseScene2.h"
#include "..\UserFull\BaseScene3.h"
#include "..\AustEngine\Scene\SceneManager.h"

void StorableManager::privRecreateScene()
{
	char tmp[tagLength];
	memcpy(tmp, buffer, tagLength);
	if (strcmp(tmp, "Level1") == 0)
	{
		SceneManager::SubmitChangeScene(new BaseScene1());
		SceneManager::SetRecreate();
		return;
	}
	if (strcmp(tmp, "Level2") == 0)
	{
		SceneManager::SubmitChangeScene(new BaseScene2());
		SceneManager::SetRecreate();
		return;
	}
	if (strcmp(tmp, "Level3") == 0)
	{
		SceneManager::SubmitChangeScene(new BaseScene3());
		SceneManager::SetRecreate();
		return;
	}
}