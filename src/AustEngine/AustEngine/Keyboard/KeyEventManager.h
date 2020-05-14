#pragma once

#include "AzulCore.h"
#include "../Game Object/EventType.h"
#include <list>

class Inputable;

class KeyEventManager
{
	private:
		typedef std::list< Inputable * > EventList;
		AZUL_KEY myKey;
		EventList pressList;
		EventList releaseList;

		bool lastFramePressed;
		bool firstFrame;
	public:
		typedef EventList::iterator EventIterator;
		
		KeyEventManager() = delete;
		KeyEventManager(AZUL_KEY k);
		KeyEventManager(const KeyEventManager&) = delete;
		KeyEventManager& operator=(const KeyEventManager&) = delete;
		~KeyEventManager() {};
	
		// These being public should be OK since the user should never access the key event manager
		void ProcessEvents();

		void Register(Inputable * i, EVENT_TYPE e);
		void Deregister(Inputable * i, EVENT_TYPE e);
};