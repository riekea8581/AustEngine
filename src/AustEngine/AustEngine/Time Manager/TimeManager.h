#pragma once

#include "AzulCore.h"
#include "FreezeTime.h"

class TimeManager
{
	friend class TimeAttorney;
private:
	static TimeManager* ptrInstance;

	TimeManager()
		:frameTime(0), totalTime(0) {};
	TimeManager(const TimeManager&) = delete;
	TimeManager& operator=(const TimeManager&) = delete;
	~TimeManager() {};

	static TimeManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new TimeManager;
		return *ptrInstance;
	}

	FreezeTime FrzTime;

	float frameTime;
	float totalTime;

	float privGetFrameTime() { return frameTime; };

	float privGetTotalTime() { return totalTime; };
	void privCalculateTime();
	void privDelete();

public:
	static float GetFrameTime() { return Instance().privGetFrameTime(); };
	static float GetTotalTime() { return Instance().privGetTotalTime(); };
};