#pragma once

#include "..\Keyboard\KeyEventManager.h"
#include "AzulCore.h"
#include "RegState.h"
#include "EventType.h"
#include <map>
#include <queue>

class InputRegistrationCommand;
class InputDeregistrationCommand;

class Inputable
{
	friend class InputableAttorney; 
private:
	typedef std::pair<AZUL_KEY, EVENT_TYPE> keyPair;
	typedef std::map<keyPair, KeyEventManager * > EventList;
	struct RegistrationData
	{
		RegState state;
		InputRegistrationCommand * regCommand;
		InputDeregistrationCommand * deregCommand;
		EventList::iterator iterator;
	};

	typedef std::map<keyPair, RegistrationData> InputList;

public:
	Inputable() = default;
	Inputable(const Inputable&) = default;
	Inputable& operator=(const Inputable&) = default;
	virtual ~Inputable();

	typedef InputList::iterator InputIterator;

private:
	InputList RegData;

	/// \brief A function that is called once a key that the game object is tracking is pressed.
	/// 
	/// \ingroup INPUTEVENTS
	/// 
	/// The KeyPressed function is an empty virtual function intended to be overridden by any game object that
	/// wishes to track keyboard presses. The actual contents of the function will vary wildly depending on
	/// what the game object is meant to do when a key is pressed. Generally, if multiple keys are being tracked, a
	/// switch statement will be necessary to see which key is pressed.
	/// 
	/// \par Example:
	/// 
	/// The following example depicts an object that will increment its health when A is pressed and decrement its
	/// health when B is pressed.
	///
	/// \code
	/// 
	/// void Player::KeyPressed(AZUL_KEY k)
	/// {
	/// 	switch (k)
	/// 	{
	/// 	case AZUL_KEY::KEY_A:
	/// 		health += 1;
	/// 		break;
	/// 	case AZUL_KEY::KEY_B:
	/// 		health -= 1;
	/// 	}
	/// }
	/// \endcode
	virtual void KeyPressed(AZUL_KEY) {};
	/// \brief A function that is called once a key that the game object is tracking is released.
	/// 
	/// \ingroup INPUTEVENTS
	/// 
	/// The KeyReleased function is an empty virtual function intended to be overridden by any game object that
	/// wishes to track keyboard key releases. The actual contents of the function will vary wildly depending on
	/// what the game object is meant to do when a key is released. Generally, if multiple keys are being tracked, a
	/// switch statement will be necessary to see which key is pressed.
	/// 
	/// \par Example:
	/// 
	/// The following example depicts an object that will decrement its health when A is released and increment its
	/// health when B is released.
	///
	/// \code
	/// 
	/// void Player::KeyReleased(AZUL_KEY k)
	/// {
	/// 	switch (k)
	/// 	{
	/// 	case AZUL_KEY::KEY_A:
	/// 		health -= 1;
	/// 		break;
	/// 	case AZUL_KEY::KEY_B:
	/// 		health += 1;
	/// 	}
	/// }
	/// \endcode
	virtual void KeyReleased(AZUL_KEY) {};

	std::queue<KeyEventManager::EventIterator> myRefQueue;
	KeyEventManager::EventIterator getRef();
	void setRef(KeyEventManager::EventIterator it) { myRefQueue.push(it); };

	EventList::iterator getIterator(InputIterator it) { return (*it).second.iterator; };
	void setIterator(InputIterator it, EventList::iterator input) { (*it).second.iterator = input; };

protected:
	/// \brief Called by a game object to indicate that it wishes to be notified when a given key is pressed or released.
	/// 
	/// \ingroup INPUTEVENTS
	/// 
	/// A game object must indicate that it wishes to be notified when a given key is pressed. Once this function
	/// is called, the Inputable::KeyPressed function will be called every time the given key is pressed.
	/// Generally this function will be called upon scene entry. The function takes two parameters. The first
	/// parameter is an AZUL_KEY indicating what key to track. The second parameter should be either
	/// "KEY_PRESS" or "KEY_RELEASE" depending on which one the user wishes to track.
	/// 
	/// \par Example:
	/// 
	/// The following example depicts a SceneEntry function that calls for the given object to be notified when
	/// the Enter key is both pressed and released.
	///
	/// \code
	/// 
	/// void Object::SceneEntry()
	/// {
	///		Inputable::SubmitSceneRegistration(AZUL_KEY::KEY_ENTER, KEY_PRESS);
	///		Inputable::SubmitSceneRegistration(AZUL_KEY::KEY_ENTER, KEY_RELEASE);
	/// }
	/// \endcode
	void SubmitSceneRegistration(AZUL_KEY k, EVENT_TYPE e);
	/// \brief Called by a game object to indicate that it no longer wishes to be notified when a given key is
	/// pressed or released.
	/// 
	/// \ingroup INPUTEVENTS
	/// 
	/// A game object must indicate that it wishes to be notified when a given key is pressed. Once this function
	/// is called, the Inputable::KeyPressed function will be called every time the given key is pressed.
	/// Generally this function will be called upon scene entry. The function takes two parameters. The first
	/// parameter is an AZUL_KEY indicating what key to track. The second parameter should be either
	/// "KEY_PRESS" or "KEY_RELEASE" depending on which one the user wishes to track.
	/// 
	/// \par Example:
	/// 
	/// The following example depicts a SceneEntry function that calls for the given object to be notified when
	/// the Enter key is both pressed and released.
	///
	/// \code
	/// 
	/// void Object::SceneEntry()
	/// {
	///		Inputable::SubmitSceneRegistration(AZUL_KEY::KEY_ENTER, KEY_PRESS);
	///		Inputable::SubmitSceneRegistration(AZUL_KEY::KEY_ENTER, KEY_RELEASE);
	/// }
	/// \endcode
	void SubmitSceneDeregistration(AZUL_KEY k, EVENT_TYPE e); 

private:
	void SceneRegistration(AZUL_KEY k, EVENT_TYPE e, Inputable::InputIterator it);
	void SceneDeregistration(EVENT_TYPE e, Inputable::InputIterator it);
};