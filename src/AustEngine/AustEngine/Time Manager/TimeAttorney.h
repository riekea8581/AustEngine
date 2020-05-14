#pragma once

#include "TimeManager.h"

class TimeAttorney
{
	friend class AustEngine;
private:
	static void CalculateTime() { TimeManager::Instance().privCalculateTime(); };
	static void Delete() { TimeManager::Instance().privDelete(); };
};