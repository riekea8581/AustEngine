#include "ParticleEmitter.h"
#include "ParticleBurst.h"
#include "ParticleEffect.h"
#include "ParticleEmitterFactory.h"

void ParticleEmitter::Initialize(Vect v)
{
	pos = v;
	burstCurrCount = 0;

	SubmitEntry();
}

void ParticleEmitter::Draw()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_FALSE);

	for (BurstIterator it = burstList.begin(); it != burstList.end(); it++)
	{
		(*it)->DrawParticles(parent->getGraphicsObject(), SceneManager::GetCurrentScene()->getCamera());
	}

	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);
}

void ParticleEmitter::Alarm0()
{
	ParticleBurst * tmp;
	if (recycleList.begin() == recycleList.end())
	{
		tmp = new ParticleBurst();
	}
	else
	{
		tmp = recycleList.front();
		recycleList.pop_front();
	}
	tmp->SetParent(this);
	tmp->InitializeData(pos, parent->GetParticleVectRange(), parent->GetParticleStartScale());
	burstList.push_back(tmp);
	burstCurrCount++;
	if(burstCurrCount < parent->GetBurstCount())
		Alarmable::SubmitSceneRegistration(0, parent->GetBurstFreq());
}

void ParticleEmitter::Alarm1()
{
	if (burstList.begin() != burstList.end())
	{
		recycleList.push_back(burstList.front());
		burstList.pop_front();
		Alarmable::SubmitSceneRegistration(1, parent->GetBurstFreq());
	}
}

void ParticleEmitter::Alarm2()
{
	while (!(burstList.empty()))
	{
		recycleList.push_back(burstList.front());
		burstList.pop_front();
	}
	Drawable::SubmitSceneDeregistration();
	SubmitExit();
}

void ParticleEmitter::SceneEntry()
{
	Drawable::SubmitSceneRegistration();
	Alarmable::SubmitSceneRegistration(0, 0);
	Alarmable::SubmitSceneRegistration(1, parent->GetBurstLifespan());
	Alarmable::SubmitSceneRegistration(2, parent->GetEmitterLifespan());
}

void ParticleEmitter::SceneExit()
{
	if (Alarmable::CheckAlarm(AlarmableManager::ALARM_ID::ALARM_0) != 0)
		Alarmable::SubmitSceneDeregistration(0);
	if (Alarmable::CheckAlarm(AlarmableManager::ALARM_ID::ALARM_1) != 0)
		Alarmable::SubmitSceneDeregistration(1);
	ParticleEmitterFactory::RecycleParticleEmitter(this);
}

float ParticleEmitter::GetStartSpeed()
{
	return parent->GetStartSpeed();
};

float ParticleEmitter::GetSpeedDec()
{
	return parent->GetSpeedDec(); 
};

ParticleEmitter::~ParticleEmitter()
{
	while (!(burstList.empty()))
	{
		delete burstList.front();
		burstList.pop_front();
	}
	while (!(recycleList.empty()))
	{
		delete recycleList.front();
		recycleList.pop_front();
	}
}