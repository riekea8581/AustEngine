#include "AzulCore.h"
#include "SceneManager.h"
#include "SceneAttorney.h"

SceneManager * SceneManager::ptrInstance = nullptr;

void SceneManager::privInitStartScene()
{
	SceneAttorney::SceneGameLoop::Initialize(currentScene);
};

void SceneManager::privUpdate()
{
	activeCmd->Execute();
	SceneAttorney::SceneGameLoop::Update(currentScene);
};

void SceneManager::privDraw()
{
	SceneAttorney::SceneGameLoop::Draw(currentScene);
};

void SceneManager::privSubmitChangeScene(Scene * s)
{
	changeCmd.SetTarget(s);
	activeCmd = &changeCmd;
}

void SceneManager::ChangeScene(Scene * s)
{
	SceneAttorney::SceneGameLoop::SceneEnd(currentScene);
	delete currentScene;
	currentScene = s;
	if (recreate == true)
	{
		SceneAttorney::SceneGameLoop::Recreate(currentScene);
		recreate = false;
	}
	else SceneAttorney::SceneGameLoop::Initialize(currentScene);
	activeCmd = &nullCmd;
}

void SceneManager::Delete()
{
	delete GetCurrentScene();
	delete ptrInstance;
	ptrInstance = nullptr;
}