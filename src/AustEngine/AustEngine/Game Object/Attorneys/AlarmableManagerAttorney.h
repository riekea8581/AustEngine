#pragma once

#include "../Alarmable.h"
#include "../Managers/AlarmableManager.h"

class AlarmableManagerAttorney
{
	friend class AlarmableAttorney;
	friend class Alarmable;
private:
	typedef AlarmableManager::StorageIterator StorageIterator;
};