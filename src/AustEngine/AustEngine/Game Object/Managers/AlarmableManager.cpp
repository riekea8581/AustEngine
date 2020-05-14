#include "AlarmableManager.h"
#include "../Alarmable.h"
#include "../Attorneys/AlarmableAttorney.h"
#include "../../Time Manager/TimeManager.h"

void AlarmableManager::ProcessElements()
{
	StorageIterator it = storageList.begin();
	while( it != storageList.end())
	{
		if ((*it).first <= TimeManager::GetTotalTime())
		{
			AlarmableAttorney::AlarmGameLoop::TriggerAlarm((*it).second.first, (*it).second.second);
			StorageIterator tmp = it;
			it++;
			this->Deregister((*tmp).second.first, (*tmp).second.second);
		}
		else return;
	}
}

void AlarmableManager::Register(float f, Alarmable * a, ALARM_ID id)
{
	float time = f + TimeManager::GetTotalTime();
	AlarmableAttorney::AlarmGameLoop::setRef(a, storageList.insert(std::pair<float, AlarmEvent>(time, AlarmEvent(a, id))), id);
}

void AlarmableManager::Deregister(Alarmable * a, ALARM_ID id)
{
	storageList.erase(AlarmableAttorney::AlarmGameLoop::getRef(a, id));
}

float AlarmableManager::GetTime(Alarmable * a, ALARM_ID id)
{
	return (*AlarmableAttorney::AlarmGameLoop::getRef(a, id)).first - TimeManager::GetTotalTime();
}