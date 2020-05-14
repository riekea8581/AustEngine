#pragma once

#include "Managers\AlarmableManager.h"
#include "Attorneys\AlarmableManagerAttorney.h"
#include "RegState.h"

class AlarmRegistrationCommand;
class AlarmDeregistrationCommand;

class Alarmable
{
	friend class AlarmableAttorney;
public:
	Alarmable();
	Alarmable(const Alarmable&) = delete;
	Alarmable& operator=(const Alarmable&) = delete;
	virtual ~Alarmable();

private:
	struct RegistrationData
	{
		AlarmableManagerAttorney::StorageIterator myRef;
		RegState state;
		AlarmRegistrationCommand * regCommand;
		AlarmDeregistrationCommand * deregCommand;
	};

	RegistrationData RegData[AlarmableManager::ALARM_NUMBER];

	void SceneRegistration(float f, AlarmableManager::ALARM_ID id);
	void SceneDeregistration(AlarmableManager::ALARM_ID id);
	
	void TriggerAlarm(AlarmableManager::ALARM_ID id);

	/// \brief A function that is called once the corresponding alarm (in this case Alarm 0) is triggered.
	/// 
	/// \ingroup ALARMEVENTS
	/// 
	/// The Alarm0() function is an empty virtual function intended to be overridden by any game object that
	/// wishes to implement an alarm. The actual contents of the Alarm0 function will vary wildly depending on
	/// what the game object's alarm is meant to do. Note that the Alarm1() and Alarm2() functions are implemented
	/// in the same way, allowing a single game object to use up to three alarms.
	/// 
	/// \par Example:
	/// 
	/// The following example depicts an Alarm that will set itself to go off again in three seconds once triggered.
	///
	/// \code
	/// 
	/// void Object::Alarm0()
	/// {
	///		Alarmable::SubmitSceneRegistration(0, 3);
	/// }
	/// \endcode
	virtual void Alarm0() {};
	virtual void Alarm1() {};
	virtual void Alarm2() {};

	AlarmableManagerAttorney::StorageIterator getRef(AlarmableManager::ALARM_ID id) { return RegData[id].myRef; };
	void setRef(AlarmableManagerAttorney::StorageIterator it, AlarmableManager::ALARM_ID id) { RegData[id].myRef = it; };

protected:
	/// \brief Called by a game object to set an alarm that will go off at the given time.
	/// 
	/// \ingroup ALARMEVENTS
	/// 
	/// In order to set an alarm, Alarmable::SubmitSceneRegistration must be called with an Alarm ID parameter
	/// and a Time parameter. The Alarm ID parameter determines which alarm (Alarms 0 through 2 are available)
	/// will be set, and the Time parameter determines when the alarm will go off (in seconds). When the alarm
	/// is triggered, the corresponding Alarm() function goes off.
	/// 
	/// \par Example:
	/// 
	/// The following example depicts a SceneEntry function that sets Alarm 1 to go off in 3 seconds.
	///
	/// \code
	/// 
	/// void Object::SceneEntry()
	/// {
	///		Alarmable::SubmitSceneRegistration(1, 3);
	/// }
	/// \endcode
	void SubmitSceneRegistration(int id, float time);
	/// \brief Called by a game object to end an alarm prematurely.
	/// 
	/// \ingroup ALARMEVENTS
	/// 
	/// Should a game object need to cancel a set alarm without triggering the corresponding Alarm() function,
	/// it will need to call Alarmable::SubmitSceneDeregistration. This will cancel the alarm. This function
	/// takes an Alarm ID parameter that determines which alarm to cancel.
	/// 
	/// \par Example:
	/// 
	/// The following example depicts a SceneExit function that cancels alarm 0 upon being called.
	///
	/// \code
	/// 
	/// void Object::SceneExit()
	/// {
	///		Alarmable::SubmitSceneDeregistration(0);
	/// }
	/// \endcode
	void SubmitSceneDeregistration(int id);

	float CheckAlarm(AlarmableManager::ALARM_ID id);
	virtual void OverrideAlarm(AlarmableManager::ALARM_ID id, float f);
};