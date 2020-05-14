#pragma once

#include "../Alarmable.h"
#include "../Attorneys/AlarmableAttorney.h"

class AlarmDeregistrationCommand : public Command
{
public:
	AlarmDeregistrationCommand(Alarmable * a, AlarmableManager::ALARM_ID id) { target = a; alarmID = id; };
	virtual void execute() { AlarmableAttorney::AlarmRegistration::SceneDeregistration(target, alarmID); };
private:
	Alarmable * target;
	AlarmableManager::ALARM_ID alarmID;
};