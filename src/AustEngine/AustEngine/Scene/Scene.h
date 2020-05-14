#pragma once

#include "../Game Object/Managers/UpdatableManager.h"
#include "../Game Object/Managers/DrawableManager.h"
#include "../Game Object/Managers/AlarmableManager.h"
#include "../Keyboard/KeyboardEventManager.h"
#include "../Game Object/Managers/CollisionManager.h"
#include "../Terrain/TerrainManager.h"
#include "../Game Object/EventType.h"
#include "SceneRegistrationBroker.h"
#include "../Camera Manager/CameraManager.h"
#include "../Collision/Attorneys/VisualizerAttorney.h"
#include "../Storable/StorableManager.h"

class Scene : public Align16
{
	friend class SceneAttorney;
public:
	Scene() = default;
	Scene(const Scene&) = delete;
	Scene& operator=(const Scene&) = delete;
	~Scene() {};

	Camera * getCamera();
	Camera * getOrthCamera();
	TerrainObject * getTerrain();
	void setTerrain(const char * tag);
protected:
	/// \brief Called by a scene in order to permit collision checking between two objects.
	/// 
	/// \ingroup COLLISIONEVENTS
	/// 
	/// Due to the way collision is handled in this engine, it is necessary for a scene to permit
	/// collision between two types of game objects within that scene. By calling this function, the
	/// user is giving the scene permission to check all objects of one type for collision with all objects
	/// of another type each frame. For each collision detected, both colliding objects will make a call to
	/// the appropriate Collision function.
	/// 
	/// \par Example:
	/// 
	/// The following example depicts a derived scene giving the engine permission to check collision between
	/// the player character and all enemy bullets. Both the player and the bullet will then be notified if a
	/// bullet strikes the player.
	/// 
	/// \code
	/// 
	/// SetCollisionPair<Player, EnemyBullet>();
	///
	/// \endcode
	template<typename C1, typename C2>
	void SetCollisionPair() { collideMgr.SetCollisionPair<C1, C2>(); };
	/// \brief Called by a scene in order to permit collision checking between multiple instances of the same object.
	/// 
	/// \ingroup COLLISIONEVENTS
	/// 
	/// Due to the way collision is handled in this engine, it is necessary for a scene to permit
	/// collision between game objects within that scene. By calling this function, the user is giving the
	/// scene permission to check all objects of one type for collision with all other objects of that same type
	/// each frame. For each collision detected, both colliding objects will make a call to the appropriate 
	/// Collision function.
	/// 
	/// \par Example:
	/// 
	/// The following example depicts a derived scene giving the engine permission to check collision between
	/// all enemy bullets. Both colliding bullets will then be notified if they collide with each other.
	/// 
	/// \code
	/// 
	/// SetCollisionSelf<EnemyBullet>();
	///
	/// \endcode
	template<typename C>
	void SetCollisionSelf() { collideMgr.SetCollisionSelf<C>(); };
	/// \brief Called by a scene in order to permit collision checking between an object and the scene's terrain.
	/// 
	/// \ingroup COLLISIONEVENTS
	/// 
	/// Due to the way collision is handled in this engine, it is necessary for a scene to permit
	/// collision between game objects within that scene. By calling this function, the user is giving the
	/// scene permission to check all objects of one type for collision with the singular terrain model held by
	/// the scene itself. For each collision detected, the object that collided with the terrain will call its
	/// own Collidable::CollisionTerrain() function.
	/// 
	/// \par Example:
	/// 
	/// The following example depicts a derived scene giving the engine permission to check collision between
	/// all enemy bullets and the scene's terrain.
	/// 
	/// \code
	/// 
	/// SetCollisionTerrain<EnemyBullet>();
	///
	/// \endcode
	template<typename C>
	void SetCollisionTerrain() { collideMgr.SetCollisionTerrain<C>(); };
private:
	UpdatableManager updateMgr;
	DrawableManager drawMgr;
	AlarmableManager alarmMgr;
	KeyboardEventManager keyboardMgr;
	CollisionManager collideMgr;
	SceneRegistrationBroker broker;
	CameraManager camMgr;
	TerrainManager terrainMgr;

	/// \brief Called when a scene is being loaded into the game. 
	///
	/// \ingroup SCENEEVENTS
	///
	/// This function is called at the beginning of a frame after SubmitChangeScene has been called.
	/// By default, this function does nothing; however when the user implements a scene, they should
	/// have the derived scene implement this function and execute all commands that need to be called
	/// when that scene is instantiated.
	///
	/// \par Example:
	///
	/// The following example depicts a derived Scene that uses its Initialize function to create two new
	/// game objects and allows them to collide with each other.
	///
	/// \code
	///
	/// void NewScene::Initialize()
	/// {
	///		object1 = new GameObject1();
	///		object2 = new GameObject2();
	///
	///		SetCollisionPair<GameObject1, GameObject2>();
	/// }
	/// \endcode
	virtual void Initialize() {};

	virtual void Recreate() {};
	/// \brief Called directly before a scene is deleted by the engine.
	/// 
	/// \ingroup SCENEEVENTS
	/// 
	/// This function is called on the currently active scene immediately before the engine changes scene,
	/// as well as immediately before the engine shuts down. By default, this function does nothing; any
	/// user-implemented scene should implement this function and execute any commands (notably deletion)
	/// that need to be called when a scene is deleted. For all intents and purposes, this function serves
	/// the same purpose as a destructor normally would.
	/// 
	/// \par Example:
	/// 
	/// The following example depicts a derived scene that uses its SceneEnd function to delete two game
	/// objects that were initialized at some point within the scene's life cycle.
	/// 
	/// \code
	/// 
	/// void NewScene::Terminate()
	/// {
	/// 	delete object1;
	/// 	delete object2;
	/// }
	/// \endcode
	virtual void SceneEnd() {};

	virtual void Update();
	virtual void Draw();

	void SubmitCommand(Command *cmd) { broker.addCommand(cmd); };
};