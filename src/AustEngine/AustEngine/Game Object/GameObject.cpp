#include "GameObject.h"
#include "Commands\SceneEnterCommand.h"
#include "Commands\SceneExitCommand.h"
#include "..\Scene\SceneAttorney.h"

GameObject::GameObject()
{
	pendingExit = false;
	state = RegState::CURRENTLY_DEREGISTERED;
	enterCommand = new SceneEnterCommand(this);
	exitCommand = new SceneExitCommand(this);
}

void GameObject::SubmitEntry()
{
	assert(state == RegState::CURRENTLY_DEREGISTERED);
	SceneAttorney::SceneGetMgr::SubmitCommand(enterCommand);
	state = RegState::PENDING_REGISTRATION;
}

void GameObject::SubmitExit()
{
	if (!pendingExit)
	{
		assert(state == RegState::CURRENTLY_REGISTERED);
		SceneAttorney::SceneGetMgr::SubmitCommand(exitCommand);
		state = RegState::PENDING_DEREGISTRATION;
		pendingExit = true;
	}
}

void GameObject::ConnectToScene()
{
	assert(state == RegState::PENDING_REGISTRATION);
	state = RegState::CURRENTLY_REGISTERED;
	this->SceneEntry();
}

void GameObject::DisconnectFromScene()
{
	assert(state == RegState::PENDING_DEREGISTRATION);
	state = RegState::CURRENTLY_DEREGISTERED;
	this->SceneExit();
	pendingExit = false;
}

GameObject::~GameObject()
{
	delete enterCommand;
	delete exitCommand;
}