#include "Inputable.h"
#include "..\Scene\SceneManager.h"
#include "..\Scene\SceneAttorney.h"
#include "Commands\InputRegistrationCommand.h"
#include "Commands\InputDeregistrationCommand.h"
#include <cassert>

void Inputable::SceneRegistration(AZUL_KEY k, EVENT_TYPE e, Inputable::InputIterator it)
{
	SceneAttorney::SceneGetMgr::GetKeyboardMgr()->Register(this, k, e, it);
}

void Inputable::SceneDeregistration(EVENT_TYPE e, Inputable::InputIterator it)
{
	SceneAttorney::SceneGetMgr::GetKeyboardMgr()->Deregister(this, e, it);
}

void Inputable::SubmitSceneRegistration(AZUL_KEY k, EVENT_TYPE e)
{
	InputIterator it = RegData.find(keyPair(k, e));
	if (it == RegData.end())
	{
		it = RegData.insert(RegData.end(), std::pair<keyPair, RegistrationData>(keyPair(k, e), RegistrationData()));
		(*it).second.regCommand = new InputRegistrationCommand(this, k, e, it);
		(*it).second.deregCommand = new InputDeregistrationCommand(this, e, it);
		(*it).second.state = RegState::CURRENTLY_DEREGISTERED;
	}
	assert((*it).second.state == RegState::CURRENTLY_DEREGISTERED);
	(*it).second.state = RegState::CURRENTLY_REGISTERED;
	SceneAttorney::SceneGetMgr::SubmitCommand((*it).second.regCommand);
}

void Inputable::SubmitSceneDeregistration(AZUL_KEY k, EVENT_TYPE e)
{
	InputIterator it = RegData.find(keyPair(k, e));
	assert(it != RegData.end());
	assert((*it).second.state == RegState::CURRENTLY_REGISTERED);
	(*it).second.state = RegState::CURRENTLY_DEREGISTERED;
	SceneAttorney::SceneGetMgr::SubmitCommand((*it).second.deregCommand);
}

KeyEventManager::EventIterator Inputable::getRef()
{
	KeyEventManager::EventIterator tmp = myRefQueue.front();
	myRefQueue.pop();
	return tmp;
}

Inputable::~Inputable()
{
	for (InputIterator it = RegData.begin(); it != RegData.end(); it++)
	{
		delete (*it).second.regCommand;
		delete (*it).second.deregCommand;
	}
}