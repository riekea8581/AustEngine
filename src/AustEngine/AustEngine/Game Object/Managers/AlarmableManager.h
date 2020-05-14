#pragma once

#include <map>

class Alarmable;

class AlarmableManager
{
public:
	enum ALARM_ID {ALARM_0, ALARM_1, ALARM_2 };
	static const int ALARM_NUMBER = 3;

	AlarmableManager() = default;
	AlarmableManager(const AlarmableManager&) = delete;
	AlarmableManager& operator=(const AlarmableManager&) = delete;
	~AlarmableManager() {};

	void Register(float f, Alarmable * a, ALARM_ID id);
	void Deregister(Alarmable * a, ALARM_ID id);
	float GetTime(Alarmable * a, ALARM_ID id);
	void ProcessElements();

private:
	friend class AlarmableManagerAttorney;

	typedef std::pair<Alarmable*, ALARM_ID> AlarmEvent;
	typedef std::multimap<float, AlarmEvent> StorageList;
	typedef StorageList::iterator StorageIterator; 
	StorageList storageList;
};