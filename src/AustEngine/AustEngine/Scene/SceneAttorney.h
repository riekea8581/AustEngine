#pragma once

#include "Scene.h"
#include "SceneManager.h"

class SceneAttorney
{
public:
	class SceneGameLoop
	{
	private:
		friend class AustEngine;
		friend class SceneManager;
		static void Initialize(Scene * s) { s->Initialize(); };
		static void Recreate(Scene * s) { s->Recreate(); };
		static void SceneEnd(Scene * s) { s->SceneEnd(); };
		static void Update(Scene * s) { s->Update(); };
		static void Draw(Scene * s) { s->Draw(); };
	};
	class SceneGetMgr
	{
	private:
		friend class GameObject;
		friend class Updatable;
		friend class Drawable;
		friend class Alarmable;
		friend class Inputable;
		friend class Collidable;
		friend class Sprite;
		static UpdatableManager* GetUpdateMgr() { return &(SceneManager::GetCurrentScene()->updateMgr); };
		static DrawableManager* GetDrawMgr() { return &(SceneManager::GetCurrentScene()->drawMgr); };
		static AlarmableManager* GetAlarmMgr() { return &(SceneManager::GetCurrentScene()->alarmMgr); };
		static KeyboardEventManager* GetKeyboardMgr() { return &(SceneManager::GetCurrentScene()->keyboardMgr); };
		static CollisionManager* GetCollisionMgr() { return &(SceneManager::GetCurrentScene()->collideMgr); };
		static CameraManager* GetCamMgr() { return &(SceneManager::GetCurrentScene()->camMgr); };
		static TerrainManager* GetTerrainMgr() { return &(SceneManager::GetCurrentScene()->terrainMgr); };
		static void SubmitCommand(Command *cmd) { SceneManager::GetCurrentScene()->SubmitCommand(cmd); };
	};
};