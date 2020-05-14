#pragma once

#include "../Scene/SceneManager.h"

class SceneManagerAttorney
{
public:
	class SceneManagement
	{
	private:
		friend class AustEngine;
		static void InitStartScene() { SceneManager::Instance().privInitStartScene(); };
		static void Update() { SceneManager::Instance().privUpdate(); };
		static void Draw() { SceneManager::Instance().privDraw(); };
		static void Delete() { SceneManager::Delete(); };
	};
	class SceneRegistration
	{
	private:
		friend class SceneChangeCommand;
		static void ChangeScene(Scene * s) { SceneManager::Instance().ChangeScene(s); };
	};
};