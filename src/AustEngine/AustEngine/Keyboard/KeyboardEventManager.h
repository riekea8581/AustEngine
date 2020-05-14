#pragma once

#include "AzulCore.h"
#include "../Game Object/EventType.h"
#include "../Game Object/Inputable.h"
#include <map>

class KeyEventManager;

class KeyboardEventManager
{
private:
	typedef std::pair<AZUL_KEY, EVENT_TYPE> keyPair;
	typedef std::map<keyPair, KeyEventManager * > EventList;

	EventList keyList;
public:
	typedef EventList::iterator EventIterator;

	KeyboardEventManager() = default;
	KeyboardEventManager(const KeyboardEventManager&) = delete;
	KeyboardEventManager& operator=(const KeyboardEventManager&) = delete;
	~KeyboardEventManager();

	// These being public should be OK since the user will not have access to the keyboard event manager

	void ProcessEvents();

	void Register(Inputable * i, AZUL_KEY k, EVENT_TYPE e, Inputable::InputIterator inputIt);
	void Deregister(Inputable * i, EVENT_TYPE e, Inputable::InputIterator inputIt);
};