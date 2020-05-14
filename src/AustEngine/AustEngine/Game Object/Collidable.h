#pragma once

#include "Managers\CollisionManager.h"
#include "Managers\CollidableGroup.h"
#include "..\Collision\CollisionVolume.h"
#include "..\Collision\Attorneys\VolumeAttorney.h"
#include "..\Scene\SceneAttorney.h"
#include "RegState.h"

class CollideRegistrationCommand;
class CollideDeregistrationCommand;
enum VolumeType;

class Collidable
{
	friend class CollisionAttorney;
public:
	Collidable();
	Collidable(const Collidable&) = delete;
	Collidable& operator=(const Collidable&) = delete;
	virtual ~Collidable();

private:
	CollisionManager::PWTypeID myID = CollisionManager::PWID_UNDEFINED;

	RegState state;

	CollideRegistrationCommand * regCommand;
	CollideDeregistrationCommand * deregCommand;

	CollisionVolume * myVolume;
	CollisionVolumeBSphere * defaultSphere;
	Model * pColModel;

	virtual void CollisionTerrain() {};

	void SceneRegistration();
	void SceneDeregistration();

	CollidableGroup::StorageIterator myRef;
	CollidableGroup::StorageIterator getRef() { return myRef; };
	void setRef(CollidableGroup::StorageIterator it) { myRef = it; };

protected:
	template <typename C> void SetCollidableGroup()
	{
		myID = SceneAttorney::SceneGetMgr::GetCollisionMgr()->GetTypeID<C>();
	}
	/// \brief A function that is called to allow collision checking on an object instance.
	/// 
	/// \ingroup COLLISIONEVENTS
	/// 
	/// Once this function is called, the calling instance of an object will check for collision with all valid
	/// collidable objects as dictated by the Scene::SetCollisionPair() and Scene::SetCollisionSelf classes.
	/// This check will be done once per frame, which can be time-consuming if used excessively, so only
	/// call this function when collision is necessary.
    ///
	/// \par Example:
	/// 
	/// The following example depicts an object that permits collision checking in its constructor. Note that this
	/// is bad practice; usually it should instead be done in the SceneEntry function so that collision can easily
	/// be turned on and off as the object enters & exits the scene.
	///
	/// \code
	/// 
	/// Object::Object()
	/// {
	///		SubmitCollisionRegistration();
	/// }
	/// \endcode
	void SubmitCollisionRegistration();
	/// \brief A function that is called to disable collision checking on an object instance.
	/// 
	/// \ingroup COLLISIONEVENTS
	/// 
	/// Once this function is called, the calling instance of an object will stop checking for collision 
	/// with all valid collidable objects. Note that all other GameObject functionality will proceed as usual
	/// unless disabled saparately.
	///
	/// \par Example:
	/// 
	/// The following example depicts an object that permits collision checking in its destructor. Note that this
	/// is bad practice; usually it should instead be done in the SceneExit function so that collision can easily
	/// be turned on and off as the object enters & exits the scene.
	///
	/// \code
	/// 
	/// Object::~Object()
	/// {
	///		SubmitCollisionDeregistration();
	/// }
	/// \endcode
	void SubmitCollisionDeregistration();

	const CollisionVolume & GetVolume() { return *myVolume; };
	const CollisionVolumeBSphere & GetSphere() { return *defaultSphere; };
	/// \brief A function that is called to set what world matrix will be used for collision calculations.
	/// 
	/// \ingroup COLLISIONEVENTS
	/// 
	/// One necessary aspect of collision checking is a model representing the space an object takes up.
	/// This function is used to pass in a game object's model for use in collision calculations. Generally
	/// a game object's model should not change often, but in case it does, the new model will need to be
	/// passed in again.
	///
	/// \par Example:
	/// 
	/// The following example depicts an object that passes in its model once during the constructor. If the
	/// model is never going to change, this is all that actually needs to be done.
	/// 
	/// \code
	/// 
	/// void Player::Player()
	/// {
	///     SetColliderModel(myModel);
	/// }
	/// \endcode
	void SetColliderModel(Model * mod, VolumeType vol);
	
	void InitializeCollisionData(Matrix & mat);
	/// \brief A function that is called to set what world matrix will be used for collision calculations.
	/// 
	/// \ingroup COLLISIONEVENTS
	/// 
	/// One necessary aspect of collision checking is a world matrix representing the location of an object.
	/// This function is used to pass in a game object's world matrix for use in collision calculations.
	/// Whenever said world matrix changes, the world matrix will need to be passed in again.
	///
	/// \par Example:
	/// 
	/// The following example depicts an object that passes in its world matrix every frame in its Update()
	/// function. Note that making a temporary variable like this isn't necessary, and is only meant to show
	/// that the matrix is being gotten from a local variable of the object.
	/// 
	/// \code
	/// 
	/// void Player::Update()
	/// {
	///		Matrix m = this->WorldMatrix;
	///     UpdateCollisionData(m);
	/// }
	/// \endcode
	void UpdateCollisionData(Matrix & mat);

	void SendColCommand(Vect col) { VolumeAttorney::SendColCommand(*myVolume, col); };
};