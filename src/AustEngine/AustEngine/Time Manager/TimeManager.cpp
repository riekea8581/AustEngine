#include "TimeManager.h"
#include "../EngineAttorney.h"

TimeManager * TimeManager::ptrInstance = NULL;

void TimeManager::privCalculateTime()
{
	//float tmp = EngineAttorney::EngineTime();
	float tmp = FrzTime.GetTimeInSeconds(EngineAttorney::AustTime::EngineTime());
	frameTime = tmp - totalTime;
	totalTime = tmp;
}

void TimeManager::privDelete()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}