#pragma once

#include "../Inputable.h"

class InputableAttorney
{
public:
	class InputGameLoop
	{
		friend class KeyEventManager;
		static void KeyPressed(Inputable * i, AZUL_KEY k) { i->KeyPressed(k); };
		static void KeyReleased(Inputable * i, AZUL_KEY k) { i->KeyReleased(k); };
		static KeyEventManager::EventIterator getRef(Inputable * i) { return i->getRef(); };
		static void setRef(Inputable * i, KeyEventManager::EventIterator it) { i->setRef(it); };
	};
	class InputIteratorFun
	{
		friend class KeyboardEventManager; 
		static Inputable::EventList::iterator getIterator(Inputable * i, Inputable::InputIterator it) { return i->getIterator(it); };
		static void setIterator(Inputable * i, Inputable::InputIterator it, Inputable::EventList::iterator input) { i->setIterator(it, input); };
	};
	class InputRegistration
	{
		friend class InputRegistrationCommand;
		friend class InputDeregistrationCommand; 
		static void SceneRegistration(Inputable * i, AZUL_KEY k, EVENT_TYPE e, Inputable::InputIterator it) { i->SceneRegistration(k, e, it); };
		static void SceneDeregistration(Inputable * i, EVENT_TYPE e, Inputable::InputIterator it) { i->SceneDeregistration(e, it); };
	};
};