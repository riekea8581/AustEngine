#pragma once

#include "../Alarmable.h"
#include "../Managers/AlarmableManager.h"
#include "AlarmableManagerAttorney.h"

class AlarmableAttorney
{
public:
	class AlarmGameLoop
	{
		friend class AlarmableManager;
		static void TriggerAlarm(Alarmable * a, AlarmableManager::ALARM_ID id) { a->TriggerAlarm(id); };
		static AlarmableManagerAttorney::StorageIterator getRef(Alarmable * a, AlarmableManager::ALARM_ID id) { return a->getRef(id); };
		static void setRef(Alarmable * a, AlarmableManagerAttorney::StorageIterator it, AlarmableManager::ALARM_ID id) { a->setRef(it, id); };
	};
	class AlarmRegistration
	{
		friend class AlarmRegistrationCommand;
		friend class AlarmDeregistrationCommand;
		static void SceneRegistration(Alarmable * a, float f, AlarmableManager::ALARM_ID id) { a->SceneRegistration(f, id); };
		static void SceneDeregistration(Alarmable * a, AlarmableManager::ALARM_ID id) { a->SceneDeregistration(id); };
	};
};