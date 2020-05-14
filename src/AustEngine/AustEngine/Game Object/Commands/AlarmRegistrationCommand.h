#pragma once

#include "Command.h"
#include "../Alarmable.h"
#include "../Attorneys/AlarmableAttorney.h"

class AlarmRegistrationCommand : public Command
{
public:
	AlarmRegistrationCommand(Alarmable * a, AlarmableManager::ALARM_ID id) { target = a; alarmID = id; };
	virtual void execute() { AlarmableAttorney::AlarmRegistration::SceneRegistration(target, time, alarmID); };
	void setTime(float x) { time = x; };
	float getTime() { return time; };
private:
	float time;
	Alarmable * target;
	AlarmableManager::ALARM_ID alarmID;
};