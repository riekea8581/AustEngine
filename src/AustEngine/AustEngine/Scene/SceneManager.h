#pragma once

#include "Scene.h"
#include "SceneNull.h"
#include "Commands\SceneNullCommand.h"
#include "Commands\SceneChangeCommand.h"

class SceneManager
{
private:
	friend class SceneManagerAttorney;
	
	static SceneManager * ptrInstance;

	SceneManager()
		:activeCmd(&nullCmd), currentScene(new SceneNull) {};
	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;
	~SceneManager() {};
	
	static SceneManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new SceneManager;
		return *ptrInstance;
	}

	bool recreate;
	Scene * currentScene;
	SceneNullCommand nullCmd;
	SceneChangeCommand changeCmd;
	SceneCommand * activeCmd;
	
	void privSetStartScene(Scene *s) { currentScene = s; };
	void privInitStartScene();
	void privUpdate();
	void privDraw();
	Scene * privGetCurrentScene() { return currentScene; };
	void privSubmitChangeScene(Scene *s);
	
	void ChangeScene(Scene *s);
	static void Delete();
public:
	/// \brief Submits a command to change to a certain scene on game start.
	/// 
	/// \ingroup SCENEEVENTS
	/// 
	/// This function is meant to be called specifically when the game is started. It will determine what scene is
	/// loaded first. As of now, this function is technically redundant since the engine automatically sets the start
	/// scene to a null scene, then lets the user change scene in the LoadResources() function. However, this function
	/// is still here, to be used with caution.
	/// \par Example:
	/// 
	/// The following example depicts the "BaseScene" start scene being set in AustEngine::AustInitialize().
	///
	/// \code
	/// 
	/// void AustEngine::AustInitialize()
	/// {
	///		SetStartScene(new BaseScene());
	/// }
	/// \endcode
	static void SetStartScene(Scene *s) { Instance().privSetStartScene(s); };
	/// \brief Returns a pointer to the currently active scene.
	/// 
	/// \ingroup SCENEEVENTS
	/// 
	/// This function gives the calling object access to the current scene. This is important because the scene
	/// has access to important pointers, like the current camera, the orthographic camera, and the current terrain.
	/// Any function that wishes to find these pointers will need to do so through getting the current scene, as
	/// demonstrated in the sample code below.
	///
	/// \par Example:
	/// 
	/// The following example depicts an object getting the current camera through the GetCurrentScene function.
	///
	/// \code
	/// 
	/// void Player::Initialize()
	/// {
	///		myCamera = SceneManager::GetCurrentScene()->getCamera();
	/// }
	/// \endcode
	static Scene * GetCurrentScene() { return Instance().privGetCurrentScene(); };
	/// \brief Submits a command to change to a new scene on the next frame.
	/// 
	/// \ingroup SCENEEVENTS
	/// 
	/// When it comes time for the current scene to be changed, an object can call the SubmitChangeScene() function.
	/// This will not immediately change the scene, but it will signal to the scene manager to change Scene at the
	/// earliest opportunity (i.e. the next frame). A new scene must be provided to change to, but after this is done,
	/// the engine will auto-delete the given scene, so the user does not need to worry about this.
	/// 
	/// \par Example:
	/// 
	/// The following example depicts an Enemy Manager changing to the Level2 scene when all enemies are defeated.
	///
	/// \code
	/// 
	/// void EnemyManager::Update()
	/// {
	///		if(EnemyCount == 0)
	///		{
	///			SceneManager::SubmitChangeScene(new Level2Scene());
	///		}
	/// }
	/// \endcode
	static void SubmitChangeScene(Scene *s) { Instance().privSubmitChangeScene(s); };
	/// \brief Indicates to the SceneManager that, when building a scene, it should be recreated rather than being
	/// initialized normally.
	/// 
	/// \ingroup STOREEVENTS
	/// 
	/// This function must be called in the StorableManager::RecreateScene() function when a new scene is loaded. The
	/// puepose is to set a bool within the engine that denotes that when the Scene is initialized, it should be done
	/// through the Scene::Recreate() function and not the Scene::Initialize() function.

	///
	/// \par Example:
	/// 
	/// The following example depicts the StorableManager::RecreateScene() function properly using the SetRecreate() function.
	///
	/// \code
	/// 
	/// void StorableManager::privRecreateScene()
	/// {
	///		myCamera = SceneManager::GetCurrentScene()->getCamera();
	/// }
	/// \endcode
	static void SetRecreate() { Instance().recreate = true; };
};