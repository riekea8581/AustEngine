#include "Alarmable.h"
#include "Commands/AlarmRegistrationCommand.h"
#include "Commands/AlarmDeregistrationCommand.h"
#include "../Scene/SceneManager.h"
#include "../Scene/SceneAttorney.h"
#include <cassert>

Alarmable::Alarmable()
{
	for (int i = 0; i < AlarmableManager::ALARM_NUMBER; i++)
	{
		RegData[i].state = RegState::CURRENTLY_DEREGISTERED;
		RegData[i].regCommand = new AlarmRegistrationCommand(this, AlarmableManager::ALARM_ID(i));
		RegData[i].deregCommand = new AlarmDeregistrationCommand(this, AlarmableManager::ALARM_ID(i));
	}
}

void Alarmable::SceneRegistration(float f, AlarmableManager::ALARM_ID id)
{
	assert(RegData[id].state == RegState::PENDING_REGISTRATION);
	SceneAttorney::SceneGetMgr::GetAlarmMgr()->Register(f, this, id);
	RegData[id].state = RegState::CURRENTLY_REGISTERED;
}

void Alarmable::SceneDeregistration(AlarmableManager::ALARM_ID id)
{
	assert(RegData[id].state == RegState::PENDING_DEREGISTRATION);
	SceneAttorney::SceneGetMgr::GetAlarmMgr()->Deregister(this, id);
	RegData[id].state = RegState::CURRENTLY_DEREGISTERED;
}

void Alarmable::SubmitSceneRegistration(int id, float time)
{
	AlarmableManager::ALARM_ID myID = AlarmableManager::ALARM_ID(id);
	assert(RegData[myID].state == RegState::CURRENTLY_DEREGISTERED);
	RegData[myID].regCommand->setTime(time);
	SceneAttorney::SceneGetMgr::SubmitCommand(RegData[myID].regCommand);
	RegData[myID].state = RegState::PENDING_REGISTRATION;
}

void Alarmable::SubmitSceneDeregistration(int id)
{
	AlarmableManager::ALARM_ID myID = AlarmableManager::ALARM_ID(id);
	assert(RegData[myID].state == RegState::CURRENTLY_REGISTERED);
	SceneAttorney::SceneGetMgr::SubmitCommand(RegData[myID].deregCommand);
	RegData[myID].state = RegState::PENDING_DEREGISTRATION;
}

void Alarmable::TriggerAlarm(AlarmableManager::ALARM_ID id)
{
	switch (id)
	{
	case AlarmableManager::ALARM_0:
		RegData[0].state = RegState::CURRENTLY_DEREGISTERED; 
		this->Alarm0();
		break;
	case AlarmableManager::ALARM_1:
		RegData[1].state = RegState::CURRENTLY_DEREGISTERED; 
		this->Alarm1();
		break;
	case AlarmableManager::ALARM_2:
		RegData[2].state = RegState::CURRENTLY_DEREGISTERED; 
		this->Alarm2();
		break;
	}
}

float Alarmable::CheckAlarm(AlarmableManager::ALARM_ID id)
{
	if (RegData[id].state == RegState::PENDING_REGISTRATION)
	{
		return RegData[id].regCommand->getTime();
	}
	if (RegData[id].state == RegState::CURRENTLY_REGISTERED)
	{
		return SceneAttorney::SceneGetMgr::GetAlarmMgr()->GetTime(this, id);
	}
	return 0;
}

void Alarmable::OverrideAlarm(AlarmableManager::ALARM_ID id, float f)
{
	if (f != 0)
	{
		RegData[id].regCommand->setTime(f);
	}
}

Alarmable::~Alarmable()
{
	for (int i = 0; i < AlarmableManager::ALARM_NUMBER; i++)
	{
		delete RegData[i].regCommand;
		delete RegData[i].deregCommand;
	}
}