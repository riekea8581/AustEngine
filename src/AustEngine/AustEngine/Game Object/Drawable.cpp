#include "Drawable.h"
#include "Commands\DrawRegistrationCommand.h"
#include "Commands\DrawDeregistrationCommand.h"
#include "..\Scene\SceneAttorney.h"
#include <cassert>

Drawable::Drawable()
{
	state = RegState::CURRENTLY_DEREGISTERED;
	regCommand = new DrawRegistrationCommand(this);
	deregCommand = new DrawDeregistrationCommand(this);
}

void Drawable::SceneRegistration()
{
	assert(state == RegState::PENDING_REGISTRATION);
	SceneAttorney::SceneGetMgr::GetDrawMgr()->Register(this);
	state = RegState::CURRENTLY_REGISTERED;
}

void Drawable::SceneDeregistration()
{
	assert(state == RegState::PENDING_DEREGISTRATION);
	SceneAttorney::SceneGetMgr::GetDrawMgr()->Deregister(this);
	state = RegState::CURRENTLY_DEREGISTERED;
}

void Drawable::SubmitSceneRegistration()
{
	if (state != RegState::CURRENTLY_DEREGISTERED)
	{
		assert(false);
	}
	//assert(state == RegState::CURRENTLY_DEREGISTERED);
	SceneAttorney::SceneGetMgr::SubmitCommand(regCommand);
	state = RegState::PENDING_REGISTRATION;
}

void Drawable::SubmitSceneDeregistration()
{
	assert(state == RegState::CURRENTLY_REGISTERED);
	SceneAttorney::SceneGetMgr::SubmitCommand(deregCommand);
	state = RegState::PENDING_DEREGISTRATION;
}

Drawable::~Drawable()
{
	delete regCommand;
	delete deregCommand;
}