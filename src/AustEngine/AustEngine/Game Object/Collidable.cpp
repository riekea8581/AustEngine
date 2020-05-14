#include "Collidable.h"
#include "..\Collision\VolumeType.h"
#include "..\Collision\CollisionVolumeBSphere.h"
#include "..\Collision\CollisionVolumeAABB.h"
#include "..\Collision\CollisionVolumeOBB.h"
#include "Commands\CollideRegistrationCommand.h"
#include "Commands\CollideDeregistrationCommand.h"
#include "..\Scene\SceneAttorney.h"
#include <cassert>

Collidable::Collidable()
{
	defaultSphere = nullptr;
	myVolume = nullptr;
	state = RegState::CURRENTLY_DEREGISTERED;
	regCommand = new CollideRegistrationCommand(this);
	deregCommand = new CollideDeregistrationCommand(this);
}

void Collidable::SceneRegistration()
{
	assert(state == RegState::PENDING_REGISTRATION);
	SceneAttorney::SceneGetMgr::GetCollisionMgr()->GetColGroup(myID)->Register(this);
	state = RegState::CURRENTLY_REGISTERED;
}

void Collidable::SceneDeregistration()
{
	assert(state == RegState::PENDING_DEREGISTRATION);
	SceneAttorney::SceneGetMgr::GetCollisionMgr()->GetColGroup(myID)->Deregister(this);
	state = RegState::CURRENTLY_DEREGISTERED;
}

void Collidable::SubmitCollisionRegistration()
{
	assert(state == RegState::CURRENTLY_DEREGISTERED);
	SceneAttorney::SceneGetMgr::SubmitCommand(regCommand);
	state = RegState::PENDING_REGISTRATION;
}

void Collidable::SubmitCollisionDeregistration()
{
	assert(state == RegState::CURRENTLY_REGISTERED);
	SceneAttorney::SceneGetMgr::SubmitCommand(deregCommand);
	state = RegState::PENDING_DEREGISTRATION;
}

void Collidable::SetColliderModel(Model * mod, VolumeType vol)
{
	defaultSphere = new CollisionVolumeBSphere();
	pColModel = mod;
	switch (vol)
	{
	case VolumeType::BSPHERE:
		myVolume = defaultSphere;
		break;
	case VolumeType::AABB:
		myVolume = new CollisionVolumeAABB();
		break;
	case VolumeType::OBB:
		myVolume = new CollisionVolumeOBB();
		break;
	}
}

void Collidable::InitializeCollisionData(Matrix & mat)
{
	VolumeAttorney::InitializeData(*defaultSphere, pColModel, mat);
	VolumeAttorney::InitializeData(*myVolume, pColModel, mat);
}

void Collidable::UpdateCollisionData(Matrix & mat)
{
	VolumeAttorney::ComputeData(*defaultSphere, pColModel, mat);
	VolumeAttorney::ComputeData(*myVolume, pColModel, mat);
}

Collidable::~Collidable()
{
	if (defaultSphere != nullptr)
	{
		if (myVolume == defaultSphere) myVolume = nullptr;
		delete defaultSphere;
		defaultSphere = nullptr;
	}
	if (myVolume != nullptr)
	{
		delete myVolume;
		myVolume = nullptr;
	}
	delete regCommand;
	delete deregCommand;
}