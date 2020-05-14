#pragma once

#include "..\Scene\SceneManager.h"
#include "Managers\UpdatableManager.h"
#include "RegState.h"

class UpdateRegistrationCommand;
class UpdateDeregistrationCommand;

class Updatable
{
public:
	Updatable();
	Updatable(const Updatable&) = delete;
	Updatable& operator=(const Updatable&) = delete;
	virtual ~Updatable();

protected:
	/// \brief Called by a game object to indicate that it wishes to be updated each frame.
	/// 
	/// \ingroup UPDATEEVENTS
	/// 
	/// A game object must indicate that it wishes to be updated by the active scene each frame in order for its
	/// Update function to be called. This is done using the SubmitSceneRegistration function. Generally this
	/// function is called either upon creation or (more likely) upon scene entry.
	/// 
	/// \par Example:
	/// 
	/// The following example depicts a SceneEntry function that ONLY calls for the given object to be updated,
	/// not drawn or any other game object functionality.
	///
	/// \code
	/// 
	/// void Object::SceneEntry()
	/// {
	///		Updatable::SubmitSceneRegistration();
	/// }
	/// \endcode
	void SubmitSceneRegistration();
	/// \brief Called by a game object to indicate that it no longer wishes to be updated each frame.
	/// 
	/// \ingroup UPDATEEVENTS
	/// 
	/// A game object must indicate that it wishes to stop being updated by the active scene each frame,
	/// or its Update function will continue to be called. This is done using the SubmitSceneDeregistration
	/// function. Generally this function is called upon scene exit.
	/// 
	/// \par Example:
	/// 
	/// The following example depicts a SceneExit function that ONLY calls for the given object to stop being
	/// updated, not drawn or any other game object functionality.
	///
	/// \code
	/// 
	/// void Object::SceneExit()
	/// {
	///		Updatable::SubmitSceneDeregistration();
	/// }
	/// \endcode
	void SubmitSceneDeregistration();
private:
	friend class UpdatableAttorney;

	RegState state;

	UpdateRegistrationCommand * regCommand;
	UpdateDeregistrationCommand * deregCommand;

	/// \brief A game object function that will be called once per frame for as long as the given object is
	/// registered to receive updates.
	/// 
	/// \ingroup UPDATEEVENTS
	/// 
	/// The Updatable::Update function is an empty virtual function intended to be overridden by any game
	/// object that wishes to be updated in a scene. The implementation of the Update function will differ
	/// wildly based on what exactly the given object is meant to do each frame.
	/// 
	/// \par Example:
	/// 
	/// The following example depicts a very simple Update function that causes a given game object to increment
	/// its health by 1 every 100 frames.
	///
	/// \code
	/// 
	/// void Boss::Update()
	/// {
	///		health += 0.01f;
	/// }
	/// \endcode
	virtual void Update() {};
	
	void SceneRegistration();
	void SceneDeregistration();

	UpdatableManager::StorageIterator myRef;
	UpdatableManager::StorageIterator getRef() { return myRef; };
	void setRef(UpdatableManager::StorageIterator it) { myRef = it; };
};