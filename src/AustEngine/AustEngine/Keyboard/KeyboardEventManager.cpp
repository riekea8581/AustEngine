#include "KeyboardEventManager.h"
#include "../Game Object/Inputable.h"
#include "../Game Object/Attorneys/InputableAttorney.h"

void KeyboardEventManager::ProcessEvents()
{
	for (EventIterator it = keyList.begin(); it != keyList.end(); it++)
	{
		(*it).second->ProcessEvents();
	}
}

void KeyboardEventManager::Register(Inputable * i, AZUL_KEY k, EVENT_TYPE e, Inputable::InputIterator inputIt)
{
	EventIterator it = keyList.find(keyPair(k, e));
	if (it == keyList.end())
	{
		KeyEventManager * km = new KeyEventManager(k);
		it = keyList.insert(keyList.end(), std::pair<keyPair, KeyEventManager *>(keyPair(k, e), km));
	}
	InputableAttorney::InputIteratorFun::setIterator(i, inputIt, it);
	(*it).second->Register(i, e);
}

void KeyboardEventManager::Deregister(Inputable * i, EVENT_TYPE e, Inputable::InputIterator inputIt)
{
	EventIterator it = InputableAttorney::InputIteratorFun::getIterator(i, inputIt);
	(*it).second->Deregister(i, e);
}

KeyboardEventManager::~KeyboardEventManager()
{
	for (EventIterator it = keyList.begin(); it != keyList.end(); it++)
	{
		delete (*it).second;
	}
}