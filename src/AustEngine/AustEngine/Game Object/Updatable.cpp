#include "Updatable.h"
#include "Commands\UpdateRegistrationCommand.h"
#include "Commands\UpdateDeregistrationCommand.h"
#include "..\Scene\SceneAttorney.h"
#include <cassert>

Updatable::Updatable()
{
	state = RegState::CURRENTLY_DEREGISTERED;
	regCommand = new UpdateRegistrationCommand(this);
	deregCommand = new UpdateDeregistrationCommand(this);
}

void Updatable::SceneRegistration()
{
	assert(state == RegState::PENDING_REGISTRATION);
	SceneAttorney::SceneGetMgr::GetUpdateMgr()->Register(this);
	state = RegState::CURRENTLY_REGISTERED;
}

void Updatable::SceneDeregistration()
{
	assert(state == RegState::PENDING_DEREGISTRATION);
	SceneAttorney::SceneGetMgr::GetUpdateMgr()->Deregister(this);
	state = RegState::CURRENTLY_DEREGISTERED;
}

void Updatable::SubmitSceneRegistration()
{
	assert(state == RegState::CURRENTLY_DEREGISTERED); 
	SceneAttorney::SceneGetMgr::SubmitCommand(regCommand);
	state = RegState::PENDING_REGISTRATION;
}

void Updatable::SubmitSceneDeregistration()
{
	assert(state == RegState::CURRENTLY_REGISTERED);
	SceneAttorney::SceneGetMgr::SubmitCommand(deregCommand);
	state = RegState::PENDING_DEREGISTRATION;
}

Updatable::~Updatable()
{
	delete regCommand;
	delete deregCommand;
}