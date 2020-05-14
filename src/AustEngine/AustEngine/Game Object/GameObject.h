#pragma once
#include "Drawable.h"
#include "Updatable.h"
#include "Alarmable.h"
#include "Inputable.h"
#include "Collidable.h"
#include "AzulCore.h"

class SceneEnterCommand;
class SceneExitCommand;

class GameObject: public Drawable, public Updatable, public Alarmable, public Inputable, public Collidable, public Align16
{
	friend class GameObjectAttorney;
public:
	GameObject();
	GameObject(const GameObject&) = delete;
	GameObject& operator=(const GameObject&) = delete;
	virtual ~GameObject();
protected:
	/// \brief Called by a game object when it is initialized and ready to be loaded into the active scene.
	/// 
	/// \ingroup GAMEOBJECTEVENTS
	/// 
	/// Generally, before loading into a scene, a game object will need to have its local variables initialized.
	/// Examples of this could include position, rotation, scale, health, and more. Either in the constructor or
	/// (more likely) in in Initialize function, the game object will need to set these variables. Once these
	/// variables are set, SubmitEntry() can be called and the game object will enter the active scene at the
	/// beginning of the next scene. Note that scene entry/exit is only necessary if a game object will be entering
	/// or exiting a scene outside of when that scene is initialized/ended.
	/// 
	/// \par Example:
	/// 
	/// The following example depicts an Initialize function that sets a game object's position and direction
	/// vectors before submitting that object to be entered into the scene.
	/// 
	/// \code
	/// 
	/// void Bullet::Initialize(Vect v1, Vect v2)
	/// {
	///		BulletPos = v1;
	///		BulletDir = v2;
	///		SubmitEntry();
	/// }
	/// \endcode
	void SubmitEntry();
	/// \brief Called by a game object when it is ready to be removed from the active scene.
	/// 
	/// \ingroup GAMEOBJECTEVENTS
	/// 
	/// Once a game object is "destroyed" or despawned, it no longer needs to be in the active scene. This function
	/// should be called when this happens, and the game object will enter the active scene at the beginning of
	/// the next scene. Note that scene entry/exit is only necessary if a game object will be entering
	/// or exiting a scene outside of when that scene is initialized/ended.
	/// 
	/// \par Example:
	/// 
	/// The following example depicts a game object that will remove itself from an active scene when a set alarm
	/// is triggered.
	/// 
	/// \code
	/// 
	/// void Object::Alarm0()
	/// {
	///		SubmitExit();
	/// }
	/// \endcode
	void SubmitExit();

	// get/set functions for children
	/// \brief Shortcut to get the current scene's active camera.
	/// 
	/// \ingroup GAMEOBJECTEVENTS
	/// 
	/// Should a game object need access to the current scene's camera (most likely to update the camera position),
	/// the GameObject::getCamera shortcut is a shortcut that will allow the object to quickly obtain a pointer to
	/// the active camera.
	/// 
	/// \par Example:
	/// 
	/// The following example depicts the getCamera function being used to store the active camera in a local
	/// camera pointer.
	/// 
	/// \code
	/// 
	/// void Object::Update()
	/// {
	///		myCamera = getCamera();
	/// }
	/// \endcode
	Camera * getCamera() { return SceneAttorney::SceneGetMgr::GetCamMgr()->getCamera(); };
	TerrainObject * getTerrain() { return SceneAttorney::SceneGetMgr::GetTerrainMgr()->getTerrain(); };
private:
	RegState state;

	SceneEnterCommand * enterCommand;
	SceneExitCommand * exitCommand;

	bool pendingExit;
	
	/// \brief Called by a game object on the frame in which it enters the active scene.
	/// 
	/// \ingroup GAMEOBJECTEVENTS
	/// 
	/// A call to GameObject::SceneEntry should always accompany a call to GameObject::SubmitEntry. This function
	/// is called on the frame after SubmitEntry is called, and it contains any functions that need to be called the
	/// moment the GameObject enters the scene. This includes registration for any parent classes of the game object
	/// class (Drawable, Updatable, Inputable, and Collidable, but NOT Alarmable unless an alarm needs to be set
	/// upon scene entry) that the game object will need to access.
	/// 
	/// \par Example:
	/// 
	/// The following example depicts a SceneEntry function that registers all parent classes of the GameObject
	/// class upon scene entry, excluding Alarmable.
	/// 
	/// \code
	/// 
	/// void Object::SceneEntry()
	/// {
	///		Updatable::SubmitSceneRegistration();
	///		Drawable::SubmitSceneRegistration();
	///		Inputable::SubmitSceneRegistration(AZUL_KEY::KEY_ENTER, KEY_PRESS);
	///		SubmitCollisionRegistration();
	/// }
	/// \endcode
	virtual void SceneEntry() {};
	/// \brief Called by a game object on the frame in which it exits the active scene.
	/// 
	/// \ingroup GAMEOBJECTEVENTS
	/// 
	/// A call to GameObject::SceneExit should always accompany a call to GameObject::SubmitExit. This function
	/// is called on the frame after SubmitExit is called, and it contains any functions that need to be called the
	/// moment the GameObject exits the scene. This includes deregistration for any parent classes of the game object
	/// class (Drawable, Updatable, Inputable, and Collidable) that were set upon scene entry.
	/// 
	/// \par Example:
	/// 
	/// The following example depicts a SceneExit function that deregisters all parent classes of the GameObject
	/// class upon scene exit, excluding Alarmable.
	/// 
	/// \code
	/// 
	/// void Object::SceneEntry()
	/// {
	///		Updatable::SubmitSceneDeregistration();
	///		Drawable::SubmitSceneDeregistration();
	///		Inputable::SubmitSceneDeregistration(AZUL_KEY::KEY_ENTER, KEY_PRESS);
	///		SubmitCollisionDeregistration();
	/// }
	/// \endcode
	virtual void SceneExit() {};
	void ConnectToScene();
	void DisconnectFromScene();
};