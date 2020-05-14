#pragma once

#include "..\Game Object\GameObject.h"

class ParticleEffect;
class ParticleBurst;

class ParticleEmitter : public GameObject
{
public:
	ParticleEmitter() {};
	ParticleEmitter(const ParticleEmitter&) = delete;
	ParticleEmitter& operator=(const ParticleEmitter&) = delete;
	virtual ~ParticleEmitter();

	void Initialize(Vect v);

	virtual void Draw();

	virtual void Alarm0(); // Spawn new burst, then reset if needed
	virtual void Alarm1(); // Kill the first burst in the list
	virtual void Alarm2(); // Recycle all bursts (just in case), then yourself

	virtual void SceneEntry();
	virtual void SceneExit();

	void SetParent(ParticleEffect * effect) { parent = effect; };

	float GetStartSpeed();
	float GetSpeedDec();

private:
	typedef std::list<ParticleBurst *> BurstList;
	typedef BurstList::iterator BurstIterator;
	BurstList burstList;
	BurstList recycleList;

	Vect pos;
	ParticleEffect * parent;
	float burstCurrCount;
};